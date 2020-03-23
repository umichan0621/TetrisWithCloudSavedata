#include "SimpleShapeFactory.h"
AbstractShape* SimpleShapeFactory::getShapeFromFactory()
{
	int ran = rand() % 5;
	if(ran==0)
		return new ShapeL;
	else if(ran==1)
		return  new ShapeO;
	else if (ran == 2)
		return  new ShapeI;
	else if (ran == 3)
		return  new ShapeT;
	else
		return  new ShapeZ;

}