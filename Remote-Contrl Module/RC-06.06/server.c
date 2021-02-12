#include <sys/types.h>
#include <sys/socket.h>                         							// 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         							// 包含AF_INET相关结构
#include <arpa/inet.h>                      								// 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define PORT    81
#define MYKEY   12345
#define SIZE    10240

int main()
{
	/* 定义变量 */
    int shared_memory_id;													// 定义共享内存标识符
    char *shared_memory_addr;                       						// 定义子进程共用的共享内存地址
	char buf[100];															// 用于保存接受的数据
	int server_sockfd;														// 用于保存服务端套接字标识符
	int client_sockfd;														// 用于保存客户端套接字标识符
    int server_len;															// 用于保存服务端消息长度
	int client_len;															// 用于保存客户端消息长度
    struct sockaddr_in server_sockaddr;										// 定义服务端套接字地址
	struct sockaddr_in client_sockaddr;										// 定义客户端套接字地址
	int optval = 1;															// 用于对套接字进行相关配置
	
	/* 共享内存初始化 */
    shared_memory_id = shmget(MYKEY, SIZE, IPC_CREAT | 0600);				// 创建共享内存,返回"shared_memory_id"作为共享内存标识符
    shared_memory_addr = (char *) shmat(shared_memory_id, 0, 0);			// 启动对该共享内存的访问
    if(shared_memory_id == -1)												// 启用共享内存失败
    {
        printf("shmid error\n");
    }
    memset(shared_memory_addr, 0, SIZE);									// 清空共享内存数据
    memset(buf, 0, 100);													// 清空数据

	/* 套接字初始化 */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 						// 定义套接字类型
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    server_len = sizeof(server_sockaddr);
    setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));	//允许重复使用本地地址和套接字绑定
    /* 绑定端口 */
    if(bind(server_sockfd, (struct sockaddr *)&server_sockaddr, server_len) == -1)
    {
        perror("bind:");
        exit(1);
    }
    if(listen(server_sockfd, 5) == -1)
    {
        perror("Listen:");
        exit(1);
    }
	
	/* 开始监听客户端消息 */
    printf("Listening...\n");												// 输出提示信息
    client_len = sizeof(client_sockaddr);									// 计算客户端消息长度
    pid_t ppid,pid;															// 定义进程变量
	while(1)
	{
		/* 接收套接字中已建立的连接,若失败则输出提示信息 */
		if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_sockaddr, &client_len)) == -1)
        {
			perror("Accept Error:");
			exit(1);
        }
		printf("%s logined IN\n", inet_ntoa(client_sockaddr.sin_addr));		// 显示客户端IP地址
		
		/* 开辟进程用于单个链接通信 */
		ppid = fork();
		if(ppid == -1)														// 若创建进程失败,则输出提示信息
		{
			printf("fork 1 failed:");
		}
		
		if(ppid == 0)														// 创建进程成功
		{
			pid = fork();													// 创建子进程
			if(pid == -1)													// 若创建子进程失败,则输出提示信息
			{
				printf("fork 2 failed:");
				exit(1);
			}
			
			/* 子子进程用于接收消息 */
			if(pid==0)
			{
				int recvbytes;												// 定义用于记录接收到的数据长度
				while(1)
				{
				   if((recvbytes = recv(client_sockfd,buf,100,0)) == -1)	// 若接收数据失败,则输出提示信息
					{
						perror("read client_sockfd failed:");
					}
					if(recvbytes == 0)										// 若recvbytes返回值为0,表示客户端退出
					{
						printf("Receive Child out\n");
					    exit(0);
					}
					usleep(10000);
					printf("client send buf=%s\n", buf);					// 输出接收到的消息
					strcpy(shared_memory_addr, buf);						// 将数据保存在当前(第一个)的数据段
				}
			}
			/* 子进程用于发送消息 */
			if(pid > 0)
			{
			   while(1)
				{
					/* 判断客户端退出 */
					if(waitpid(0, NULL, WNOHANG))
					{
						printf("Send Clild out\n");
						close(client_sockfd);
						exit(0);
					}
					usleep(2000);
					if(*(shared_memory_addr) != 0)							// 共享内存非空时,发送消息
					{
						printf("shmaddr is :%s\n", shared_memory_addr);		// 输出数据内容
					   	write(client_sockfd, shared_memory_addr, SIZE);		// 将数据写入客户端套接字
						usleep(2000);
						*(shared_memory_addr) = 0;							// 数据段清零
					}
				}
			}
		}
		
		if(ppid > 0)		//总父进程返回等待接收消息,会存在僵尸进程，下次运行到这里的时候会被杀死
		{
			waitpid(0, NULL, WNOHANG);
			close(client_sockfd);
		}
    }
 
}
