#pragma once
#include "GameDataOperator.h"
#include "Printer.h"
class Block
{
private:
	int blockX = -1;//ˮƽ����
	int blockY = -1;//��ֱ����
	int blockColor = 0;//��ɫ
	Printer blockPrinter;
	GameDataOperator op;
public:
	//��x��y����һ����ɫΪc�Ŀ�
	void createBlock(int x, int y, int c);
	//�����·����ͻʱ���̶���
	void soildBlock();
	//�жϿ��ƶ�x��y���Ƿ������ͻ����ͻ����true
	bool isConflict(int dx, int dy);
	//��ˮƽ�����ƶ�dx����ֱ�����ƶ�dy��-Ϊ��/�ϣ�+Ϊ��/��
	void moveBlock(int dx, int dy);
	//����y
	int getY();

};