#pragma once
#include "Block.h"
#include "GameDataOperator.h"
class AbstractShape
{
protected:
	Block b0, b1, b2, b3;
	int status = 0;
	GameDataOperator op;
public:
	//创建一个Shape
	void soildShape();
	virtual void createShape(int x, int y, int c) = 0;
	virtual void moveShapeLeft() = 0;
	virtual void moveShapeRight() = 0;
	//下落返回true，冲突返回false
	virtual bool moveShapeDown() = 0;
	virtual void rollShape() = 0;
};

//长条形Shape，初始状态从上到下为3、2、0、1
class ShapeI :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//正方形Shape
class ShapeO :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//L形Shape
class ShapeL :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//T形Shape
class ShapeT :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//Z形Shape
class ShapeZ :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};