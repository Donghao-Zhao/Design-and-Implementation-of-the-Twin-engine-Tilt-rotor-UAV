#include <sys/types.h>
#include <sys/socket.h>                         	// 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         	// 包含AF_INET相关结构
#include <arpa/inet.h>                          	// 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h> 								// 标准函数库定义
#include <unistd.h> 								// Unix 标准函数定义
#include <sys/stat.h>
#include <fcntl.h> 									// 文件控制定义
#include <termios.h>								// PPSIX 终端控制定义
#include <errno.h> 									// 错误号定义
#define  PORT 81
#define  IP_ADDR "47.95.13.239"
#define  SIZE 10240
 
 /*---------------------------------------------------------------
【函    数】set_opt
【功    能】初始化串口通信,配置串口信息
【参    数】int fd,int nSpeed, int nBits, char nEvent, int nStop
【返 回 值】0或-1
【注意事项】无
----------------------------------------------------------------*/
int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	/* 获取fd串口对应的termios结构体，这步主要是查询串口是否启动正常 */
	if(tcgetattr(fd, &oldtio) != 0)
	{ 
		perror("SetupSerial 1");
		return -1;
	}
	/* 清空数据位设置 */
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;											// 配置成本地模式(本地连接、不改变端口所有者)、可读
	newtio.c_cflag &= ~CSIZE;													// 清空数据位设置
	/* 选择数据位 */
	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;	
			break;
	}
	/* 选择校验位 */
	switch( nEvent )
	{
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);									// 启用输入奇偶检测、去掉第八位
			break;
		case 'E': 
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			break;
		case 'N':  
			newtio.c_cflag &= ~PARENB;
			break;
	}
	/* 选择波特率 */
	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	/* 选择停止位，貌似linux下不能设置(1.5 0.5)停止位 */
	if(nStop == 1) newtio.c_cflag &=  ~CSTOPB;
	else if(nStop == 2) newtio.c_cflag |=  CSTOPB;
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd, TCIFLUSH);
	/* 设置新配置 */
	if((tcsetattr(fd, TCSANOW, &newtio)) != 0)
	{
		perror("com set error");
		return -1;
	}
	return 0;
}

/*---------------------------------------------------------------
【函    数】indexOf
【功    能】判断str2字符串在str1中,首次出现的位置
【参    数】字符串str1,字符串str2
【返 回 值】返回str2字符串在str1中,首次出现的位置location
【注意事项】无
----------------------------------------------------------------*/
int indexOf(char *str1, char *str2)
{  
    char *pointer = str1;														// 定义指向字符串首地址的指针
    int location = 0;  															// 定义函数返回值
    pointer = strstr(str1, str2);
    if(pointer == NULL)  														// 若str1中没有str2子串,返回-1
        return -1;
    else{
        while(str1 != pointer)
        {
            str1++;
            location++;
        }
    }
    return location;
}

int main()
{
	/* 定义变量 */
	int uart_open_fd;															// 用于记录打开串口的标识符
	char *uart = "/dev/ttyAMA0";												// ttyAMA0代表树莓派zero上的串口
	int client_sockfd;															// 用于保存客户套接字标识符
	int client_len;                                    							// 用于客户端消息长度
	struct sockaddr_in address;                 								// 定义客户套接字地址
	int connection_result;														// 保存请求连接的返回值
	char send_buffer[100];                              						// 定义要发送的数据
	char shmaddr[SIZE];                    										// 定义共享内存,接受服务器发送的全部数据 
	int read_result;															// 保存读取串口数据结果的返回值
	char uart_buffer[100];														// 用于接收串口数据
	
	/* 打开串口，可读写，不将该设备作为此进程的控制终端，非阻塞方式操作 */
	if((uart_open_fd = open(uart, O_RDWR|O_NOCTTY|O_NDELAY)) < 0)
	{
		printf("open %s is failed\n", uart);									// 若初始化串口失败,则输出提示信息
	}
	else																		// 初始化串口成功
	{
		printf("open %s is success\n", uart);
		set_opt(uart_open_fd, 115200, 8, 'N', 1); 								// 设置串口
	}
	
	/* 套接字初始化 */
	client_sockfd = socket(AF_INET,SOCK_STREAM, 0);    							// 定义套接字类型
	address.sin_family = AF_INET;               								// 定义套接字地址中的域
	address.sin_addr.s_addr = inet_addr(IP_ADDR);								// 定义套接字地址
	address.sin_port = htons(PORT);                 							// 定义套接字端口
	memset(send_buffer, 0, 100);												// 清空原始数据
	client_len = sizeof(address);
	connection_result = connect(client_sockfd, (struct sockaddr *) &address, client_len); // 请求连接
	/* 若连接失败,输出提示信息 */
	if(connection_result == -1)  
	{
		perror("Connect failed");
		return 1;
	}
    printf("成功connect服务器:\n");												// 连接成功
	
	/* 创建进程用于接收发送消息 */
    pid_t pid;
    pid=fork();																	// 创建进程
	/* 若创建进程失败,输出提示信息 */
    if(pid == -1)
    {
        printf("fork failed");
    }
    int sendbytes=0;
	
	/* 父进程用于发送消息 */
    if(pid > 0)
    {
       while(1)
        {
			if(waitpid(0,NULL,WNOHANG))											// 判断客户端退出
			{
				printf("Send Child out\n");
				close(client_sockfd);
				exit(0);
			}
			/* 读取K66串口数据 */
			read_result = read(uart_open_fd, uart_buffer, sizeof(uart_buffer));
			/* 若读取到了消息 */
			if(read_result > 0)
			{
				printf("Uart Success!\n");										// 输出提示信息
				strcpy(send_buffer, "@@");										// 将"@@"加在数据起始位置作为报头
				strcat(send_buffer, uart_buffer);								// 将串口数据传入send_buffer,等待数据发送
				memset(uart_buffer, 0, 100);									// 清空串口数据
				/* 向服务器发送消息 */
				if((sendbytes=send(client_sockfd, send_buffer, 100, MSG_WAITALL)) == -1)
				{
					perror("send to server failed:");
				}  // 向服务器发送消息
				usleep(1000);
				memset(send_buffer, 0, 100);									// 清空send_buffer数据
			}
        }      
    }
	
	/* 子进程用于接受消息并读取 */
    if(pid == 0)
    {
        while(1)
        {
			int length_of_recv;													// 定义接收到的数据量
			length_of_recv = recv(client_sockfd, shmaddr, SIZE, MSG_WAITALL);	// 服务器断开时，返回值为0
			if(length_of_recv == 0)												// 若服务器断开,则输出提示信息
			{
				printf("服务器已断开\n");
				exit(0);
			}
			printf("shmaddr is : %s\n", shmaddr);								// 输出数据
			/* 当共享内存不为空时,判断是否向串口发送信息 */
			while(*(shmaddr) != 0)
			{
				if(indexOf(shmaddr, "%%") == 0)									// 由客户端发来的数据
				{
					printf("UART %s\n", (shmaddr + 2));
					write(uart_open_fd, (shmaddr + 2), strlen(shmaddr + 2));
				}
				// printf("UART %s\n", (shmaddr));								// 输出数据
				// 如果是K66发来的数据,就不再向串口发送
				else if(indexOf(shmaddr, "@@") == 0)							// 由树莓派发来的消息
				{
					printf("UART %s\n", (shmaddr + 2));
					printf("have date but not send.\n");
				}
				else															// 不明数据
				{
					printf("Bad data!\n");
				}
				// write(uart_open_fd, shmaddr, strlen(shmaddr)); 				// 发送串口流数据
				usleep(1000);
				*(shmaddr) = 0;													// 操作结束后及时清空当前数据
			}
            usleep(1000);
        }    
    }
    close(client_sockfd);
}
