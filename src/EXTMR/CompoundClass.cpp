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
    const Template& tempjate,
    const ConstTypeVector& templateParamTypes
) :
    Class
    (
        name,
        size,
        cppType,
        constructor,
        copyConstructor,
        destructor,
        assignOperator
    ),
    tempjate_(&tempjate),
    templateArgs_(templateParamTypes)
{
}


const Template& CompoundClass::getTemplate() const
{
    return *tempjate_;
}


const ConstTypeVector& CompoundClass::getTemplateArgs() const
{
    return templateArgs_;
}

