#pragma once
#include "Printer.h"
#include "SimpleShapeFactory.h"
#include "GameDataOperator.h"
#include "SaveData.h"
#include "Client.h"
#include "conio.h"
#include <time.h>

enum Key
{
	Cyan = 11,//��ɫ
	SPACE = 32, ESC = 27, ENTER = 13,
	UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd',
	SAVE = 0, LOAD = 1,
	START_SCENE = 0, GAME_SCENE = 1, PAUSE_SCENE = 2, 
	LOAD_SCENE = 3, SAVE_SCENE = 4,QUIT=-1
};

class Scene:protected Printer
{
protected:
	//=0����ʼ��1����Ϸ��2����ͣ��3����ȡ��4�����棬-1���˳�
	int scene_seq = 0;
	//�������
	void clearScene();
	//�ӷ������˶�ȡ����
	void getServerSaveData();
	GameDataOperator op;
public:
	virtual void showScene();
	int getNextScene();	
};

class Start :public Scene
{
public:
	void showScene();
};

class Game :public Scene
{
private:
	void printGameData();
public:
	void showScene();
};

class Pause :public Scene
{
public:
	void showScene();
};

class Load :public Scene
{
public:
	void showScene();
};

class Save :public Scene
{
public:
	void showScene();
};

class GameOver :public Scene
{
public:
	void showScene();
};

class Background :public Scene
{
public:
	void showScene();
};