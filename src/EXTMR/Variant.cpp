/* 
 * File:   Variant.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 3 September 2012, 12.04
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Variant::Variant() : flags_(0)
{
    data_ = NULL;
    type_ = &Type::Void;
}


RefVariant Variant::getRefVariant() const
{
    RefVariant refVar;
    refVar.data_ = data_;
    refVar.type_ = type_;
    refVar.flags_ = flags_ | Reference;
    
    // need a const cast to help compiler choose the copy constructor
    // instead of the template constructor
    return const_cast<const RefVariant&>(refVar);
}


Variant::Variant(const Variant& orig) : flags_(0)
{       
    // copy the Type pointer
    type_ = orig.type_;
    
    // copy the data
    data_ = type_->copyInstance(orig.data_);
}


const Variant& Variant::operator=(const Variant& other)
{
    // check if the type are different
    if (*other.type_ != *type_)
    {
        // deallocate previous data if any
        if (data_) type_->deleteInstance(data_);

        // copy the Type pointer
        type_ = other.type_;
        
        // allocate the new type data
        data_ = type_->newInstance();
    }
    // if no data has yet been allocated, allocate it now
    else if(!data_)
        data_ = type_->newInstance();
    
    // perform assignment
    type_->assignInstance(data_, other.data_);
}


Variant::~Variant()
{
    if (!flags_ & Reference)
    {        
        // deallocate the data
        if (data_)
            type_->deleteInstance(data_);
    }
}


// A variant can always be converted to an Empty object. 
template<>
Empty& Variant::as<Empty>() const
{
    static Empty empty;
    return empty;
}

