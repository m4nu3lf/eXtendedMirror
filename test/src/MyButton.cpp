#include <MyButton.hpp>

MyButton::MyButton(int x, int y, int w, int h)
	: Button(x, y, w, h)
{
}

void MyButton::onMouseClick()
{
	mouseClicks ++;
}

void MyButton::onMouseEnter()
{
	mouseOver = true;
}

void MyButton::onMouseExit()
{
	mouseOver = false;
}

unsigned int MyButton::getClickCount() 
{
	return mouseClicks;
}

bool MyButton::isMouseOver()
{
	return mouseOver;
}

XM_BUILD_CLASS(MyButton)
{

}

XM_AUTOREG(MyButton);

