#include "GameData.h"
GameData* GameData::instance = 0;
vector<vector<int>> GameData::gameData(ROW, vector<int>(COL));

GameData::GameData()
{
	for (int y = ROW - 3; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
			gameData[y][x] = rand() % 6;
		//避免出现一行初始情况就全满
		gameData[y][rand() % COL] = 0;
		gameData[y][rand() % COL] = 0;
		gameData[y][rand() % COL] = 0;
	}
}

GameData* GameData::getGameData()
{
	if (instance == 0)
		instance = new GameData();
	return instance;
}

