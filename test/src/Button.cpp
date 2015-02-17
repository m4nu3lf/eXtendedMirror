# include <Button.hpp>

Button::Button(int x, int y, int w, int h)
	: Rectangle(x, y, w, h)
{
}

XM_BUILD_CLASS(Button)
{
	XM_BIND_PASE(Rectangle);
	XM_BIND_PASE(Control);    
}
