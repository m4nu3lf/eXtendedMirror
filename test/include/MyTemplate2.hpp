#include<XM/xMirror.hpp>
#include<MyButton.hpp>

template<typename T1, typename T2, int i>
class MyTemplate2 : public MyButton
{
public:
    MyTemplate2() : MyButton(10, 10, 10, 10){};
    T1 field1;
    T2 getField2() {return field2;}
    virtual ~MyTemplate2(){};
private:
    T2 field2;
};

XM_DECLARE_CLASS(MyTemplate2<int, int, 10>);
