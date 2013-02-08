/* 
 * File:   PropertyArrayField.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 2 February 2013, 20.29
 */

#ifndef EXTMR_PROPERTYARRAYFIELD_HPP
#define	EXTMR_PROPERTYARRAYFIELD_HPP

#include <EXTMR/Exceptions/SetNotAllowed.hpp>

#include "Variant.hpp"

namespace extmr{

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
    PropertyArrayField(const std::string& name, FieldT ClassT::*field) : Property(name)
    {
        
        offset = (size_t) &(((ClassT*)NULL)->*field);
        type = &TypeRegister::getTypeReg().getType<FieldT>();
    }
    
    char getFlags() const
    {
        return flags;
    }
    
    Property& setFlags(char flags)
    {
        // cannot set an array
        flags &= ~Settable;
        
        this->flags = flags;   
        return *this;
    }
    
    bool getGetByNcRef()
    {
        return false;
    }
    
    bool getSetByNcRef()
    {
        return false;
    }
    
    Variant getData(const Variant& objPtr) const
    {
        // the pointer is retrieved from the variant and converted to a raw char pointer
        char* byteObjPtr = reinterpret_cast<char*>(objPtr.to<ClassT*>());
        
        // the pointer is summed to the the object pointer and converted to the field type
        FieldT& fieldRef = *reinterpret_cast<FieldT*>(byteObjPtr + offset);
        
        if (objPtr.isPointedConst())
        {
            // the array type is converted to a constant type, and the value is returned through a Variant
            return Variant(const_cast<const FieldT&>(fieldRef));
        }
        else
        {
            // the array is returned through a Variant
            return Variant(fieldRef);
        }
    }
    
    void setData(const Variant& objPtr, const Variant& data) const
    {
        // cannot set an array
        throw SetNotAllowed(*this);
    }
    
    /// The offset of the field within the object.
    size_t offset;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYARRAYFIELD_HPP */

