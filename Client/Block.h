#pragma once
#include "GameDataOperator.h"
#include "Printer.h"
class Block
{
private:
	int blockX = -1;//水平方向
	int blockY = -1;//竖直方向
	int blockColor = 0;//颜色
	Printer blockPrinter;
	GameDataOperator op;
public:
	//在x，y创建一个颜色为c的块
	void createBlock(int x, int y, int c);
	//块与下方块冲突时，固定块
	void soildBlock();
	//判断块移动x，y后是否产生冲突，冲突返回true
	bool isConflict(int dx, int dy);
	//向水平方向移动dx，竖直方向移动dy，-为左/上，+为右/下
	void moveBlock(int dx, int dy);
	//返回y
	int getY();

};