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
    dataPtr = NULL;
    typePtr = NULL;
}

Variant::Variant(const Variant& orig) : flags(0)
{       
    // copy the Type pointer
    typePtr = orig.typePtr;
    
    if (orig.flags | CopyByRef)
    {
        // reference the data
        dataPtr = orig.dataPtr;
        
        // copy constness
        flags = orig.flags;
        
        // mark the variant as a reference
        flags |= Reference;
    }
    else
    {
        // copy the data
        dataPtr = typePtr->newInstance(orig.dataPtr);
    }
}

const Variant& Variant::operator=(const Variant& other)
{
    // check if the type are different
    if (*other.typePtr != *typePtr)
    {
        // deallocate previous data if any
        if (dataPtr) typePtr->deleteInstance(dataPtr);

        // copy the Type pointer
        typePtr = other.typePtr;
        
        // allocate the new type data
        dataPtr = typePtr->newInstance();
    }
    // if no data has yet been allocated, allocate it now
    else if(!dataPtr) dataPtr = typePtr->newInstance();
    
    // perform assignment
    typePtr->assignInstance(dataPtr, other.dataPtr);
}

Variant::~Variant()
{
    if (!flags & Reference)
    {        
        // deallocate the data
        if (dataPtr) typePtr->deleteInstance(dataPtr);
    }
}

bool Variant::isValid()
{
    return dataPtr && typePtr;
}

bool Variant::canReinterpret(const Type& type, const Type& targetType)
{
    // are they the same type?
    if (type == targetType) return true;

    // are they objects?
    if (type.getCategory() == Type::Class && targetType.getCategory() == Type::Class)
    {
        // cast to the respective class descriptors
        const Class& clazz = dynamic_cast<const Class&>(type);
        const Class& targetClass = dynamic_cast<const Class&>(targetType);

        // is the target type a base class of the contained data type?
        if (clazz.derivesFrom(targetClass)) return true;
        else return false;
    }
        
    // are they pointers?
    if (type.getCategory() == Type::Pointer && targetType.getCategory() == Type::Pointer)
    {
        // get the pointed types
        const Type& pointedType = type.getPointedType();
        const Type& pointedTargetType = targetType.getPointedType();

        // are they objects?
        if (pointedType.getCategory() != Type::Class || pointedTargetType.getCategory() != Type::Class)
            return false;

        // are they the same type?
        if (pointedType == pointedTargetType) return true;

        // cast to the respective class descriptors
        const Class& pointedClass = dynamic_cast<const Class&>(pointedType);
        const Class& pointedTargetClass = dynamic_cast<const Class&>(pointedTargetType);
        
        // is the target pointed class a base class of the pointed class?
        if (pointedClass.derivesFrom(pointedTargetClass)) return true;
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

