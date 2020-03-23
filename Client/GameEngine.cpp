#include "SimpleSceneFactory.h"
int main()
{

	Scene *s=new Background;
	s->showScene();
	SimpleSceneFactory factory;
	while (s->getNextScene() != -1)
	{
		s = factory.createScene(s->getNextScene());
		s->showScene();
	}
	

}