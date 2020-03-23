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
	//默认服务器本机
	char ipAddress[20] = "127.0.0.1";
	//默认端口5000
	char port[10] = "5000";
public:
	//重新设定服务器ip和端口
	void setIPAddressAndPort(string ip, string port);
	//存取游戏存档，成功返回0，失败返回-1
	int saveandloadSaveData(bool mode, string s);
};

