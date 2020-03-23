#include "Scene.h"


string getCookies()
{
	ifstream load_cookies("config.ini");
	//如果存在cookies，就返回
	if (load_cookies.good() == 1)
	{
		string tp;
		getline(load_cookies, tp);
		if (tp.size() == 64)
			return tp;
	}
	//如果cookies不存在就创建
	string cookies = "";
	for (int i = 0; i < 64; i++)
	{
		int tp = rand() % 36;

		if (tp > 9)
			tp += ('a' - 10);
		else
			tp += '0';
		char c = tp;
		cookies += c;
	}
	ofstream save("config.ini");
	//保存到文件
	save << cookies;
	save.close();
	return cookies;
}

void Scene::showScene() {}
int Scene::getNextScene() { return scene_seq; }

void Scene::clearScene()
{
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 2; j < COL * 2 + 1; j++)
			printText(j, i, 0, "  ");
	}
}

void Scene::getServerSaveData()
{
	//调用Client读取数据
	Client c;
	c.setIPAddressAndPort(IP_ADDRESS, PORT);
	//客户端读取数据，发送cookies，返回存档数据
	c.saveandloadSaveData(LOAD, getCookies());
	for (int i = 0; i < 3; i++)
	{
		printText(4, 3 + 4 * i, Cyan, "┏━━━━━━━━━━━━━━━━━┓");
		printText(4, 4 + 4 * i, Cyan, "┃                 ┃");
		printText(4, 5 + 4 * i, Cyan, "┃                 ┃");
		printText(4, 6 + 4 * i, Cyan, "┗━━━━━━━━━━━━━━━━━┛");
		
		if (SaveDataSet::getSet()->getSaveData(i).isEmpty() == true)
			printText(COL - 2, 4 + 4 * i, Cyan, "空的存档");
		else
		{
			//打印得分
			printText(6, 4 + 4 * i, Cyan, "Score:" + to_string(SaveDataSet::getSet()->getSaveData(i).getScore()));
			//打印时间戳
			printText(6, 5 + 4 * i, Cyan, SaveDataSet::getSet()->getSaveData(i).getTimeStamp());
		}
	}
	printText(2, 4, Cyan, "→");
}

void Game::printGameData()
{	
	//打印游戏数据
	int tp = max(op.readBlockTop() - 1, 0);
	for (int y = tp; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			int color = op.readGameData(x, y);
			if (color != 0)
				printOneBlock(x, y, color);
			else
				clearOneBlock(x, y);
		}
	}
	printText(2 * COL + 10, 3, Cyan, "        ");
	printText(2 * COL + 10, 3, Cyan, to_string(op.readScore()));
	printText(2 * COL + 4, 3, Cyan, "Score:");
}

void Start::showScene()
{
	//0开始游戏，1读取进度，2退出游戏
	int mode = 0;
	printText(COL - 3, 2, Cyan, "俄罗斯方块");
	printText(COL - 2, 6, Cyan, "开始游戏");
	printText(COL - 2, 8, Cyan, "读取存档");
	printText(COL - 2, 10, Cyan, "退出游戏");
	printText(COL - 4, 6, Cyan, "→");
	int ch = 0;
	//按键不为ENTER	SPACE时
	while (ch != ENTER && ch != SPACE)
	{
		//如果有按键按下，则_kbhit()函数返回真
		if (_kbhit())
		{
			//使用_getch()函数获取按下的键值
			ch = _getch();
			printText(COL - 4, 6 + mode * 2, 0, "  ");
			switch (ch)
			{
			case UP:
			{
				mode = (mode + 2) % 3;
				break;
			}
			case DOWN:
			{
				mode = (mode + 1) % 3;
				break;
			}
			case ESC:
			{
				scene_seq = QUIT;
				return;
			}
			}
			printText(COL - 4, 6 + mode * 2, Cyan, "→");
		}
	}
	clearScene();
	//开始游戏
	if (mode == 0)
		scene_seq = GAME_SCENE;
	//读取进度
	else if (mode == 1)
		scene_seq = LOAD_SCENE;
	//退出游戏
	else
		scene_seq = QUIT;
}

void Game::showScene()
{
	//如果是新游戏
	if (op.readIsNewGame() == true)
	{
		op.createNewGameData();
		op.resetIsNewGame(false);
	}
	//打印游戏数据
	printGameData();
	//创建简单工厂
	SimpleShapeFactory factory;
	//当前的块
	AbstractShape* current_shape = NULL;
	//下一个块
	AbstractShape* next_shape = NULL;
	//先初始化一个块，用作下一个块
	next_shape = factory.getShapeFromFactory();
	//初始化第一个块的颜色
	int shapecolor= rand() % 5 + 1;
	//循环条件：没有GameOver
	while (op.readBlockTop() > 0)
	{
		//当前块=下个块
		current_shape = next_shape;
		//从简单工厂得到下一个块 
		next_shape = factory.getShapeFromFactory();
		//创建块
		current_shape->createShape(rand() % 6 + 3, -3, shapecolor);
		//设定下个块的颜色
		shapecolor = rand() % 5 + 1;
		//在特定区域显示下一个块
		next_shape->createShape(COL + 4, 13, shapecolor);
		printText(2*COL + 8, 10,Cyan, "Next");
		//flag用来判断块是否下落时固定
		bool flag = true;
		//用于计算块下落速率
		int fresh_time = 0;
		//循环条件：块没有被固定
		while (flag != false)
		{
			if (_kbhit())//如果有按键按下，则_kbhit()函数返回真
			{
				switch (_getch())//使用_getch()函数获取按下的键值
				{
				case UP:
					current_shape->rollShape();
					break;
				case DOWN:
					flag = current_shape->moveShapeDown();
					break;
				case LEFT:
					current_shape->moveShapeLeft();
					break;
				case RIGHT:
					current_shape->moveShapeRight();
					break;
				case ENTER:case SPACE:case ESC://暂停游戏
					Scene* pause = new Pause;
					pause->showScene();
					//=GAME_SCENE表示进入暂停界面后返回游戏界面
					if (pause->getNextScene() == SAVE_SCENE)
					{
						printGameData();
						current_shape->moveShapeDown();
					}
					else if (pause->getNextScene() == LOAD_SCENE)
					{
						printGameData();
						flag = false;
					}
					else if (pause->getNextScene() == QUIT)
					{
						scene_seq = QUIT;
						return;
					}
					break;
				}
			}
			if (fresh_time == 0)
				flag = current_shape->moveShapeDown();
			Sleep(50);
			fresh_time = (fresh_time + 1) % (12 / op.readGameSpeed());
		}
		//打印当前数据
		printGameData();
		//删除当前块
		delete current_shape;
		for (int x = COL + 1; x < COL + 8; x++)
		{
			for (int y = 8; y < 15; y++)
				clearOneBlock(x, y);
		}
		
	}
	//删除原有数据
	op.createNewGameData();
	Scene* go = new GameOver;
	//进入GameOver界面
	go->showScene();
	//获得下一个界面的序号
	scene_seq = go->getNextScene();
}

void Pause::showScene()
{
	//Pause界面是Game界面的子界面
	int mode = 0;
	printText(COL - 6, 4, Cyan, "┏━━━━━━━━━━━━━┓");
	printText(COL - 6, 5, Cyan, "┃             ┃");
	printText(COL - 6, 6, Cyan, "┃             ┃");
	printText(COL - 6, 7, Cyan, "┃             ┃");
	printText(COL - 6, 8, Cyan, "┃             ┃");
	printText(COL - 6, 9, Cyan, "┗━━━━━━━━━━━━━┛");
	printText(COL - 4, 5, Cyan, "→");
	printText(COL - 2, 5, Cyan, "继续游戏");
	printText(COL - 2, 6, Cyan, "保存游戏");
	printText(COL - 2, 7, Cyan, "读取存档");
	printText(COL - 2, 8, Cyan, "退出游戏");
	int ch = 0;
	//按键不为Enter	Space时
	while (ch != ENTER && ch != SPACE)
	{
		//如果有按键按下，则_kbhit()函数返回真
		if (_kbhit())
		{
			//使用_getch()函数获取按下的键值
			ch = _getch();
			printText(COL - 4, 5 + mode, Cyan, "  ");
			if (ch == UP)
				mode = (mode + 3) % 4;
			else if (ch == DOWN)
				mode = (mode + 1) % 4;
			else if (ch == ESC)
			{
				mode = 0;
				break;
			}
			else if (ch == ENTER || ch == SPACE)
				break;
			printText(COL - 4, 5 + mode, Cyan, "→");
		}
	}
	clearScene();
	//退出游戏
	if (mode == 3)
	{
		scene_seq = QUIT;
		return;
	}
	if (mode == 0)
	{
		scene_seq = GAME_SCENE;
	}
	//保存游戏
	else if (mode == 1)
	{
		Save* s = new Save;
		s->showScene();
		scene_seq = SAVE_SCENE;
	}
	//读取存档
	else if (mode == 2)
	{
		Load* l = new Load;
		l->showScene();
		scene_seq = LOAD_SCENE;
	}	
}

void Load::showScene()
{
	printText(COL - 2, 2, Cyan, "读取游戏");
	getServerSaveData();
	int savedata_seq = 0;
	int ch = 0;
	//按键不为Enter	Space时
	while (ch != ENTER && ch != SPACE)
	{
		//如果有按键按下，则_kbhit()函数返回真
		if (_kbhit())
		{
			//使用_getch()函数获取按下的键值
			ch = _getch();
			printText(2, 4 + 4 * savedata_seq, Cyan, "  ");
			switch (ch)
			{
			case UP:
				savedata_seq = (savedata_seq + 2) % 3;
				break;
			case DOWN:
				savedata_seq = (savedata_seq + 1) % 3;
				break;
			case ESC://返回游戏
				clearScene();
				scene_seq = GAME_SCENE;
				return;
			}
			printText(2, 4 + 4 * savedata_seq, Cyan, "→");
		}
	}
	//如果存档不为空
	if (SaveDataSet::getSet()->getSaveData(savedata_seq).isEmpty() == false)
	{	
		op.createNewGameData();
		//转换存档中的数据为game_data
		string s = SaveDataSet::getSet()->getSaveData(savedata_seq).getData();
		for (int y = 0; y < ROW; y++)
		{
			for (int x = 0; x < COL; x++)
				op.writeGameData(x, y, stoi(s.substr(y * COL + x, 1)));
		}
		//获取存档中的分数
		op.resetScore(SaveDataSet::getSet()->getSaveData(savedata_seq).getScore());
		//设定速率和得分率
		op.updateSpeedAndRate();
		//设定为非新游戏
		op.resetIsNewGame(false);
	}
	scene_seq = GAME_SCENE;
	clearScene();
}

void Save::showScene()
{
	//调用Client读取数据
	getServerSaveData();
	printText(COL - 2, 2, Cyan, "保存游戏");
	int savedata_seq = 0;
	int ch = 0;
	//按键不为Enter	Space时
	while (ch != ENTER && ch != SPACE)
	{
		//如果有按键按下，则_kbhit()函数返回真
		if (_kbhit())
		{
			//使用_getch()函数获取按下的键值
			ch = _getch();
			printText(2, 4 + 4 * savedata_seq, Cyan, "  ");
			switch (ch)
			{
			case UP:
				savedata_seq = (savedata_seq + 2) % 3;
				break;
			case DOWN:
				savedata_seq = (savedata_seq + 1) % 3;
				break;
			case ESC:
				clearScene();
				scene_seq = GAME_SCENE;
				return;
			}
			printText(2, 4 + 4 * savedata_seq, Cyan, "→");
		}
	}
	//获取时间戳
	struct tm t;//tm结构指针
	time_t now;//声明time_t类型变量
	time(&now);//获取系统日期和时间
	localtime_s(&t, &now);//获取当地日期和时间
	//格式化输出本地时间
	string timestamp = to_string(t.tm_year + 1900) + "/";
	if (t.tm_mon + 1 < 10)
		timestamp += "0";
	timestamp += to_string(t.tm_mon + 1) + "/";
	if (t.tm_mday < 10)
		timestamp += "0";
	timestamp += to_string(t.tm_mday) + " ";
	if (t.tm_hour < 10)
		timestamp += "0";
	timestamp += to_string(t.tm_hour) + ":";
	if (t.tm_min < 10)
		timestamp += "0";
	timestamp += to_string(t.tm_min);
	//Cookies
	string tp = getCookies();
	//存档序号
	tp += to_string(savedata_seq);
	//时间戳
	tp += timestamp;
	//游戏数据	
	string data = "";
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
			data += to_string(op.readGameData(x, y));
	}
	tp += data;
	//得分	
	tp += to_string(op.readScore());
	//客户端保存数据
	Client c;
	c.setIPAddressAndPort(IP_ADDRESS, PORT);
	//发送存档给服务器
	c.saveandloadSaveData(SAVE, tp);
	//清屏
	clearScene();
	scene_seq = GAME_SCENE;
}

void GameOver::showScene()
{
	int mode = 0;
	printText(COL - 6, 4, Cyan, "┏━━━━━━━━━━━━━┓");
	printText(COL - 6, 5, Cyan, "┃             ┃");
	printText(COL - 6, 6, Cyan, "┃             ┃");
	printText(COL - 6, 7, Cyan, "┃             ┃");
	printText(COL - 6, 8, Cyan, "┗━━━━━━━━━━━━━┛");
	printText(COL - 4, 5, Cyan, "→");
	printText(COL - 2, 5, Cyan, "重新开始");
	printText(COL - 2, 6, Cyan, "读取存档");
	printText(COL - 2, 7, Cyan, "退出游戏");
	int ch = 0;
	while (1)
	{
		//如果有按键按下，则_kbhit()函数返回真
		if (_kbhit())
		{
			//使用_getch()函数获取按下的键值
			ch = _getch();
			printText(COL - 4, 5 + mode, Cyan, "  ");
			if (ch == UP)
				mode = (mode + 2) % 3;
			else if (ch == DOWN)
				mode = (mode + 1) % 3;
			else if (ch == ESC)
			{
				mode = -1;
				break;
			}
			else if (ch == ENTER || ch == SPACE)
				break;
			printText(COL - 4, 5 + mode, Cyan, "→");
		}
	}
	clearScene();
	if (mode == 0)
		scene_seq = GAME_SCENE;
	else if (mode == 1)
		scene_seq = LOAD_SCENE;
	else
		scene_seq = QUIT;
}

void Background::showScene()
{
	for (int y = 0; y < ROW + 2; y++)
	{
		for (int x = 0; x < 2 * COL - 2; x++)
			if (y == 0 || y == ROW + 1 || x == 0
				|| x == COL + 1 || x == 2 * COL - 3)
				printText(2 * x, y, Cyan, "█");
	}
	printText(2 * COL + 6, 5, Cyan, "↑:W  ↓:S");
	printText(2 * COL + 6, 6, Cyan, "←:A  →:D");
	printText(2 * COL + 6, 7, Cyan, "Enter/Space");
	printText(2 * COL + 6, 8, Cyan, "Esc");
}