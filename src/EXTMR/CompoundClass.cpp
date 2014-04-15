/* 
 * File:   CompoundClass.cpp
 * Author: manuele
 * 
 * Created on May 2, 2013, 4:00 PM
 */

#include <EXTMR/ExtendedMirror.hpp>

using namespace extmr;
using namespace std;


CompoundClass::CompoundClass
(
    const string& name,
    uint size,
    const type_info& cppType,
    Constructor* constructor,
    CopyConstructor* copyConstructor,
    Destructor* destructor,
    AssignOperator* assignOperator,
    bool isAbstract,
    const Template& tempjate,
    const Const_Type_Vector& templateArgs
) :
    Class
    (
        name,
        size,
        cppType,
        constructor,
        copyConstructor,
        destructor,
        assignOperator,
        isAbstract
    ),
    tempjate_(&tempjate),
    templateArgs_(templateArgs)
{
}


Type::Category CompoundClass::getCategory() const
{
    return Type::CompoundClass;
}


const Template& CompoundClass::getTemplate() const
{
    return *tempjate_;
}


const Const_Type_Vector& CompoundClass::getTemplateArgs() const
{
    return templateArgs_;
}

