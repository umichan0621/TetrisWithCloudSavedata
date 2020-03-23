#include "Scene.h"


string getCookies()
{
	ifstream load_cookies("config.ini");
	//�������cookies���ͷ���
	if (load_cookies.good() == 1)
	{
		string tp;
		getline(load_cookies, tp);
		if (tp.size() == 64)
			return tp;
	}
	//���cookies�����ھʹ���
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
	//���浽�ļ�
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
	//����Client��ȡ����
	Client c;
	c.setIPAddressAndPort(IP_ADDRESS, PORT);
	//�ͻ��˶�ȡ���ݣ�����cookies�����ش浵����
	c.saveandloadSaveData(LOAD, getCookies());
	for (int i = 0; i < 3; i++)
	{
		printText(4, 3 + 4 * i, Cyan, "��������������������������������������");
		printText(4, 4 + 4 * i, Cyan, "��                 ��");
		printText(4, 5 + 4 * i, Cyan, "��                 ��");
		printText(4, 6 + 4 * i, Cyan, "��������������������������������������");
		
		if (SaveDataSet::getSet()->getSaveData(i).isEmpty() == true)
			printText(COL - 2, 4 + 4 * i, Cyan, "�յĴ浵");
		else
		{
			//��ӡ�÷�
			printText(6, 4 + 4 * i, Cyan, "Score:" + to_string(SaveDataSet::getSet()->getSaveData(i).getScore()));
			//��ӡʱ���
			printText(6, 5 + 4 * i, Cyan, SaveDataSet::getSet()->getSaveData(i).getTimeStamp());
		}
	}
	printText(2, 4, Cyan, "��");
}

void Game::printGameData()
{	
	//��ӡ��Ϸ����
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
	//0��ʼ��Ϸ��1��ȡ���ȣ�2�˳���Ϸ
	int mode = 0;
	printText(COL - 3, 2, Cyan, "����˹����");
	printText(COL - 2, 6, Cyan, "��ʼ��Ϸ");
	printText(COL - 2, 8, Cyan, "��ȡ�浵");
	printText(COL - 2, 10, Cyan, "�˳���Ϸ");
	printText(COL - 4, 6, Cyan, "��");
	int ch = 0;
	//������ΪENTER	SPACEʱ
	while (ch != ENTER && ch != SPACE)
	{
		//����а������£���_kbhit()����������
		if (_kbhit())
		{
			//ʹ��_getch()������ȡ���µļ�ֵ
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
			printText(COL - 4, 6 + mode * 2, Cyan, "��");
		}
	}
	clearScene();
	//��ʼ��Ϸ
	if (mode == 0)
		scene_seq = GAME_SCENE;
	//��ȡ����
	else if (mode == 1)
		scene_seq = LOAD_SCENE;
	//�˳���Ϸ
	else
		scene_seq = QUIT;
}

void Game::showScene()
{
	//���������Ϸ
	if (op.readIsNewGame() == true)
	{
		op.createNewGameData();
		op.resetIsNewGame(false);
	}
	//��ӡ��Ϸ����
	printGameData();
	//�����򵥹���
	SimpleShapeFactory factory;
	//��ǰ�Ŀ�
	AbstractShape* current_shape = NULL;
	//��һ����
	AbstractShape* next_shape = NULL;
	//�ȳ�ʼ��һ���飬������һ����
	next_shape = factory.getShapeFromFactory();
	//��ʼ����һ�������ɫ
	int shapecolor= rand() % 5 + 1;
	//ѭ��������û��GameOver
	while (op.readBlockTop() > 0)
	{
		//��ǰ��=�¸���
		current_shape = next_shape;
		//�Ӽ򵥹����õ���һ���� 
		next_shape = factory.getShapeFromFactory();
		//������
		current_shape->createShape(rand() % 6 + 3, -3, shapecolor);
		//�趨�¸������ɫ
		shapecolor = rand() % 5 + 1;
		//���ض�������ʾ��һ����
		next_shape->createShape(COL + 4, 13, shapecolor);
		printText(2*COL + 8, 10,Cyan, "Next");
		//flag�����жϿ��Ƿ�����ʱ�̶�
		bool flag = true;
		//���ڼ������������
		int fresh_time = 0;
		//ѭ����������û�б��̶�
		while (flag != false)
		{
			if (_kbhit())//����а������£���_kbhit()����������
			{
				switch (_getch())//ʹ��_getch()������ȡ���µļ�ֵ
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
				case ENTER:case SPACE:case ESC://��ͣ��Ϸ
					Scene* pause = new Pause;
					pause->showScene();
					//=GAME_SCENE��ʾ������ͣ����󷵻���Ϸ����
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
		//��ӡ��ǰ����
		printGameData();
		//ɾ����ǰ��
		delete current_shape;
		for (int x = COL + 1; x < COL + 8; x++)
		{
			for (int y = 8; y < 15; y++)
				clearOneBlock(x, y);
		}
		
	}
	//ɾ��ԭ������
	op.createNewGameData();
	Scene* go = new GameOver;
	//����GameOver����
	go->showScene();
	//�����һ����������
	scene_seq = go->getNextScene();
}

void Pause::showScene()
{
	//Pause������Game������ӽ���
	int mode = 0;
	printText(COL - 6, 4, Cyan, "������������������������������");
	printText(COL - 6, 5, Cyan, "��             ��");
	printText(COL - 6, 6, Cyan, "��             ��");
	printText(COL - 6, 7, Cyan, "��             ��");
	printText(COL - 6, 8, Cyan, "��             ��");
	printText(COL - 6, 9, Cyan, "������������������������������");
	printText(COL - 4, 5, Cyan, "��");
	printText(COL - 2, 5, Cyan, "������Ϸ");
	printText(COL - 2, 6, Cyan, "������Ϸ");
	printText(COL - 2, 7, Cyan, "��ȡ�浵");
	printText(COL - 2, 8, Cyan, "�˳���Ϸ");
	int ch = 0;
	//������ΪEnter	Spaceʱ
	while (ch != ENTER && ch != SPACE)
	{
		//����а������£���_kbhit()����������
		if (_kbhit())
		{
			//ʹ��_getch()������ȡ���µļ�ֵ
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
			printText(COL - 4, 5 + mode, Cyan, "��");
		}
	}
	clearScene();
	//�˳���Ϸ
	if (mode == 3)
	{
		scene_seq = QUIT;
		return;
	}
	if (mode == 0)
	{
		scene_seq = GAME_SCENE;
	}
	//������Ϸ
	else if (mode == 1)
	{
		Save* s = new Save;
		s->showScene();
		scene_seq = SAVE_SCENE;
	}
	//��ȡ�浵
	else if (mode == 2)
	{
		Load* l = new Load;
		l->showScene();
		scene_seq = LOAD_SCENE;
	}	
}

void Load::showScene()
{
	printText(COL - 2, 2, Cyan, "��ȡ��Ϸ");
	getServerSaveData();
	int savedata_seq = 0;
	int ch = 0;
	//������ΪEnter	Spaceʱ
	while (ch != ENTER && ch != SPACE)
	{
		//����а������£���_kbhit()����������
		if (_kbhit())
		{
			//ʹ��_getch()������ȡ���µļ�ֵ
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
			case ESC://������Ϸ
				clearScene();
				scene_seq = GAME_SCENE;
				return;
			}
			printText(2, 4 + 4 * savedata_seq, Cyan, "��");
		}
	}
	//����浵��Ϊ��
	if (SaveDataSet::getSet()->getSaveData(savedata_seq).isEmpty() == false)
	{	
		op.createNewGameData();
		//ת���浵�е�����Ϊgame_data
		string s = SaveDataSet::getSet()->getSaveData(savedata_seq).getData();
		for (int y = 0; y < ROW; y++)
		{
			for (int x = 0; x < COL; x++)
				op.writeGameData(x, y, stoi(s.substr(y * COL + x, 1)));
		}
		//��ȡ�浵�еķ���
		op.resetScore(SaveDataSet::getSet()->getSaveData(savedata_seq).getScore());
		//�趨���ʺ͵÷���
		op.updateSpeedAndRate();
		//�趨Ϊ������Ϸ
		op.resetIsNewGame(false);
	}
	scene_seq = GAME_SCENE;
	clearScene();
}

void Save::showScene()
{
	//����Client��ȡ����
	getServerSaveData();
	printText(COL - 2, 2, Cyan, "������Ϸ");
	int savedata_seq = 0;
	int ch = 0;
	//������ΪEnter	Spaceʱ
	while (ch != ENTER && ch != SPACE)
	{
		//����а������£���_kbhit()����������
		if (_kbhit())
		{
			//ʹ��_getch()������ȡ���µļ�ֵ
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
			printText(2, 4 + 4 * savedata_seq, Cyan, "��");
		}
	}
	//��ȡʱ���
	struct tm t;//tm�ṹָ��
	time_t now;//����time_t���ͱ���
	time(&now);//��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);//��ȡ�������ں�ʱ��
	//��ʽ���������ʱ��
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
	//�浵���
	tp += to_string(savedata_seq);
	//ʱ���
	tp += timestamp;
	//��Ϸ����	
	string data = "";
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
			data += to_string(op.readGameData(x, y));
	}
	tp += data;
	//�÷�	
	tp += to_string(op.readScore());
	//�ͻ��˱�������
	Client c;
	c.setIPAddressAndPort(IP_ADDRESS, PORT);
	//���ʹ浵��������
	c.saveandloadSaveData(SAVE, tp);
	//����
	clearScene();
	scene_seq = GAME_SCENE;
}

void GameOver::showScene()
{
	int mode = 0;
	printText(COL - 6, 4, Cyan, "������������������������������");
	printText(COL - 6, 5, Cyan, "��             ��");
	printText(COL - 6, 6, Cyan, "��             ��");
	printText(COL - 6, 7, Cyan, "��             ��");
	printText(COL - 6, 8, Cyan, "������������������������������");
	printText(COL - 4, 5, Cyan, "��");
	printText(COL - 2, 5, Cyan, "���¿�ʼ");
	printText(COL - 2, 6, Cyan, "��ȡ�浵");
	printText(COL - 2, 7, Cyan, "�˳���Ϸ");
	int ch = 0;
	while (1)
	{
		//����а������£���_kbhit()����������
		if (_kbhit())
		{
			//ʹ��_getch()������ȡ���µļ�ֵ
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
			printText(COL - 4, 5 + mode, Cyan, "��");
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
				printText(2 * x, y, Cyan, "��");
	}
	printText(2 * COL + 6, 5, Cyan, "��:W  ��:S");
	printText(2 * COL + 6, 6, Cyan, "��:A  ��:D");
	printText(2 * COL + 6, 7, Cyan, "Enter/Space");
	printText(2 * COL + 6, 8, Cyan, "Esc");
}