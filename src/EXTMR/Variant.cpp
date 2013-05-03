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

Variant::Variant()
{
    data_ = NULL;
    type_ = NULL;
}


Variant::Variant(const Variant& orig) : flags(0)
{       
    // copy the Type pointer
    type_ = orig.type_;
    
    if (orig.flags | CopyByRef)
    {
        // reference the data
        data_ = orig.data_;
        
        // copy constness
        flags = orig.flags;
        
        // mark the variant as a reference
        flags |= Reference;
    }
    else
    {
        // copy the data
        data_ = type_->newInstance(orig.data_);
    }
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
    if (!flags & Reference)
    {        
        // deallocate the data
        if (data_)
            type_->deleteInstance(data_);
    }
}


bool Variant::isValid()
{
    return data_ && type_;
}


bool Variant::canReinterpret(const Type& type, const Type& targetType)
{
    // are they the same type?
    if (type == targetType) return true;

    // are they objects?
    if (type.getCategory() == Type::Class &&
            targetType.getCategory() == Type::Class)
    {
        // cast to the respective class descriptors
        const Class& clazz = dynamic_cast<const Class&>(type);
        const Class& targetClass = dynamic_cast<const Class&>(targetType);

        // is the target type a base class of the contained data type?
        if (clazz.inheritsFrom(targetClass)) return true;
        else return false;
    }
        
    // are they pointers?
    if (type.getCategory() == Type::Pointer &&
            targetType.getCategory() == Type::Pointer)
    {
        // is target of type void*?
        if (targetType.getName() == "void*") return true;
        
        // get the pointed types
        const PointerType& ptrType = dynamic_cast<const PointerType&>(type);
        const PointerType& ptrTargetType =
                                   dynamic_cast<const PointerType&>(targetType);
        const Type& pointedType = ptrType.getPointedType();
        const Type& pointedTargetType = ptrTargetType.getPointedType();

        // are they objects?
        if (pointedType.getCategory() != Type::Class ||
                pointedTargetType.getCategory() != Type::Class)
            return false;

        // are they the same type?
        if (pointedType == pointedTargetType) return true;

        // cast to the respective class descriptors
        const Class& pointedClass = dynamic_cast<const Class&>(pointedType);
        const Class& pointedTargetClass =
                dynamic_cast<const Class&>(pointedTargetType);
        
        // is the target pointed class a base class of the pointed class?
        if (pointedClass.inheritsFrom(pointedTargetClass)) return true;
        else return false;
    }
}


namespace extmr{

// A variant can always be converted to an Empty object. 
template<>
Empty& Variant::to<Empty>() const
{
    static Empty empty;
    return empty;
}


} // namespace extmr

