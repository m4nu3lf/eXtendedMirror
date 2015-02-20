#include <Control.hpp>

XM_DEFINE_CLASS(Control)
{
    bindProperty(XM_MNP(name));
	bindMethod(XM_MNP(onMouseClick));
	bindMethod(XM_MNP(onMouseEnter));
	bindMethod(XM_MNP(onMouseExit));
}
