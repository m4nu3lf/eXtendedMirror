/* 
 * File:   PropertyField.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 2 February 2013, 20.11
 */

#ifndef EXTMR_PROPERTYFIELD_HPP
#define	EXTMR_PROPERTYFIELD_HPP

#include <limits>

#include <EXTMR/BoundsCheck.hpp>
#include <EXTMR/Exceptions/SetNotAllowed.hpp>
#include <EXTMR/Exceptions/OutOfRange.hpp>
#include <EXTMR/Exceptions/ConstnessBreak.hpp>

#include "Variant.hpp"
#include "TypeRegister.hpp"

namespace extmr{

/**
 * Implementation of the Property class. Handles a property from a field.
 * The field must be a valid lvalue since the data writing is done using the
 * assignment.
 */
template<class ClassT, typename FieldT>
class PropertyField : public Property
{
public:
    /// A numerical type. The same of FieldT if FieldT is numerical.
    typedef typename ToNumerical<FieldT>::Type NumT;
    
    /// The property type, without any cv-qualifier.
    typedef typename RemoveConst<FieldT>::Type PropT;
    
    /**
     * Constructor for the property object.
     * 
     * @param name The property name.
     * @param field A member pointer to the field.
     */
    PropertyField(const std::string& name, FieldT ClassT::*field) : Property(name)
    {
        
        offset = (size_t) &(((ClassT*)NULL)->*field);
        type = &TypeRegister::getTypeReg().getType<FieldT>();
        
        // initialize bounds
        getTypeBounds<FieldT>(minValue, maxValue);
    }
    
    char getFlags() const
    {
        return flags;
    }
    
    Property& setFlags(char flags)
    {
        // cannot set a constant field
        if (IsConst<FieldT>::value) flags &= ~Settable;
        
        this->flags = flags;  
        return *this;
    }
    
    double getMinValue() const
    {
        return minValue;
    }
    
    Property& setMinValue(double minValue)
    {
        this->minValue = minValue;
        return *this;
    }
    
    double getMaxValue() const
    {
        return maxValue;
    }
    
    Property& setMaxValue(double maxValue)
    {
        this->maxValue = maxValue;
        return *this;
    }
    
    bool getGetByNcRef()
    {
        return true;
    }
    
    bool getSetByNcRef()
    {
        return false;
    }
    
    Variant getData(const Variant& objPtr) const
    {
        // the pointer is retrieved from the Variant and converted to a raw char pointer
        char* byteObjPtr = reinterpret_cast<char*>(objPtr.to<ClassT*>());
        
        // the pointer is summed to the the object pointer and converted to the field type
        FieldT& fieldRef = *reinterpret_cast<FieldT*>(byteObjPtr + offset);
        
        // the flags to construct the returned Variant. The Variant is a reference variant and it must by copied by reference
        char flags = Variant::Reference | Variant::CopyByRef;
        
        // if the pointer to the instance is a pointer to a constant, return the field data as a constant Variant
        if (objPtr.isPointedConst()) flags |= Variant::Const;
        
        // the data of the field is returned as a reference Variant
        return Variant(fieldRef, flags);
    }
    
    void setData(const Variant& objPtr, const Variant& data) const
    {   
        // check whether the property is settable
        if (!flags & Settable) throw SetNotAllowed(*this);
        
        // the pointer is retrieved from the variant and converted to a raw char pointer
        char* byteObjPtr = reinterpret_cast<char*>(objPtr.to<ClassT*>());
        
        // check whether the pointer provided in not a pointer to a constant object
        if (objPtr.isPointedConst()) throw ConstnessBreak(objPtr.getType());
        
        // retrieve the new data value
        const PropT extractedValue = data.to<const PropT>();
        
        // check whether the new value is acceptable
        if (!checkValueBounds(extractedValue, minValue, maxValue))
            throw OutOfRange(extractedValue, minValue, maxValue);
        
        // the pointer is summed to the the object pointer and converted to the field type
        PropT& fieldRef = *reinterpret_cast<PropT*>(byteObjPtr + offset);
        
        // the field is assigned the new data
        fieldRef = extractedValue;
    }
    
    /// The offset of the field within the object.
    size_t offset;
    
    /// The minimum allowed value for this property.
    NumT minValue;
    
    /// The maximum allowe value for this property.
    NumT maxValue;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYFIELD_HPP */

