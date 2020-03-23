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
	//����һ��Shape
	void soildShape();
	virtual void createShape(int x, int y, int c) = 0;
	virtual void moveShapeLeft() = 0;
	virtual void moveShapeRight() = 0;
	//���䷵��true����ͻ����false
	virtual bool moveShapeDown() = 0;
	virtual void rollShape() = 0;
};

//������Shape����ʼ״̬���ϵ���Ϊ3��2��0��1
class ShapeI :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//������Shape
class ShapeO :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//L��Shape
class ShapeL :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//T��Shape
class ShapeT :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};

//Z��Shape
class ShapeZ :public AbstractShape
{
public:
	void createShape(int x, int y, int c);
	void moveShapeLeft();
	void moveShapeRight();
	bool moveShapeDown();
	void rollShape();
};