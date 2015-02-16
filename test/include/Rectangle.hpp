#include "Shape.hpp"
#include <XM/xMirror.hpp>

class Rectangle: public Shape
{
public:
	Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);	
	int getWidth();
	void setWidth(int width);

	int getHeight();
	void setHeight(int height);

private:
	int width, height;
};

XM_ENABLE_CLASS(Rectangle);

