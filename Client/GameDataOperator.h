#pragma once
#include"GameData.h"
class GameDataOperator
{
public:
	//��ȡ����(x,y)����Ϣ���������Խ�緵��-1
	int readGameData(int x, int y);
	//������(x,y)д��,��ɫΪc
	void writeGameData(int x, int y, int c);
	//ɾ��ԭ��GameData������һ���µ�
	void createNewGameData();
	//��ȡ�÷�
	int readScore();
	//��ȡ�����ߵ��λ��
	int readBlockTop();
	//��ȡ�����ٶ�
	int readGameSpeed();
	//��ȡ��������
	int readScoreRate();
	//��ȡ�Ƿ�Ϊ�¿�ʼ����Ϸ
	bool readIsNewGame();
	//��ȡ�浵�������趨�÷�
	void resetScore(int s);
	//�����趨�Ƿ�Ϊ����Ϸ
	void resetIsNewGame(bool isg);
	//�����趨�����ߵ��λ��
	void resetBlockTop(int bt);
	//���ݵ�ǰ�����趨��Ϸ�ٶȺ͵÷ֱ���
	void updateSpeedAndRate();
};

