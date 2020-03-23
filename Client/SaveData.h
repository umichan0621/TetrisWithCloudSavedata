#pragma once
#include<string>
using namespace std;

//游戏存档
class SaveData
{
private:
	string time_stamp = "";//时间戳
	int score = 0;//得分
	string data = "";//游戏数据
	bool is_empty = true;//判断存档是否为空，默认空
public:
	int getScore();//获取得分
	string getTimeStamp();//获取时间戳
	string getData();//获取数据
	bool isEmpty();//获取存档是否为空

	//写入存档数据，参数：得分、数据、时间戳
	void writeSaveData(int score, string data, string time_stamp);
};

//游戏存档集，单例模式
class SaveDataSet
{
private:
	SaveData sd1;
	SaveData sd2;
	SaveData sd3;
	SaveDataSet();
	static SaveDataSet* instance;
public:
	static SaveDataSet* getSet();
	//获取第seq个存档
	SaveData& getSaveData(int seq);
};