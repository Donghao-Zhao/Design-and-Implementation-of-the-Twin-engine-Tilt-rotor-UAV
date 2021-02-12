#include <sys/types.h>
#include <sys/socket.h>											// 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>											// 包含AF_INET相关结构
#include <arpa/inet.h>											// 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
#define  PORT 81
#define IP_ADDR "47.95.13.239"
#define SIZE 10240


/*---------------------------------------------------------------
【函    数】indexOf
【功    能】判断str2字符串在str1中,首次出现的位置
【参    数】字符串str1,字符串str2
【返 回 值】返回str2字符串在str1中,首次出现的位置location
【注意事项】无
----------------------------------------------------------------*/
int indexOf(char *str1, char *str2)
{
    char *pointer = str1;										// 定义指向字符串首地址的指针
    int location = 0;  											// 定义函数返回值
    pointer = strstr(str1, str2);
    if(pointer == NULL)  										// 若str1中没有str2子串,返回-1
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

/*---------------------------------------------------------------
【函    数】checkStr
【功    能】匹配字符串是否相等
【参    数】字符串str1,字符串str2
【返 回 值】相等返回1,不相等返回0
【注意事项】无
----------------------------------------------------------------*/
int checkStr(char *str1, char *str2)								//匹配字符串是否相等
{
	for (int i = 0; i < strlen(str2); i++)
	{
		if (str1[i] != str2[i]) return 0;
	}
	return 1;
}

/*---------------------------------------------------------------
【函    数】reStr
【功    能】在字符串str1中,替换字符串str2为str3
【参    数】原字符串str1, 被替换的字符串str2, 替换为字符串str3
【返 回 值】无
【注意事项】无
----------------------------------------------------------------*/
void reStr(char *s1, char *s2, char *s3)
{
	int s1len = strlen(s1),
	s2len = strlen(s2),
	s3len = strlen(s3);
	int n1 = s1len - s2len;
	int n2 = s2len - s3len;
	if (n2 > 0)
	{
		//后面的字符串全部向前移n2个位置
		for (int i = s2len; i < s1len; i++)
		{
			s1[i - n2] = s1[i];
		}
		s1[s1len - n2] = '\0';
	}
	for (int i = s1len; i >= s2len; i--)
	{
		s1[i - n2] = s1[i];
	}
	s1[s1len - n2 + 1] = '\0';
	//后面的字符串全部向后移n2个位置
	for (int i = 0; i < s3len; i++)
	{
		s1[i] = s3[i];
	}
}

/*---------------------------------------------------------------
【函    数】replaceStr
【功    能】替换字符串并返回替换次数
【参    数】原字符串str1, 被替换的字符串str2, 替换为字符串str3
【返 回 值】被替换次数n
【注意事项】无
----------------------------------------------------------------*/
int replaceStr(char *s1, char *s2, char *s3)
{
	int n = 0;
	for (int i = 0; i < strlen(s1); i++)
	{
		if (s1[i] == s2[0] && checkStr(&s1[i], s2) == 1)
		{
			reStr(&s1[i], s2, s3);
			n++;
		}
	}
	return n;
}

int main()
{
	/* 定义变量 */
    int cmptclient_sockfd;										// 用于保存客户端套接字标识符
    int cmptclient_len;											// 用于保存客户端消息长度
    struct sockaddr_in address;									// 定义客户套接字地址
    int connection_result;										// 定义请求连接的返回值
	char send_buffer[100];										// 用于保存要发送的消息
	char temporary_data_buffer[120];							// 用于暂存输入的数据
    char character_data;										// 用于保存要输入的单个字符
    char shmaddr[SIZE]; 										// 定义用于接收数据的共享内存
	int sendbytes = 0;											// 定义写入数据的字节数
    char string[50] = "\0";										// 用于连接断开的数据并输出
	int display_flag = 0;										// 定义用于判断是否输出数据的标志位
	
	/* 套接字初始化 */
    cmptclient_sockfd = socket(AF_INET, SOCK_STREAM, 0);		// 定义套接字类型
    address.sin_family = AF_INET;								// 定义套接字地址中的域
    address.sin_addr.s_addr = inet_addr(IP_ADDR);				// 定义套接字地址
    address.sin_port = htons(PORT);								// 定义套接字端口
    memset(send_buffer, 0, 100);								// 清空原始数据内容
	memset(shmaddr, 0, SIZE);									// 清空共享内存 
	cmptclient_len = sizeof(address);
	connection_result = connect(cmptclient_sockfd, (struct sockaddr *) &address, cmptclient_len); // 请求连接
	
	/* 若连接失败,输出提示信息 */
	if (connection_result == -1)
    {
		perror("Connect failed");
		return 1;
    }
    printf("ConnectOK.\n");										// 连接成功
	
	/* 创建进程用于接收发送消息 */
    pid_t pid;
    pid = fork();												// 创建进程
	/* 若创建进程失败,输出提示信息 */
    if(pid == -1)
    {
        printf("fork failed");
    }
	/* 子进程用于接受消息并读取 */
    if(pid == 0)
    {
        while(1)
        {
			int recvbytes;										// 定义接收到的数据量
			recvbytes = recv(cmptclient_sockfd, shmaddr, SIZE, MSG_WAITALL);
			if(recvbytes == 0)									// 返回0表示服务器已断开
			{
				printf("Receive Child out\n");
				exit(0);
			}

			/* 当共享内存不为空时,判断是否输出信息 */
			while(*(shmaddr) != 0)
			{
				/* 若为K66发来的数据 */
				if(indexOf(shmaddr,"@@") == 0)
				{
					replaceStr(shmaddr, "?", "\r\n");			// 替换"?"为"\r\n"
					display_flag = 2;
					strcpy(string,(shmaddr+2));
				}
				/* 若是客户端发来的数据 */
				else if(indexOf(shmaddr,"%%") == 0)
				{
					if(strcmp((shmaddr), "%%2") == 0)
					{
						printf("Send out\n");
						close(cmptclient_sockfd);
						exit(0);
					}
					strcpy(string, shmaddr + 2);				// 直接将数据放到string中
					display_flag = 1;							// 标记为可发送
				}
				/* 判断是否可以显示数据 */
				if(display_flag == 1)							// 若来自客户端,应该显示数据
				{
					printf(" UART %s\r\n", string);				// 输出数据
					display_flag = 0;							// 标志位记为不可发送
					memset(string, '\0', sizeof(string));		// 清空数据
				}
				if(display_flag == 2)							// 若为来自K66的数据并可显示,则输出数据
				{
					printf("%s", string);						// 输出数据
					display_flag = 0;							// 标志位记为不可发送
					memset(string, '\0', sizeof(string));		// 清空数据
				}
				usleep(1000);
				*(shmaddr) = 0;
			}
		}
		usleep(1000); 
    }

	/* 父进程用于发送消息 */
    if(pid > 0)
    {
       while(1)
        {
			/* 判断服务端退出 */
			if(waitpid(0, NULL, WNOHANG))
			{
				printf("Send out\n");
				close(cmptclient_sockfd);
				exit(0);
			}
			/* 从键盘接收消息数据 */
			system("stty raw");									// 设置原始输入,只接收单个字符
			fflush(stdin);										// 清空输入缓冲区
			character_data = getchar();							// 从键盘接收单个字符
			system("stty -raw");								// 关闭原始输入模式
			memset(temporary_data_buffer, 0, 120);				// 清空数据
			strcpy(temporary_data_buffer, "%%");				// 客户端数据添加"%%"报头
			strcat(temporary_data_buffer, &character_data);		// 将字符数据放到临时变量中
			strcpy(send_buffer, temporary_data_buffer);			// 语句传入"send_buffer"中
			memset(temporary_data_buffer, 0, 120);				// 清空数据
			/* 向服务器发送消息 */
			if((sendbytes = write(cmptclient_sockfd, send_buffer, 100)) == -1)
			{
				perror("send to server failed:");
			}
			usleep(1000);
			memset(send_buffer, 0, 100);						// 清空"send_buffer"数据
		}     
    }
    close(cmptclient_sockfd);
    return 0;
} 
