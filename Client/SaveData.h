#pragma once
#include<string>
using namespace std;

//��Ϸ�浵
class SaveData
{
private:
	string time_stamp = "";//ʱ���
	int score = 0;//�÷�
	string data = "";//��Ϸ����
	bool is_empty = true;//�жϴ浵�Ƿ�Ϊ�գ�Ĭ�Ͽ�
public:
	int getScore();//��ȡ�÷�
	string getTimeStamp();//��ȡʱ���
	string getData();//��ȡ����
	bool isEmpty();//��ȡ�浵�Ƿ�Ϊ��

	//д��浵���ݣ��������÷֡����ݡ�ʱ���
	void writeSaveData(int score, string data, string time_stamp);
};

//��Ϸ�浵��������ģʽ
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
	//��ȡ��seq���浵
	SaveData& getSaveData(int seq);
};