#include "SaveData.h"

SaveDataSet* SaveDataSet::instance = 0;
SaveDataSet::SaveDataSet(){}
string SaveData::getData() { return data; }
string SaveData::getTimeStamp() { return time_stamp; }
int SaveData::getScore() { return score; }
bool SaveData::isEmpty() { return is_empty; }
void SaveData::writeSaveData(int score, string data, string time_stamp)
{
	this->score = score;
	this->data = data;
	this->time_stamp = time_stamp;
	this->is_empty = false;
}

SaveDataSet* SaveDataSet::getSet()
{
	if (instance == 0)
		instance = new SaveDataSet;
	return instance;
}

SaveData& SaveDataSet::getSaveData(int seq)
{
	if (seq == 0)
		return sd1;
	else if (seq == 1)
		return sd2;
	else
		return sd3;
}