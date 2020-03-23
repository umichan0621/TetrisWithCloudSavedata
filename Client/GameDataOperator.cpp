#include "GameDataOperator.h"

int GameDataOperator::readGameData(int x, int y)
{
	if (y<0 || y>ROW - 1 || x<0 || x>COL - 1)
		return -1;
	
	return GameData::getGameData()->gameData[y][x];
}

int GameDataOperator::readScore() { return GameData::getGameData()->gameScore; }
int GameDataOperator::readBlockTop() { return GameData::getGameData()->blockTop; }
int GameDataOperator::readGameSpeed() { return GameData::getGameData()->gameSpeed; }
int GameDataOperator::readScoreRate() { return GameData::getGameData()->scoreRate; }
bool GameDataOperator::readIsNewGame() { return GameData::getGameData()->isNewGame; }
void GameDataOperator::resetScore(int s) { GameData::getGameData()->gameScore = s; }
void GameDataOperator::resetIsNewGame(bool isg) { GameData::getGameData()->isNewGame = isg; }
void GameDataOperator::resetBlockTop(int bt) { GameData::getGameData()->blockTop = bt; }

void GameDataOperator::createNewGameData()
{
	delete GameData::getGameData()->instance;
	GameData::getGameData()->instance = new GameData();
}

void GameDataOperator::writeGameData(int x, int y, int c)
{
	if (y<0 || y>ROW - 1 || x<0 || x>COL - 1)
		return;
	GameData::getGameData()->gameData[y][x] = c;
}

void GameDataOperator::updateSpeedAndRate()
{
	int score = GameData::getGameData()->gameScore;
	if (score > 1000 && score < 10000)
	{
		GameData::getGameData()->scoreRate = 500;
		GameData::getGameData()->gameSpeed = 2;
	}
	else if (score > 10000 && score < 100000)
	{
		GameData::getGameData()->scoreRate = 1000;
		GameData::getGameData()->gameSpeed = 4;
	}
	else if (score > 100000)
	{
		GameData::getGameData()->scoreRate = 10000;
		GameData::getGameData()->gameSpeed = 6;
	}
}