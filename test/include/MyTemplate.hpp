#include<XM/xMirror.hpp>
#include<MyButton.hpp>

template<typename T1, typename T2>
class MyTemplate : public MyButton
{
public:
    MyTemplate() : MyButton(10, 10, 10, 10){};
    T1 field1;
    T2 getField2() {return field2;}
    virtual ~MyTemplate(){};
private:
    T2 field2;
};

XM_DECLARE_TEMPLATE_2(MyTemplate);

template<typename T1, typename T2>
XM_DEFINE_CLASS(MyTemplate<T1, T2>)
{
    XM_BIND_PBASE(MyButton);
    bindProperty(XM_MNP(field1));
    bindProperty("field2", &ClassT::getField2);
}
