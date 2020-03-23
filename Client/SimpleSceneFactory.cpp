#include "SimpleSceneFactory.h"

Scene* SimpleSceneFactory::createScene(int seq)
{
	//=0����ʼ��1����Ϸ��2����ͣ��3����ȡ��4������
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