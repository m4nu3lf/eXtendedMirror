#ifndef EXTMR_PROPERTYDESC_HPP
#define EXTMR_PROPERTYDESC_HPP

namespace extmr{

class Type;
class Class;
class Variant;

/**
 * Describes a property of a class. A property is an attribute that has been 
 * registered through the reflection mechanism. Note that a Property is related 
 * to the class and not to the object (instances).
 */
class Property
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
    Property(const std::string& name = "");
    
    /**
     * Get the name of the property.
     * 
     * @return The name of the property.
     */
    const std::string& getName() const;
    
    /**
     * Get the Type of the property type.
     * 
     * @return The Type.
     */
    const Type& getType() const;
    
    /**
     * Get the owner Class of the property.
     * 
     * @return The owner Class.
     */
    const Class& getOwner() const;
    
    /**
     * Set the owner Class of the property.
     * 
     * @param owner The owner Class.
     */
    void setOwner(const Class& owner);
    
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
    
    
    typedef extmr::PtrCmpByName<Property> PtrCmp;
    
protected:
    
    // The property name.
    std::string name_;
    
    // The property owner class
    const Class* owner_;
    
    // The property Type.
    const Type* type_;
    
    // PtrCmpByName must be a friend of this class to access the name attribute.
    friend class extmr::PtrCmpByName<Property>;
    
    // Property flags.
    char flags_;
};

typedef std::set<Property*, Property::PtrCmp> PropertySet;
typedef std::set<const Property*, Property::PtrCmp> ConstPropertySet;

} // namespace extmr

#endif // EXTMR_PROPERTYDESC_HPP
