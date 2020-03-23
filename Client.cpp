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
	WSADATA wsa_data; //WSADATA����,����windows socketִ�е���Ϣ
	SOCKET sock_client = INVALID_SOCKET;
	addrinfo* result = nullptr, hints;
	int i_result = 0; //���շ���ֵ
	//��ʼ��winsock��̬��(ws2_32.dll),MAKEWORD(2, 2)��������ʹ��winsock2.2�汾
	i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (i_result != 0)
		return -1;

	SecureZeroMemory(&hints, sizeof(hints));//����������0�����һ���ڴ�����
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//getaddrinfo�����ܹ��������ֵ���ַ�Լ����񵽶˿�������ת����
	//���ص���һ��sockaddr�ṹ�����������һ����ַ�嵥��
	//��Щsockaddr�ṹ�������׽ӿں���ֱ��ʹ��
	i_result = getaddrinfo(ipAddress, port, &hints, &result);

	if (i_result != 0)
	{
		WSACleanup();
		return -1;
	}
	//�����׽���
	sock_client = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sock_client == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}
	//���ӷ�����
	i_result = connect(sock_client, result->ai_addr, result->ai_addrlen);
	if (i_result == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}
	//�ͷ���getaddrinfo���صĴ洢�ռ䣬����addrinfo�ṹ��ai_addr�ṹ��ai_canonname�ַ���
	freeaddrinfo(result);

	char send_buf[BUF_SIZE];
	//stringתchar[]
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
	//��ȡ�浵
	if (mode == 1)
	{
		//������Ϣ
		char buf_msg[BUF_SIZE];
		//���ض����ֽ���
		int ret_val = 0;
		//���ط�����Ϣ�ֽ���
		int snd_result = 0;
		memset(buf_msg, 0, BUF_SIZE);
		//�������ݣ����޴��󣬷��ض����ֽ���
		ret_val = ::recv(sock_client, buf_msg, BUF_SIZE, 0);
		//��ȡ�浵
		if (ret_val > 0)
		{
			string tp(buf_msg);
			tp = tp.substr(1, tp.size() - 1);
			unsigned int rear = 0;
			while (rear < tp.size())
			{
				int front = 0;
				rear = tp.find("|");
				//�浵���
				int seq = stoi(tp.substr(front, 1));
				front += 1;
				//ʱ���
				string time_stamp = tp.substr(front, 16);
				front += 16;
				//�浵����
				string data = tp.substr(front, 12 * 18);
				front += 12 * 18;
				//�÷�
				int score = stoi(tp.substr(front, rear - front));
				tp = tp.substr(rear + 1, tp.size() - rear - 1);
				//�浵
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
