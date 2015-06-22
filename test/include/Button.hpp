#include <XM/xMirror.hpp>
#include <Rectangle.hpp>
#include <Control.hpp>

class Button : public Rectangle, public Control
{
public:
	Button(int x = 0, int y = 0, int w = 0, int h = 0);
    virtual ~Button();
};

XM_ASSUME_ABSTRACT(Button);
XM_DECLARE_CLASS(Button);

