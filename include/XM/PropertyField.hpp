/******************************************************************************      
 *      Extended Mirror: PropertyField.hpp                                    *
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


#ifndef XM_PROPERTYFIELD_HPP
#define	XM_PROPERTYFIELD_HPP

#include <limits>

#include <XM/Utils/Bounds.hpp>
#include <XM/Exceptions/PropertySetException.hpp>
#include <XM/Exceptions/PropertyRangeException.hpp>
#include <XM/Exceptions/VariantCostnessException.hpp>

#include "Variant.hpp"


namespace xm{

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
    : Item(name, xm::getClass<ClassT>())
    {
        
        offset_ = (size_t) &(((ClassT*)NULL)->*field);
        type_ = &xm::getType<FieldT>();
        
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
    
    
    Variant getData(const Variant& self) const
    {            
        // the value is retrieved as a constant to prevent exception throwing
        // if the passed Variant is a constant Variant.
        const ClassT& constObj = const_cast<Variant&>(self).as<const ClassT>();
        
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
        if (self.isConst())
            flags |= Variant::Const;
        
        // the data of the field is returned as a reference Variant
        return Variant(fieldRef, flags | Variant::CpyByRef);
    }
    
    
    void setData(const Variant& self, const Variant& data) const
    {
        // check whether the property is settable
        if (!(flags_ & Settable))
            throw PropertySetException(*this);
        
        // the pointer is retrieved from the variant and converted to a raw char
        // pointer
        char* byteObjPtr = reinterpret_cast<char*>(
            &const_cast<Variant&>(self).as<ClassT>());
        
        // check whether the pointer provided in not a pointer to a constant
        // object
        if (self.isConst())
            throw VariantCostnessException(self.getType());
        
        // retrieve the new data value
        const PropT extractedValue =
            const_cast<Variant&>(data).as<const PropT>();
        
        // check whether the new value is within bounds
        if (!checkValueBounds(extractedValue, minValue_, maxValue_))
            throw PropertyRangeException(toDouble(extractedValue), minValue_, maxValue_);
        
        // the pointer is added to the the object pointer and converted to the
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

} // namespace xm

#endif	/* XM_PROPERTYFIELD_HPP */

