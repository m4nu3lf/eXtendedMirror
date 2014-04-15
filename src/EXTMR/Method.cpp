/* 
 * File:   Method.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 20 ottobre 2012, 21.55
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Method::Method(const std::string& name) :
        Member(Class::Void, name), retType_(&Type::Void), fullSignature_(false)
{
}


Method::Method(const Class& owner, const std::string& name) :
        Member(owner, name), retType_(&Type::Void), fullSignature_(false)
{
}


Method::Method
(
    const string& name,
    const Type& retType,
    const Type& paramType1,
    const Type& paramType2,
    const Type& paramType3,
    const Type& paramType4,
    const Type& paramType5,
    const Type& paramType6,
    const Type& paramType7,
    const Type& paramType8
) :
    Member(Class::Void, name),
    retType_(&retType),
    fullSignature_(true)
{
    this->retType_ = &retType;
    if (paramType1 != Type::Void)
        params_.push_back(new Parameter(paramType1));
    if (paramType2 != Type::Void)
        params_.push_back(new Parameter(paramType2));
    if (paramType3 != Type::Void)
        params_.push_back(new Parameter(paramType3));
    if (paramType4 != Type::Void)
        params_.push_back(new Parameter(paramType4));
    if (paramType5 != Type::Void)
        params_.push_back(new Parameter(paramType5));
    if (paramType6 != Type::Void)
        params_.push_back(new Parameter(paramType6));
    if (paramType7 != Type::Void)
        params_.push_back(new Parameter(paramType7));
    if (paramType8 != Type::Void)
        params_.push_back(new Parameter(paramType8));
}


Method::Method
(
    const Class& owner,
    const string& name,
    const Type& retType,
    const Type& paramType1,
    const Type& paramType2,
    const Type& paramType3,
    const Type& paramType4,
    const Type& paramType5,
    const Type& paramType6,
    const Type& paramType7,
    const Type& paramType8
) :
    Member(owner, name),
    retType_(&retType),
    fullSignature_(true)
{
    this->retType_ = &retType;
    if (paramType1 != Type::Void)
        params_.push_back(new Parameter(paramType1));
    if (paramType2 != Type::Void)
        params_.push_back(new Parameter(paramType2));
    if (paramType3 != Type::Void)
        params_.push_back(new Parameter(paramType3));
    if (paramType4 != Type::Void)
        params_.push_back(new Parameter(paramType4));
    if (paramType5 != Type::Void)
        params_.push_back(new Parameter(paramType5));
    if (paramType6 != Type::Void)
        params_.push_back(new Parameter(paramType6));
    if (paramType7 != Type::Void)
        params_.push_back(new Parameter(paramType7));
    if (paramType8 != Type::Void)
        params_.push_back(new Parameter(paramType8));
}


void Method::addParameter(const Parameter& param)
{
    params_.push_back(&param);
}


const Type& Method::getReturnType() const
{
    return *retType_;
}


Method::ReturnMode Method::getReturnMode() const
{
    return Value;
}


const std::vector<const Parameter*>& Method::getParameters() const
{
    return params_;
}


bool Method::isConst() const
{
    return false;
}
