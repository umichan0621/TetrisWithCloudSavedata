#pragma once
#include"GameData.h"
class GameDataOperator
{
public:
	//读取坐标(x,y)块信息，如果坐标越界返回-1
	int readGameData(int x, int y);
	//对坐标(x,y)写入,颜色为c
	void writeGameData(int x, int y, int c);
	//删除原有GameData，创建一个新的
	void createNewGameData();
	//读取得分
	int readScore();
	//读取块的最高点的位置
	int readBlockTop();
	//读取下落速度
	int readGameSpeed();
	//读取分数倍率
	int readScoreRate();
	//读取是否为新开始的游戏
	bool readIsNewGame();
	//读取存档后重新设定得分
	void resetScore(int s);
	//重新设定是否为新游戏
	void resetIsNewGame(bool isg);
	//重新设定块的最高点的位置
	void resetBlockTop(int bt);
	//根据当前分数设定游戏速度和得分倍率
	void updateSpeedAndRate();
};

