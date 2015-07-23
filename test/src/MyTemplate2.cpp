#include <MyTemplate2.hpp>


XM_DEFINE_CLASS(MyTemplate2<int, int, 10>)
{
    XM_ADD_TEMPL_ARG(xm::getType<int>());
    XM_ADD_TEMPL_ARG(xm::getType<int>());
    XM_ADD_TEMPL_ARG(10);

    XM_BIND_PBASE(MyButton);
    bindProperty(XM_MNP(field1));
    bindProperty("field2", &ClassT::getField2);
}

XM_REGISTER_TYPE(MyTemplate2<int, int, 10>);
