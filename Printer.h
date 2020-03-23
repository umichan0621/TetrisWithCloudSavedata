#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  
#include <string>
#include <iostream>
#include "GameData.h"
using namespace std;
//实现所有控制台的输出操作
class Printer
{
public:
	//在(x,y)打印一个颜色为c的块
	void printOneBlock(int x, int y, int c);
	//清除(x,y)的块
	void clearOneBlock(int x, int y);
	//在(x,y)打印颜色为c的字符串s
	void printText(int x, int y, int c, string s);
};

