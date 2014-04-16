/* 
 * File:   main.cpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 19, 2013, 16.09
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "EXTMR/ExtendedMirror.hpp"

using namespace std;
using namespace extmr;

char c;


template<typename T>
class ClassTemplate
{
public:
    T val;
};

EXTMR_ENABLE_TEMPLATE_1(ClassTemplate)
template<typename T>
EXTMR_BUILD_CLASS(ClassTemplate<T>)
{
    clazz & makeProperty("val", &ClassTemplate<T>::val);
}

class Uninstantiable
{
private:
    Uninstantiable();
};

EXTMR_ENABLE_CLASS(Uninstantiable)
EXTMR_ASSUME_NON_INSTANTIABLE(Uninstantiable)
EXTMR_BUILD_CLASS(Uninstantiable){}
EXTMR_AUTOREG(Uninstantiable)

class Base
{
public:
    virtual void method() = 0;
    virtual ~Base(){};
private:
};

EXTMR_ENABLE_CLASS(Base)
EXTMR_ASSUME_ABSTRACT(Base)
EXTMR_BUILD_CLASS(Base){}

class CopyNotify
{
public:
    CopyNotify()
    {
        
    }
    CopyNotify(const CopyNotify& orig)
    {
        cout << "object copy" << endl;
    }
};

EXTMR_ENABLE_CLASS(CopyNotify)
EXTMR_BUILD_CLASS(CopyNotify){}

class Dummy : public Base
{
public:
    void method(){};
    void doSomething(int i, int j)
    {
        field_ = i * j;
    }
    int& getField()
    {
        return field_;
    }
    void doNothingUseful(int& i)
    {
        i++;
    }
    CopyNotify& getSomething()
    {
        static CopyNotify copyNotify;
        return copyNotify;
    }
    ClassTemplate<int> templateInstance;
    int a[10][10];
private:
    int field_;
};

EXTMR_ENABLE_CLASS(Dummy)
EXTMR_BUILD_CLASS(Dummy)
{
    clazz & const_cast<Class&>(registerClass<Base>());
    clazz & makeProperty("templateInstance", &Dummy::templateInstance);
    clazz & makeProperty("a", &Dummy::a);
    clazz & makeMethod("doNothingUseful", &Dummy::doNothingUseful);
    clazz & makeMethod("getSomething", &Dummy::getSomething);
    clazz & makeProperty("copyCount", &Dummy::getSomething);
}
EXTMR_AUTOREG(Dummy)

/*
 * 
 */
int main(int argc, char** argv)
{    
    Dummy dummy;
    Dummy& d = dummy;
    
    int i = 0;
    getClass("Dummy").getMethod("doNothingUseful").call(d, RefVariant(i));
    getClass("ClassTemplate<int>").getProperty("val").setData(d.templateInstance, 5);
 
    cout << i << endl;
    cout << d.templateInstance.val << endl;

    Base* b = new Dummy();
    //cout << is(*b, getClass<Dummy>()) << endl;
    getClass("Dummy").getMethod("getSomething").call(d);
    
    d.a[2][2] = 50;
    cout << getClass("Dummy").getProperty("a").getData(d).as<void*>() << endl;
    cout << getClass("Base").isAbstract() << endl;
}



