#pragma once
#include<vector>
#include<string>
#include<fstream>
using namespace std;

const string IP_ADDRESS = "175.24.16.186";
const string PORT = "5000";
//����    ����
enum GameKey { ROW = 18, COL = 12 };

//��Ϸ������	����ģʽ
class GameData
{
private:
	friend class GameDataOperator;
	//GameData��Ψһʵ������
	static GameData* instance;
	//�洢��Ϸ���ݣ�0��ʾû�п飬!=0��ʾ����ɫ�Ŀ飬����(x,y)����ɫΪgame_data[y][x]
	static vector<vector<int>> gameData;
	//�÷ֱ���
	int scoreRate = 100;
	//��Ϸ�ٶ�
	int gameSpeed = 1;
	//�÷�
	int gameScore=0;
	//��ʾ��Ϸ�����п����ߵ��λ��
	int blockTop = ROW - 4;
	//�ж��Ƿ�Ϊ�¿�ʼ����Ϸ
	bool isNewGame = true;
	//private�Ĺ��죬��ʼ�����ݣ���ʼ����ײ�����
	GameData();
public:
	//��ȡ��Ϸ���ݵĵ�������
	static GameData* getGameData();

};