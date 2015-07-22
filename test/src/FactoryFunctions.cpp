#include <FactoryFunctions.hpp>
#include <XM/xMirror.hpp>

Button* dgui_factories::makeButton(int x, int y, int width, int height)
{
    return new MyButton(x, y, width, height);
}

XM_BIND_FREE_ITEMS
{
    XM_BIND_FUNCTION(::dgui_factories::makeButton);
}
