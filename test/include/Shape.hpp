#include <XM/xMirror.hpp>

class Shape
{
public:
	Shape(int x = 0, int y = 0);

	int getX();
	void setX(int x);
	
	int getY();
	void setY(int y);

	virtual int getWidth() = 0;
	virtual void setWidth(int w) = 0;

	virtual int getHeight() = 0;
	virtual void  setHeight(int h) = 0;

private:
	int x, y;
};

XM_ASSUME_ABSTRACT(Shape);
XM_DECLARE_CLASS(Shape);
