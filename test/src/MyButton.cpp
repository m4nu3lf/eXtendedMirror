#include <MyButton.hpp>

MyButton::MyButton(int x, int y, int w, int h)
	: Button(x, y, w, h), mouseClicks(0)
{
}

MyButton::~MyButton()
{
}

void MyButton::onMouseClick()
{
	mouseClicks ++;
}

void MyButton::onMouseClick(int x, int y)
{
    clickX = x;
    clickY = y;
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

unsigned int MyButton::getClickCount() const
{
	return mouseClicks;
}

int MyButton::getClickX() const
{
    return clickX;
}

int MyButton::getClickY() const
{
    return clickY;
}

bool MyButton::isMouseOver()
{
	return mouseOver;
}

XM_DEFINE_CLASS(MyButton)
{
	XM_BIND_PBASE(Button);
    bindMethod<ClassT, void, int, int>("onMouseClick", &ClassT::onMouseClick);
    bindMethod(XM_MNP(getClickCount));
	bindProperty("clickCount", &ClassT::getClickCount);
	bindProperty("isMouseOver", &ClassT::isMouseOver);
}

XM_REGISTER_TYPE(MyButton);

