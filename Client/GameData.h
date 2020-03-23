#pragma once
#include<vector>
#include<string>
#include<fstream>
using namespace std;

const string IP_ADDRESS = "175.24.16.186";
const string PORT = "5000";
//行数    列数
enum GameKey { ROW = 18, COL = 12 };

//游戏数据类	单例模式
class GameData
{
private:
	friend class GameDataOperator;
	//GameData的唯一实例对象
	static GameData* instance;
	//存储游戏数据，0表示没有块，!=0表示有颜色的块，坐标(x,y)的颜色为game_data[y][x]
	static vector<vector<int>> gameData;
	//得分倍率
	int scoreRate = 100;
	//游戏速度
	int gameSpeed = 1;
	//得分
	int gameScore=0;
	//表示游戏数据中块的最高点的位置
	int blockTop = ROW - 4;
	//判断是否为新开始的游戏
	bool isNewGame = true;
	//private的构造，初始化数据，初始化最底层三行
	GameData();
public:
	//获取游戏数据的单例对象
	static GameData* getGameData();

};