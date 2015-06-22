#include <XM/xMirror.hpp>
#include <Button.hpp>

class MyButton : public Button
{
public:
	MyButton(int x = 0, int y = 0, int w = 0, int h = 0);
	void onMouseClick();
    void onMouseClick(int x, int y);
	void onMouseEnter();
	void onMouseExit();
	unsigned int getClickCount();
	bool isMouseOver();
    virtual ~MyButton();
private:
	unsigned int mouseClicks;
	bool mouseOver;
};

XM_DECLARE_CLASS(MyButton);
