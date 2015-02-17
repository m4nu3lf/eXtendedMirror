#include <Control.hpp>

XM_BUILD_CLASS(Control)
{
    bindProperty(XM_MNP(name));
	bindMethod(XM_MNP(onMouseClick));
	bindMethod(XM_MNP(onMouseEnter));
	bindMethod(XM_MNP(onMouseExit));
}
