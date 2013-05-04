/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PROPERTYFIELD_HPP
#define	EXTMR_PROPERTYFIELD_HPP

#include <limits>

#include <EXTMR/NumericalUtils.hpp>
#include <EXTMR/Exceptions/PropertySetException.hpp>
#include <EXTMR/Exceptions/PropertyRangeException.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>


namespace extmr{

/**
 * Implementation of the Property class. Handles a property from a field.
 * The field must be a valid lvalue since the data writing is done using the
 * assignment.
 */
template<class ClassT, typename FieldT>
class PropertyField : public Property
{
    /// A numerical type. The same of FieldT if FieldT is numerical.
    typedef typename ToNumerical<FieldT>::Type NumT;

    /// The property type, without any cv-qualifier.
    typedef typename RemoveConst<FieldT>::Type PropT;

public:
    
    /**
     * Constructor for the property object.
     * 
     * @param name The property name.
     * @param field A member pointer to the field.
     */
    PropertyField(const std::string& name, FieldT ClassT::*field)
    : Property(name)
    {
        
        offset_ = (size_t) &(((ClassT*)NULL)->*field);
        type_ = &TypeRegister::getSingleton().getType<FieldT>();
        
        // initialize bounds
        getTypeBounds<FieldT>(minValue_, maxValue_);
        
        // if the property is not constant we can set it by default
        if (!IsConst<FieldT>::value) flags_ |= Settable;
        
    }
    
    
    char getFlags() const
    {
        return flags_;
    }
    
    
    Property& setFlags(char flags)
    {
        // cannot set a constant field
        if (IsConst<FieldT>::value) flags &= ~Settable;
        
        this->flags_ = flags;  
        return *this;
    }
    
    
    double getMinValue() const
    {
        return minValue_;
    }
    
    
    Property& setMinValue(double minValue)
    {
        this->minValue_ = minValue;
        return *this;
    }
    
    
    double getMaxValue() const
    {
        return maxValue_;
    }
    
    
    Property& setMaxValue(double maxValue)
    {
        this->maxValue_ = maxValue;
        return *this;
    }
    
    
    Property::GetMode getGetMode()
    {
        return Reference;
    }
    
    
    Property::SetMode getSetMode()
    {
        return Value;
    }
    
    
    Variant getData(const Variant& objPtr) const
    {            
        // the value is retrieved as a constant to prevent exception throwing
        // if the passed Variant is a constant Variant.
        const ClassT& constObj = *objPtr.to<const ClassT*>();
        
        // remove constness, the costness is however handled successively
        ClassT& obj = const_cast<ClassT&>(constObj);
        char* byteObjPtr = reinterpret_cast<char*>(&obj);
        
        // the pointer is summed to the the object pointer and converted to the
        // field type
        FieldT& fieldRef = *reinterpret_cast<FieldT*>(byteObjPtr + offset_);
        
        // the flags to construct the returned Variant. The Variant is a
        // reference variant and it must by copied by reference
        char flags = Variant::Reference;
        
        // if the pointer to the instance is a pointer to a constant, return the
        // field data as a constant Variant
        if (objPtr.isPointerToConst())
            flags |= Variant::Const;
        
        // the data of the field is returned as a reference Variant
        return Variant(fieldRef, flags);
    }
    
    
    void setData(const Variant& objPtr, const Variant& data) const
    {   
        // check whether the property is settable
        if (!flags_ & Settable)
            throw PropertySetException(*this);
        
        // the pointer is retrieved from the variant and converted to a raw char
        // pointer
        char* byteObjPtr = reinterpret_cast<char*>(objPtr.to<ClassT*>());
        
        // check whether the pointer provided in not a pointer to a constant
        // object
        if (objPtr.isPointerToConst())
            throw VariantCostnessException(objPtr.getType());
        
        // retrieve the new data value
        const PropT extractedValue = data.to<const PropT>();
        
        // check whether the new value is within bounds
        if (!checkValueBounds(extractedValue, minValue_, maxValue_))
            throw PropertyRangeException(toDouble(extractedValue), minValue_, maxValue_);
        
        // the pointer is summed to the the object pointer and converted to the
        // field type
        PropT& fieldRef = *reinterpret_cast<PropT*>(byteObjPtr + offset_);
        
        // the field is assigned the new data
        fieldRef = extractedValue;
    }
    
private:
    // The offset of the field within the object.
    size_t offset_;
    
    // Used only for numerical properties.
    NumT minValue_;
    
    // Used only for numerical properties.
    NumT maxValue_;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYFIELD_HPP */

