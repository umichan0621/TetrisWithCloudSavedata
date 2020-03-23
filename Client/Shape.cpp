#include "Shape.h"

bool clearOneRow(int y, GameDataOperator op)
{
	if (y < 0)
		return false;
	for (int x = 0; x < COL; x++)
		if (op.readGameData(x, y) == 0)
			return false;
	//行移动，将行y之上所有的行向下平移一行	
	for (int i = y; i > 0; i--)//单行平移
	{
		for (int x = 0; x < COL; x++)
		{
			op.writeGameData(x, i, op.readGameData(x, i - 1));
		}
	}
	//最高行置空
	for (int x = 0; x < COL; x++)
		op.writeGameData(x, 0, 0);
	return true;
}

void plusScore(int counter, GameDataOperator op)
{
	int Temp = static_cast<int> (pow(2, counter - 1));
	op.resetScore(op.readScore() + Temp * op.readScoreRate());
}

void AbstractShape::soildShape()
{
	b0.soildBlock();
	b1.soildBlock();
	b2.soildBlock();
	b3.soildBlock();
}

void ShapeI::createShape(int x, int y, int c)
{
	b0.createBlock(x, y, c);
	b1.createBlock(x + 1, y, c);
	b2.createBlock(x - 1, y, c);
	b3.createBlock(x - 2, y, c);
	for (int i = 0; i <= rand() % 2; i++)
		this->rollShape();
}

void ShapeI::moveShapeLeft()
{
	if (status == 0)
	{
		int tp = b0.isConflict(-1, 0) + b1.isConflict(-1, 0) + b2.isConflict(-1, 0) + b3.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else
	{
		if (b1.isConflict(-1, 0) != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
}

void ShapeI::moveShapeRight()
{
	if (status == 0)
	{
		int tp = b0.isConflict(1, 0) + b1.isConflict(1, 0) + b2.isConflict(1, 0) + b3.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b3.moveBlock(1, 0);
	}
	else
	{
		if (b3.isConflict(1, 0) != 0)
			return;
		b1.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b3.moveBlock(1, 0);
	}
}

bool ShapeI::moveShapeDown()
{
	if (status == 0)
	{
		int tp = b0.isConflict(0, 1) + b1.isConflict(0, 1) + b2.isConflict(0, 1) + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			tp = clearOneRow(b0.getY(), op);//刷新顺序从上往下,tp是清除的行数
			plusScore(tp, op);
			op.resetBlockTop(min(op.readBlockTop(), b0.getY()));//维护最高点位置block_top
			return false;
		}
		b0.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
	}
	else
	{
		int tp = b1.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b3.getY(), op) + clearOneRow(b2.getY(), op)
				+ clearOneRow(b0.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			op.resetBlockTop(min(op.readBlockTop(), b3.getY()));//维护最高点位置block_top
			return false;
		}
		b1.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
	}
	return true;
}

void ShapeI::rollShape()
{
	if (status == 1)
	{
		int tp = b0.isConflict(-1, 0) + b0.isConflict(-2, 0) + b0.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, -1);
		b2.moveBlock(-1, 1);
		b3.moveBlock(-2, 2);
		status = 0;
	}
	else
	{
		if (b0.isConflict(0, 1) != 0)
			return;
		b1.moveBlock(-1, 1);
		b2.moveBlock(1, -1);
		b3.moveBlock(2, -2);
		status = 1;
	}
}

void ShapeO::createShape(int x, int y, int c)
{
	b0.createBlock(x, y, c);
	b1.createBlock(x - 1, y, c);
	b2.createBlock(x - 1, y + 1, c);
	b3.createBlock(x, y + 1, c);
}

void ShapeO::moveShapeLeft()
{
	int tp = b0.isConflict(-1, 0) + b1.isConflict(-1, 0);
	if (tp != 0)
		return;
	b2.moveBlock(-1, 0);
	b1.moveBlock(-1, 0);
	b0.moveBlock(-1, 0);
	b3.moveBlock(-1, 0);
}

void ShapeO::moveShapeRight()
{
	int tp = b2.isConflict(1, 0) + b3.isConflict(1, 0);
	if (tp != 0)
		return;
	b3.moveBlock(1, 0);
	b0.moveBlock(1, 0);
	b2.moveBlock(1, 0);
	b1.moveBlock(1, 0);
}

bool ShapeO::moveShapeDown()
{
	GameDataOperator op;
	int tp = b2.isConflict(0, 1) + b3.isConflict(0, 1);
	//冲突
	if (tp != 0)
	{
		soildShape();//固定块
		//刷新顺序从上往下,tp是清除的行数
		tp = clearOneRow(b1.getY(), op) + clearOneRow(b2.getY(), op);
		plusScore(tp, op);
		//维护最高点位置block_top
		op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
		return false;
	}
	b2.moveBlock(0, 1);
	b3.moveBlock(0, 1);
	b1.moveBlock(0, 1);
	b0.moveBlock(0, 1);
	return true;
}

void ShapeO::rollShape() {}

void ShapeL::createShape(int x, int y, int c)
{
	b0.createBlock(x, y, c);
	b1.createBlock(x - 1, y, c);
	b2.createBlock(x + 1, y, c);
	b3.createBlock(x + 1, y + 1, c);
	for (int i = 0; i <= rand() % 4; i++)
		rollShape();
}

void ShapeL::moveShapeLeft()
{
	int tp;
	if (status == 0)
	{
		tp = b1.isConflict(-1, 0) + b3.isConflict(-1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
	else if (status == 1)
	{
		tp = b3.isConflict(-1, 0) + b0.isConflict(-1, 0) + b1.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 2)
	{
		tp = b3.isConflict(-1, 0) + b2.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 3)
	{
		tp = b1.isConflict(-1, 0) + b0.isConflict(-1, 0) + b2.isConflict(-1, 0);
		if ( tp!= 0)
			return;
		b1.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
}

void ShapeL::moveShapeRight()
{
	int tp;
	if (status == 0)
	{
		tp = b3.isConflict(1, 0) + b2.isConflict(1, 0);
		if ( tp!= 0)
			return;
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b1.moveBlock(1, 0);
	}
	else if (status == 1)
	{
		tp = b1.isConflict(1, 0) + b0.isConflict(1, 0) + b2.isConflict(1, 0);
		if ( tp!= 0)
			return;
		b1.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b3.moveBlock(1, 0);
	}
	else if (status == 2)
	{
		tp = b1.isConflict(1, 0) + b3.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b3.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
	}
	else if (status == 3)
	{
		tp = b3.isConflict(1, 0) + b0.isConflict(1, 0) + b1.isConflict(1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b1.moveBlock(1, 0);
	}
}

bool ShapeL::moveShapeDown()
{
	if (status == 0)
	{
		int tp = b0.isConflict(0, 1) + b1.isConflict(0, 1)+ b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b1.getY(), op) + clearOneRow(b3.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b3.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 1)
	{
		int tp = b3.isConflict(0, 1) + b2.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b1.getY(), op) + clearOneRow(b0.getY(), op) + clearOneRow(b3.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b3.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 2)
	{
		int tp = b1.isConflict(0, 1) + b0.isConflict(0, 1)+b2.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b3.getY(), op) + clearOneRow(b2.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b3.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		return true;
	}
	else if (status == 3)
	{
		int tp = b1.isConflict(0, 1) + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b2.getY(), op) + clearOneRow(b0.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b3.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		return true;
	}
	return true;
}

void ShapeL::rollShape()
{
	if (status == 0)
	{
		int tp = b0.isConflict(0, 2) + b3.isConflict(0, 1);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 1);
		b2.moveBlock(0, 2);
		b0.moveBlock(1, 1);
		b1.moveBlock(2, 0);
		status++;
	}
	else if (status == 1)
	{
		int tp = b3.isConflict(-1, 0) + b0.isConflict(-2, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, -1);
		b2.moveBlock(-2, 0);
		b0.moveBlock(-1, 1);
		b1.moveBlock(0, 2);
		status++;
	}
	else if (status == 2)
	{
		int tp = b3.isConflict(0, -1) + b3.isConflict(1, -1);
		if (tp != 0)
			return;
		b3.moveBlock(1, -1);
		b2.moveBlock(0, -2);
		b0.moveBlock(-1, -1);
		b1.moveBlock(-2, 0);
		status++;
	}
	else if (status == 3)
	{
		int tp = b3.isConflict(1, 0) + b3.isConflict(1, 1);
		if (tp != 0)
			return;
		b3.moveBlock(1, 1);
		b2.moveBlock(2, 0);
		b0.moveBlock(1, -1);
		b1.moveBlock(0, -2);
		status = 0;
	}
}

void ShapeT::createShape(int x, int y, int c)
{
	b0.createBlock(x, y, c);
	b1.createBlock(x - 1, y - 1, c);
	b2.createBlock(x - 1, y, c);
	b3.createBlock(x - 1, y + 1, c);
	    for(int i=0;i<=rand()%4;i++)
			rollShape();
}

void ShapeT::moveShapeLeft()
{
	int tp;
	if (status == 0)
	{
		tp = b1.isConflict(-1, 0) + b2.isConflict(-1, 0) + b3.isConflict(-1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
	else if (status == 1)
	{
		tp = b3.isConflict(-1, 0) + b0.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 2)
	{
		tp = b3.isConflict(-1, 0) + b0.isConflict(-1, 0) + b1.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 3)
	{
		tp = b1.isConflict(-1, 0) + b0.isConflict(-1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
}

void ShapeT::moveShapeRight()
{
	int tp;
	if (status == 0)
	{
		tp = b3.isConflict(1, 0) + b0.isConflict(1, 0) + b1.isConflict(1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b1.moveBlock(1, 0);
	}
	else if (status == 1)
	{
		tp = b1.isConflict(1, 0) + b0.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b3.moveBlock(1, 0);
		b0.moveBlock(1, 0);
	}
	else if (status == 2)
	{
		tp = b1.isConflict(1, 0) +b0.isConflict(1, 0)+ b3.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b0.moveBlock(1, 0);
	}
	else if (status == 3)
	{
		tp = b3.isConflict(1, 0) + b0.isConflict(1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b1.moveBlock(1, 0);
		b0.moveBlock(1, 0);
	}
}

bool ShapeT::moveShapeDown()
{
	if (status == 0)
	{
		int tp = b0.isConflict(0, 1) + b1.isConflict(0, 1) + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b1.getY(), op) + clearOneRow(b2.getY(), op) + clearOneRow(b3.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b3.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 1)
	{
		int tp = b3.isConflict(0, 1) + b0.isConflict(0, 1) + b1.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b3.getY(), op) + clearOneRow(b0.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b0.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 2)
	{
		int tp = b1.isConflict(0, 1) + b0.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b3.getY(), op) + clearOneRow(b2.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b3.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		return true;
	}
	else if (status == 3)
	{
		int tp = b1.isConflict(0, 1) + b2.isConflict(0, 1) + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b0.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b0.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		return true;
	}
	return true;
}

void ShapeT::rollShape()
{
	if (status == 0)
	{
		int tp = b2.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, -1);
		b0.moveBlock(-1, 1);
		b1.moveBlock(1, 1);
		status++;
	}
	else if (status == 1)
	{
		int tp = b2.isConflict(0, -1);
		if (tp != 0)
			return;
		b3.moveBlock(1, -1);
		b0.moveBlock(-1, -1);
		b1.moveBlock(-1, 1);
		status++;
	}
	else if (status == 2)
	{
		int tp = b2.isConflict(1, 0) ;
		if (tp != 0)
			return;
		b3.moveBlock(1, 1);
		b0.moveBlock(1, -1);
		b1.moveBlock(-1, -1);
		status++;
	}
	else if (status == 3)
	{
		int tp = b2.isConflict(0, 1);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 1);
		b0.moveBlock(1, 1);
		b1.moveBlock(1, -1);
		status = 0;
	}
}

void ShapeZ::createShape(int x, int y, int c)
{
	b0.createBlock(x, y, c);
	b1.createBlock(x  , y - 1, c);
	b2.createBlock(x + 1, y, c);
	b3.createBlock(x+ 1, y + 1, c);
	for (int i = 0; i <= rand() % 4; i++)
		rollShape();
}

void ShapeZ::moveShapeLeft()
{
	int tp;
	if (status == 0)
	{
		tp = b1.isConflict(-1, 0) + b0.isConflict(-1, 0) + b3.isConflict(-1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
	else if (status == 1)
	{
		tp = b3.isConflict(-1, 0) + b0.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 2)
	{
		tp = b3.isConflict(-1, 0) + b2.isConflict(-1, 0) + b1.isConflict(-1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b1.moveBlock(-1, 0);
	}
	else if (status == 3)
	{
		tp = b1.isConflict(-1, 0) + b2.isConflict(-1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(-1, 0);
		b0.moveBlock(-1, 0);
		b2.moveBlock(-1, 0);
		b3.moveBlock(-1, 0);
	}
}

void ShapeZ::moveShapeRight()
{
	int tp;
	if (status == 0)
	{
		tp = b3.isConflict(1, 0) + b2.isConflict(1, 0) + b1.isConflict(1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b1.moveBlock(1, 0);
	}
	else if (status == 1)
	{
		tp = b1.isConflict(1, 0) + b2.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b3.moveBlock(1, 0);
	}
	else if (status == 2)
	{
		tp = b1.isConflict(1, 0) + b2.isConflict(1, 0) + b3.isConflict(1, 0);
		if (tp != 0)
			return;
		b1.moveBlock(1, 0);
		b3.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b2.moveBlock(1, 0);
	}
	else if (status == 3)
	{
		tp = b3.isConflict(1, 0) + b0.isConflict(1, 0);
		if (tp != 0)
			return;
		b3.moveBlock(1, 0);
		b2.moveBlock(1, 0);
		b0.moveBlock(1, 0);
		b1.moveBlock(1, 0);
	}
}

bool ShapeZ::moveShapeDown()
{
	if (status == 0)
	{
		int tp = b0.isConflict(0, 1)  + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b1.getY(), op) + clearOneRow(b2.getY(), op) + clearOneRow(b3.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b3.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 1)
	{
		int tp = b3.isConflict(0, 1) + b2.isConflict(0, 1) + b1.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b1.getY(), op) + clearOneRow(b3.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b1.getY()));
			return false;
		}
		b2.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		b1.moveBlock(0, 1);
		return true;
	}
	else if (status == 2)
	{
		int tp = b1.isConflict(0, 1) + b2.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b3.getY(), op) + clearOneRow(b2.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b3.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		return true;
	}
	else if (status == 3)
	{
		int tp = b1.isConflict(0, 1) + b0.isConflict(0, 1) + b3.isConflict(0, 1);
		//冲突
		if (tp != 0)
		{
			soildShape();//固定块
			//刷新顺序从上往下,tp是清除的行数
			tp = clearOneRow(b2.getY(), op) + clearOneRow(b1.getY(), op);
			plusScore(tp, op);
			//维护最高点位置block_top
			op.resetBlockTop(min(op.readBlockTop(), b2.getY()));
			return false;
		}
		b1.moveBlock(0, 1);
		b0.moveBlock(0, 1);
		b2.moveBlock(0, 1);
		b3.moveBlock(0, 1);
		return true;
	}
	return true;
}

void ShapeZ::rollShape()
{
	if (status == 0)
	{
		int tp = b0.isConflict(-1, 1)+ b0.isConflict(0, 1);
		if (tp != 0)
			return;
		b3.moveBlock(-2, 0);
		b2.moveBlock(-1, 1);
		b1.moveBlock(1, 1);
		status++;
	}
	else if (status == 1)
	{
		int tp = b0.isConflict(-1, -1)+ b0.isConflict(0, -1);
		if (tp != 0)
			return;
		b3.moveBlock(0, -2);
		b2.moveBlock(-1, -1);
		b1.moveBlock(-1, 1);
		status++;
	}
	else if (status == 2)
	{
		int tp = b0.isConflict(1, -1)+ b0.isConflict(0, -1);
		if (tp != 0)
			return;
		b3.moveBlock(2, 0);
		b2.moveBlock(1, -1);
		b1.moveBlock(-1, -1);
		status++;
	}
	else if (status == 3)
	{
		int tp = b0.isConflict(1, 0)+ b0.isConflict(1, 1);
		if (tp != 0)
			return;
		b3.moveBlock(0, 2);
		b2.moveBlock(1, 1);
		b1.moveBlock(1, -1);
		status = 0;
	}
}