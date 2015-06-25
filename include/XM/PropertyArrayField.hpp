/******************************************************************************      
 *      Extended Mirror: PropertyArrayField.hpp                               *
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


#ifndef XM_PROPERTYARRAYFIELD_HPP
#define	XM_PROPERTYARRAYFIELD_HPP

#include <XM/Exceptions/PropertySetException.hpp>

#include "Variant.hpp"

namespace xm{

/**
 * Implementation of the Property class. Handles a property from an array field.
 */
template<class ClassT, typename FieldT>
class PropertyArrayField : public Property
{
public:
    
    /**
     * Constructor for the property object.
     * 
     * @param name The property name.
     * @param field A member pointer to the field.
     */
    PropertyArrayField(const std::string& name, FieldT ClassT::*field)
    : Item(name, xm::getClass<ClassT>())
    {
        
        offset = (size_t) &(((ClassT*)NULL)->*field);
        type_ = &xm::getType<FieldT>();
    }
    
    
    char getFlags() const
    {
        return flags_;
    }
    
    
    Property& setFlags(char flags)
    {
        // cannot set an array
        flags &= ~Settable;
        
        this->flags_ = flags;   
        return *this;
    }
    
    
    Property::GetMode getGetMode()
    {
        return Value;
    }
    
    
    Property::SetMode getSetMode()
    {
        return None;
    }
    
    
    Variant getData(const Variant& self) const
    {
        // the value is retrieved as a constant to prevent exception throwing
        // if the passed Variant is a constant Variant.
        const ClassT& constObj = const_cast<Variant&>(self).as<const ClassT>();
        
        // remove constness, the costness is however handled successively
        ClassT& obj = const_cast<ClassT&>(constObj);
        char* byteObjPtr = reinterpret_cast<char*>(&obj);
        
        // the pointer is added to the the object pointer and converted to
        // the field type
        FieldT& fieldRef = *reinterpret_cast<FieldT*>(byteObjPtr + offset);
        
        if (self.isConst())
        {
            return Variant(const_cast<const FieldT&>(fieldRef),
                    Variant::CopyByRef);
        }
        else
        {
            return Variant(fieldRef, Variant::CopyByRef);
        }
    }
    
    
    void setData(const Variant& self, const Variant& data) const
    {
        // cannot set an array
        (void) self;
        (void) data;
        throw PropertySetException(*this);
    }
    
    
private:
    
    /// The offset of the field within the object.
    size_t offset;
};

} // namespace xm

#endif	/* XM_PROPERTYARRAYFIELD_HPP */

