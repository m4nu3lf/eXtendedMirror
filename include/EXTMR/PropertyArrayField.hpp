/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PROPERTYARRAYFIELD_HPP
#define	EXTMR_PROPERTYARRAYFIELD_HPP

#include <EXTMR/Exceptions/PropertySetException.hpp>

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
    PropertyArrayField(const std::string& name, FieldT ClassT::*field)
    : Property(name)
    {
        
        offset = (size_t) &(((ClassT*)NULL)->*field);
        type_ = &TypeRegister::getSingleton().getType<FieldT>();
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
    
    
    Variant getData(const Variant& objPtr) const
    {
        // the value is retrieved as a constant to prevent exception throwing
        // if the passed Variant is a constant Variant.
        const ClassT& constObj = *objPtr.as<const ClassT*>();
        
        // remove constness, the costness is however handled successively
        ClassT& obj = const_cast<ClassT&>(constObj);
        char* byteObjPtr = reinterpret_cast<char*>(&obj);
        
        // the pointer is summed to the the object pointer and converted to the field type
        FieldT& fieldRef = *reinterpret_cast<FieldT*>(byteObjPtr + offset);
        
        if (objPtr.isPointerToConst())
        {
            return Variant(const_cast<const FieldT&>(fieldRef), 0);
        }
        else
        {
            return Variant(fieldRef, 0);
        }
    }
    
    
    void setData(const Variant& objPtr, const Variant& data) const
    {
        // cannot set an array
        throw PropertySetException(*this);
    }
    
    
private:
    
    /// The offset of the field within the object.
    size_t offset;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYARRAYFIELD_HPP */

