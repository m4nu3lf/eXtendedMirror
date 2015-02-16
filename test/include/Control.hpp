#include<string>
#include<XM/ExtendedMirror.hpp>

class Control
{
public:
	std::string name;
	virtual void onMouseClick() = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseExit() = 0;
};

XM_ASSUME_ABSTRACT(Control);
XM_ENABLE_CLASS(Control);

