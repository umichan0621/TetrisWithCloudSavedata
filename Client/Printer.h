#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  
#include <string>
#include <iostream>
#include "GameData.h"
using namespace std;
//ʵ�����п���̨���������
class Printer
{
public:
	//��(x,y)��ӡһ����ɫΪc�Ŀ�
	void printOneBlock(int x, int y, int c);
	//���(x,y)�Ŀ�
	void clearOneBlock(int x, int y);
	//��(x,y)��ӡ��ɫΪc���ַ���s
	void printText(int x, int y, int c, string s);
};

