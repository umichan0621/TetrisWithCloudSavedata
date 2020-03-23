#include "Printer.h"

void Printer::printOneBlock(int x, int y, int c)
{
	//在界面外就不打印
	if (y<0 || y>ROW - 1)
		return;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos.X = 2 * (x + 1);
	cursorPos.Y = y + 1;
	SetConsoleTextAttribute(hStdout, c);
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "█";
	cursorPos.X = 0;
	cursorPos.Y = ROW + 2;
	SetConsoleCursorPosition(hStdout, cursorPos);
}

void Printer::printText(int x, int y, int c, string s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleTextAttribute(hStdout, c);
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << s;
	cursorPos.X = 0;
	cursorPos.Y = ROW + 2;
	SetConsoleCursorPosition(hStdout, cursorPos);
}

void Printer::clearOneBlock(int x, int y)
{
	//在界面外就不清除
	if (y<0 || y>ROW - 1)
		return;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos.X = 2 * (x + 1);
	cursorPos.Y = y + 1;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << "  ";
	cursorPos.X = 0;
	cursorPos.Y = ROW + 2;
	SetConsoleCursorPosition(hStdout, cursorPos);
}