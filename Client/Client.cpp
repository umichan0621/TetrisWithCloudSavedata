#include "Client.h"

void Client::setIPAddressAndPort(string ip, string port)
{
	unsigned int i;
	for (i = 0; i < ip.length(); i++)
		ipAddress[i] = ip[i];
	ipAddress[i] = '\0';

	for (i = 0; i < port.length(); i++)
		this->port[i] = port[i];
	this->port[i] = '\0';
}

int Client::saveandloadSaveData(bool mode, string s)
{
	WSADATA wsa_data; //WSADATA变量,包含windows socket执行的信息
	SOCKET sock_client = INVALID_SOCKET;
	addrinfo* result = nullptr, hints;
	int i_result = 0; //接收返回值
	//初始化winsock动态库(ws2_32.dll),MAKEWORD(2, 2)用于请求使用winsock2.2版本
	i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (i_result != 0)
		return -1;

	SecureZeroMemory(&hints, sizeof(hints));//其作用是用0来填充一块内存区域
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//getaddrinfo函数能够处理名字到地址以及服务到端口这两种转换，
	//返回的是一个sockaddr结构的链表而不是一个地址清单。
	//这些sockaddr结构随后可由套接口函数直接使用
	i_result = getaddrinfo(ipAddress, port, &hints, &result);

	if (i_result != 0)
	{
		WSACleanup();
		return -1;
	}
	//创建套接字
	sock_client = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sock_client == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}
	//连接服务器
	i_result = connect(sock_client, result->ai_addr, result->ai_addrlen);
	if (i_result == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}
	//释放由getaddrinfo返回的存储空间，包括addrinfo结构、ai_addr结构和ai_canonname字符串
	freeaddrinfo(result);

	char send_buf[BUF_SIZE];
	//string转char[]
	unsigned int i = 0;
	for (i = 0; i < s.size(); i++)
	{
		send_buf[i] = s[i];
	}
	send_buf[i] = '\0';

	i_result = send(sock_client, send_buf, static_cast<int>(strlen(send_buf)), 0);
	if (i_result < 1)
	{
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	//读取存档
	if (mode == 1)
	{
		//接收信息
		char buf_msg[BUF_SIZE];
		//返回读入字节数
		int ret_val = 0;
		//返回发送信息字节数
		int snd_result = 0;
		memset(buf_msg, 0, BUF_SIZE);
		//接收数据，若无错误，返回读入字节数
		ret_val = ::recv(sock_client, buf_msg, BUF_SIZE, 0);
		//读取存档
		if (ret_val > 0)
		{
			string tp(buf_msg);
			tp = tp.substr(1, tp.size() - 1);
			unsigned int rear = 0;
			while (rear < tp.size())
			{
				int front = 0;
				rear = tp.find("|");
				//存档序号
				int seq = stoi(tp.substr(front, 1));
				front += 1;
				//时间戳
				string time_stamp = tp.substr(front, 16);
				front += 16;
				//存档数据
				string data = tp.substr(front, 12 * 18);
				front += 12 * 18;
				//得分
				int score = stoi(tp.substr(front, rear - front));
				tp = tp.substr(rear + 1, tp.size() - rear - 1);
				//存档
				SaveDataSet::getSet()->getSaveData(seq).writeSaveData(score, data, time_stamp);
			}
		}
	}
	i_result = shutdown(sock_client, SD_SEND);
	if (i_result == SOCKET_ERROR)
	{
		closesocket(sock_client);
		WSACleanup();
		return -1;
	}
	closesocket(sock_client);
	WSACleanup();
	return 0;
}
