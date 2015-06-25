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
	unsigned int getClickCount() const;
	bool isMouseOver();
    int getClickX() const;
    int getClickY() const;
    virtual ~MyButton();
private:
	unsigned int mouseClicks;
	bool mouseOver;
    int clickX;
    int clickY;
};

XM_DECLARE_CLASS(MyButton);
