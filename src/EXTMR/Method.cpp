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
        name_(name), fullSignature_(false)
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
    name_(name),
    retType_(&retType),
    fullSignature_(true)
{
    this->retType_ = &retType;
    if (&paramType1 != NULL) params_.push_back(new Parameter(paramType1));
    if (&paramType2 != NULL) params_.push_back(new Parameter(paramType2));
    if (&paramType3 != NULL) params_.push_back(new Parameter(paramType3));
    if (&paramType4 != NULL) params_.push_back(new Parameter(paramType4));
    if (&paramType5 != NULL) params_.push_back(new Parameter(paramType5));
    if (&paramType6 != NULL) params_.push_back(new Parameter(paramType6));
    if (&paramType7 != NULL) params_.push_back(new Parameter(paramType7));
    if (&paramType8 != NULL) params_.push_back(new Parameter(paramType8));
}

Method::Method
(
    const string& name,
    const type_info& retType,
    const type_info& paramType1,
    const type_info& paramType2,
    const type_info& paramType3,
    const type_info& paramType4,
    const type_info& paramType5,
    const type_info& paramType6,
    const type_info& paramType7,
    const type_info& paramType8
) :
    name_(name),
    fullSignature_(true)
{    
    const TypeRegister& typeReg = TypeRegister::getTypeReg();
    
    if (&retType)
        this->retType_ = &typeReg.getType(retType);
    else this->retType_ = NULL;
    if (&paramType1 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType1)));
    if (&paramType2 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType2)));
    if (&paramType3 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType3)));
    if (&paramType4 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType4)));
    if (&paramType5 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType5)));
    if (&paramType6 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType6)));
    if (&paramType7 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType7)));
    if (&paramType8 != NULL) params_.push_back(new Parameter(typeReg.getType(paramType8)));
}

const std::string& Method::getName() const
{
    return name_;
}

void Method::addParameter(const Parameter& param)
{
    params_.push_back(&param);
}

const Type& Method::getReturnType() const
{
    return *retType_;
}

bool Method::getReturnByNonConstRef() const
{
    return false;
}

const std::vector<const Parameter*>& Method::getParameters() const
{
    return params_;
}

bool Method::isConst() const
{
    return false;
}
