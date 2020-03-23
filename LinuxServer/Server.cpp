#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <fcntl.h>
#include <string>
#include <iostream>

const int QUEUE = 20;  //连接请求队列
const int PORT = 6000;//服务器开放端口
const int BUFFERSIZE = 1024;//Socket通信收发信息缓存区大小


//服务器TCP    Socket步骤
//1.创建socket  socket()
//2.设置socket  setsockopt()
//3.绑定IP地址端口信息  bind()
//4.开启监听  listen()
//5.接受客户端连接   accept()
//6.收发数据  send()/recv()
//7.关闭网络连接
//8.关闭监听

class Server
{
public:
	Server();
	~Server();
	void wait_for_client();
	void data_trans(int);
private:
	//存放了服务端地址族、端口、ip地址，用来处理通信地址
	sockaddr_in ServerAddr;
	//存放了客户端地址族、端口、ip地址，用来处理通信地址
	sockaddr_in ClientAddr;
	socklen_t AddrLen;
	//服务器端socket套接字描述符
	int ServerSocket;


};


int main()
{
	Server Server;
	Server.wait_for_client();


	return 0;
}

Server::Server()
{
	AddrLen = sizeof(ClientAddr);
	//若成功则返回一个sockfd (套接字描述符)
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//下面设置sockaddr_in 结构体中相关参数
	ServerAddr.sin_family = AF_INET;
	//将一个无符号短整型数值转换为网络字节序，即大端模式
	ServerAddr.sin_port = htons(PORT);
	//INADDR_ANY就是指定地址为0.0.0.0的地址
	//这个地址事实上表示不确定地址，或"所有地址"、“任意地址”。
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定IP地址端口信息
	bind(ServerSocket, (struct sockaddr*) & ServerAddr, sizeof(ServerAddr));
	//监听Socket端口
	listen(ServerSocket, QUEUE);
	std::cout << "服务器启动成功" << std::endl;
}
Server::~Server()
{
	//close(RetVal);   //因为accept函数连接成功后还会生成一个新的套接字描述符，结束后也需要关闭
	//close(ServerSocket);     //关闭socket套接字描述符
}
//服务器循环执行，等待客户端连接
void Server::wait_for_client()
{
	while (1)
	{
		//成功返回非负描述字，出错返回-1
		//如果accept成功，那么其返回值是由内核自动生成的一个全新描述符，代表与所返回客户的TCP连接
		int Descriptor = accept(ServerSocket, (struct sockaddr*) & ClientAddr, &AddrLen);
		if (Descriptor != -1)
		{
			//创建线程
			//如果线程调用的是某个类A的函数b(int)，构造时参数为(&A::b,this,int)
			//std::thread Thread(&Server::data_trans, this, Descriptor);
			std::cout << Descriptor << std::endl;
			std::thread * Thread = new std::thread(&Server::data_trans, this, Descriptor);

			//分离线程
			Thread->detach();

		}

	}
}

//多线程数据传输，参数为int服务器端socket描述符
void Server::data_trans(int Descriptor)
{
	//缓存区	大小1024
	char Buffer[BUFFERSIZE];
	//缓存区初始化	置零
	memset(Buffer, 0, sizeof(Buffer));

	//接收数据  若无错误，返回读入字节数
	ssize_t ret_val = recv(Descriptor, Buffer, sizeof(Buffer), 0);
	if (ret_val != -1)
	{
		std::cout << Buffer << std::endl;
		close(Descriptor);
		return;
	}
	
}



