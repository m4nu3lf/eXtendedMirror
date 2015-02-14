/******************************************************************************      
 *      Extended Mirror: main.cpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#include <iostream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "XM/ExtendedMirror.hpp"
#include "XM/EnableStd.hpp"

using namespace std;
using namespace xm;

char c;


template<typename T>
class ClassTemplate
{
public:
    T val;
};

XM_ENABLE_TEMPLATE_1(ClassTemplate)
template<typename T>
XM_BUILD_CLASS(ClassTemplate<T>)
{
    bindProperty("val", &ClassTemplate<T>::val);
}

class Uninstantiable
{
private:
    Uninstantiable();
};

XM_ENABLE_CLASS(Uninstantiable)
XM_ASSUME_NON_INSTANTIABLE(Uninstantiable)
XM_BUILD_CLASS(Uninstantiable){}
XM_AUTOREG(Uninstantiable)

class Base
{
public:
    virtual void method() = 0;
    virtual ~Base(){};
private:
};

XM_ENABLE_CLASS(Base)
XM_ASSUME_ABSTRACT(Base)
XM_BUILD_CLASS(Base){}

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

XM_ENABLE_CLASS(CopyNotify)
XM_BUILD_CLASS(CopyNotify){}

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
    void doNothingUseful(std::string& s)
    {
        cout << s << endl;
    }
    CopyNotify& getSomething()
    {
        static CopyNotify copyNotify;
        return copyNotify;
    }
    ClassTemplate<int> templateInstance;
    int a[10][10];
    Dummy& self()
    {
        return *this;
    }
private:
    int field_;
};

XM_ENABLE_CLASS(Dummy)
XM_BUILD_CLASS(Dummy)
{
    XM_BIND_PASE(Base);
    bindProperty(XM_MNP(templateInstance));
    bindProperty(XM_MNP(a));
    bindMethod(XM_MNP(self));
    bindMethod<Dummy, void, int&>(XM_MNP(doNothingUseful));
    bindMethod<Dummy, void, string&>(XM_MNP(doNothingUseful));
    bindMethod(XM_MNP(getSomething));
    bindProperty("copyCount", &Dummy::getSomething);
}
XM_AUTOREG(Dummy)

/*
 * 
 */
int main(int argc, char** argv)
{    
    Dummy dummy;
    Dummy& d = dummy;
    
    int i = 0;
    Variant(&d).call("doNothingUseful", &i);
    getClass("Dummy").getMethod("doNothingUseful").call(d, &i);
    Variant(&d).call("doNothingUseful", string("ciao"));
    getClass("ClassTemplate<int>").getProperty("val").setData(d.templateInstance, 5);
 
    cout << i << endl;
    cout << d.templateInstance.val << endl;

    Base* b = new Dummy();
    //cout << is(*b, getClass<Dummy>()) << endl;
    getClass("Dummy").getMethod("getSomething").call(d);
    
    d.a[2][2] = 50;
    cout << getClass("Dummy").getProperty("a").getData(d).as<int(*)[10]>() << endl;
    cout << getClass("Base").isAbstract() << endl;
}



