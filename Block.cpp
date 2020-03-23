#include "Block.h"

void Block::createBlock(int x, int y, int c)
{
	blockX = x;
	blockY = y;
	blockColor = c;
	//��ӡ��
	blockPrinter.printOneBlock(x, y, c);
}

void Block::soildBlock() { op.writeGameData(blockX, blockY, blockColor); }

bool Block::isConflict(int dx, int dy)
{
	if (blockY + dy < 0)//�ƶ������ϱ߽���
		return false;
	if (op.readGameData(blockX + dx, blockY + dy) == 0)
		return false;
	return true;
}

void Block::moveBlock(int dx, int dy)
{
	//ɾ��ԭ�еĿ�
	blockPrinter.clearOneBlock(blockX, blockY);
	blockX += dx;
	blockY += dy;
	//��ӡ�µ�λ�õĿ�
	blockPrinter.printOneBlock(blockX ,blockY, blockColor);
}

int Block::getY() { return blockY; }


