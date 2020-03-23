#include "SimpleSceneFactory.h"

Scene* SimpleSceneFactory::createScene(int seq)
{
	//=0：开始，1：游戏，2：暂停，3：读取，4：保存
	Scene* s = new Scene;
	if (seq == 0)
		s = new Start;
	else if (seq == 1)
		s = new Game;
	else if (seq == 2)
		s = new Pause;
	else if (seq == 3)
		s = new Load;
	else if (seq == 4)
		s = new Save;
	return s;
}