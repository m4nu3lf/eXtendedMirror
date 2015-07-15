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

XM_DEFINE_CLASS(Shape)
{
	bindProperty("x", &ClassT::getX, &ClassT::setX);
	bindProperty("y", &ClassT::getY, &ClassT::setY);
	bindProperty("width", &ClassT::getWidth, &ClassT::setWidth);
	bindProperty("height", &ClassT::getHeight, &ClassT::setHeight);
}

XM_BIND_FREE_ITEMS
{
    bindEnum("Shape::Alignement")
            .addValue(XM_UNV(Shape::Center))
            .addValue(XM_UNV(Shape::Bottom))
            .addValue(XM_UNV(Shape::Left))
            .addValue(XM_UNV(Shape::Right))
            .addValue(XM_UNV(Shape::Up));
}
