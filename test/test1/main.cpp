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

class Base0
{
public:
    Base0(){a = 0;};
    float a;
    virtual ~Base0(){};
};

EXTMR_ENABLE_CLASS(Base0)
EXTMR_BUILD_CLASS(Base0)
{
    
}

class Base1 : public Base0
{
public:
    Base1(){a = 1;};
    float a;
};

EXTMR_ENABLE_CLASS(Base1)
EXTMR_BUILD_CLASS(Base1)
{
    clazz & const_cast<Class&>(registerClass<Base0>());
    clazz & *new extmr::RefCasterImpl<Base1, Base0>();
}

class Base2
{
public:
    Base2(){a = 2;};
    float a;
};

EXTMR_ENABLE_CLASS(Base2)
EXTMR_BUILD_CLASS(Base2)
{
    
}

class Derived: public Base1, public Base2
{
public:
    virtual ~Derived(){};
};

EXTMR_ENABLE_CLASS(Derived)
EXTMR_BUILD_CLASS(Derived)
{
    clazz & const_cast<Class&>(extmr::registerClass<Base1>());
    clazz & *new extmr::RefCasterImpl<Derived,Base1>();
    
    clazz & const_cast<Class&>(extmr::registerClass<Base2>());
    clazz & *new extmr::RefCasterImpl<Derived,Base2>();
}

class Derived2: public Derived
{
public:
    Derived2() {a = 50;}
    float a;
};

EXTMR_ENABLE_CLASS(Derived2)
EXTMR_BUILD_CLASS(Derived2)
{
    clazz & const_cast<Class&>(extmr::registerClass<Derived>());
    clazz & *new extmr::RefCasterImpl<Derived2,Derived>();
}


int main(int argc, char** argv)
{    
    Derived d;
    Variant v = d;
    cout << v.to<Base0>().a << endl;
}

