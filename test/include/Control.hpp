#include<string>
#include<XM/xMirror.hpp>

class Control
{
public:
    char* name;
	virtual void onMouseClick() = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseExit() = 0;
};

XM_ASSUME_ABSTRACT(Control);
XM_DECLARE_CLASS(Control);

