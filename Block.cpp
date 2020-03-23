#include "Block.h"

void Block::createBlock(int x, int y, int c)
{
	blockX = x;
	blockY = y;
	blockColor = c;
	//打印块
	blockPrinter.printOneBlock(x, y, c);
}

void Block::soildBlock() { op.writeGameData(blockX, blockY, blockColor); }

bool Block::isConflict(int dx, int dy)
{
	if (blockY + dy < 0)//移动后在上边界外
		return false;
	if (op.readGameData(blockX + dx, blockY + dy) == 0)
		return false;
	return true;
}

void Block::moveBlock(int dx, int dy)
{
	//删除原有的块
	blockPrinter.clearOneBlock(blockX, blockY);
	blockX += dx;
	blockY += dy;
	//打印新的位置的块
	blockPrinter.printOneBlock(blockX ,blockY, blockColor);
}

int Block::getY() { return blockY; }


