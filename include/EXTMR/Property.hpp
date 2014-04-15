/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PROPERTYDESC_HPP
#define EXTMR_PROPERTYDESC_HPP

namespace extmr{

class Type;
class Variant;

/**
 * Describes a property of a class. A property is an attribute that has been 
 * registered through the reflection mechanism. Note that a Property is related 
 * to the class and not to the object (instances).
 */
class Property : public Member
{
public:
    
    // Some property flags.
    enum PropertyFlags
    {
        // Whether the property is settable or not.
        Settable = 1,

        // Whether the property interface should be considered part of the host
        // class interface.
        Encapsulated = 2,

        // Whether the property is retrieved and set by pointer
        Pointer = 4,

    };
    
    enum GetSetMode
    {
        None = 0,
        Value = 1,
        Reference = 2,
        ConstReference = 6,
    };
    
    typedef GetSetMode GetMode;
    typedef GetSetMode SetMode;
    
    /**
     * Basic constructor for initialization.
     * 
     * @param name The property name.
     */
    Property(const std::string& name);
    
    /**
     * Basic constructor for initialization.
     * 
     * @param owner The property owner.
     * @param name The property name.
     */
    Property(const Class& owner, const std::string& name);
    
    /**
     * Get the Type of the property type.
     * 
     * @return The Type.
     */
    const Type& getType() const;
    
    /**
     * Get the flags of this property.
     * 
     * @return The flags.
     */
    virtual char getFlags() const;
    
    /**
     * Set the property flags.
     * A reference to the Property is returned to allow a method chain call.
     * 
     * @param flags The flags.
     * @return This Property.
     */
    virtual Property& setFlags(char flags);
    
    /**
     * Ask for the property minimum allowed value.
     * NOTE: this method makes sense only if the property is of a numerical
     * type.
     * 
     * @return the minimum value.
     */
    virtual double getMinValue() const;
    
    /**
     * Set the property minimum allowed value.
     * A reference to the Property is returned to allow a method chain call.
     * NOTE: this method makes sense only if the property is of a numerical
     * type.
     * 
     * @param minValue the minimum allowed value.
     * @return This Property.
     */
    virtual Property& setMinValue(double minValue);
    /**
     * Ask for the property maximum allowed value.
     * NOTE: this method makes sense only if the property is of a numerical
     * type.
     * 
     * @return the maximum value.
     */
    virtual double getMaxValue() const;
    
    /**
     * Set the property maximum allowed value.
     * A reference to the Property is returned to allow a method chain call.
     * NOTE: this method makes sense only if the property is of a numerical
     * type.
     * 
     * @param maxValue the maximum allowed value.
     * @return This Property.
     */
    virtual Property& setMaxValue(double maxValue);
    
    /**
     * Ask how the property data is retrieved, that is by value, by reference
     * of by a constant reference.
     * 
     * @return The GetMode
     */
    virtual Property::GetMode getGetMode();
    
    /**
     * Ask how the property data is set, that is by value, by reference
     * of by a constant reference.
     * 
     * @return The SetMode
     */
    virtual Property::SetMode getSetMode();
    
    /**
     * Get the data through variant objects.
     * 
     * @param objPtr Pointer to an object which type has this property. 
     * @return Variant containing the property data.
     */
    virtual Variant getData(const Variant& objPtr) const;
    
    /**
     * Set the data through variant objects.
     * 
     * @param objPtr Pointer to an object which type has this property. 
     * @param data Variant containing the data to be set.
     */
    virtual void setData(const Variant& objPtr, const Variant& data) const {};
    
protected:
    // The property Type.
    const Type* type_;
    
    // Property flags.
    char flags_;
};


bool inline operator<(const Property& p1, const Property& p2)
{
    return static_cast<const Member&>(p1) < static_cast<const Member&>(p2);
}

typedef std::set<Property*, PtrCmpByVal<Property> > Property_Set;
typedef std::set<const Property*, PtrCmpByVal<Property> > Const_Property_Set;

} // namespace extmr

#endif // EXTMR_PROPERTYDESC_HPP
