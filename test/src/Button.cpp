# include <Button.hpp>

Button::Button(int x, int y, int w, int h)
	: Rectangle(x, y, w, h)
{
}

Button::~Button()
{
}

XM_DEFINE_CLASS(Button)
{
	XM_BIND_PBASE(Rectangle);
	XM_BIND_PBASE(Control);    
}
