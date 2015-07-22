# include <Button.hpp>

const int Button::A_Const = 4;

int Button::aVar;

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

XM_BIND_FREE_ITEMS
{
    XM_BIND_CONSTANT(Button::A_Const);
    XM_BIND_VARIABLE(Button::aVar);
}
