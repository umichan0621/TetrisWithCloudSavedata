#pragma once
#pragma comment(lib, "ws2_32.lib")
#include "SaveData.h"
#include <WinSock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
using namespace std;

const int BUF_SIZE = 1024;

class Client
{
private:
	//Ĭ�Ϸ���������
	char ipAddress[20] = "127.0.0.1";
	//Ĭ�϶˿�5000
	char port[10] = "5000";
public:
	//�����趨������ip�Ͷ˿�
	void setIPAddressAndPort(string ip, string port);
	//��ȡ��Ϸ�浵���ɹ�����0��ʧ�ܷ���-1
	int saveandloadSaveData(bool mode, string s);
};

