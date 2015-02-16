#include <Shape.hpp>

using namespace xm;

Shape::Shape(int x, int y) : x(x), y(y) {}

int Shape::getX()
{
	return x;
}

void Shape::setX(int x)
{
	this->x = x;
}

int Shape::getY()
{
	return y;
}

void Shape::setY(int y)
{
	this->y = y;
}

XM_BUILD_CLASS(Shape)
{
	bindProperty("x", &ClassT::getX, &ClassT::setX);
	bindProperty("y", &ClassT::getY, &ClassT::setY);
	bindProperty("width", &ClassT::getWidth, &ClassT::setWidth);
	bindProperty("height", &ClassT::getHeight, &ClassT::setHeight);
}
