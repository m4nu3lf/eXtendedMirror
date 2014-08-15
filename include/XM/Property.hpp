/******************************************************************************      
 *      Extended Mirror: Property.hpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
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


#ifndef XM_PROPERTY_HPP
#define XM_PROPERTY_HPP

namespace xm{

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
    Property(const std::string& name = "");
    
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
     * @param self Reference variant of an object which type has this property. 
     * @return Variant containing the property data.
     */
    virtual Variant getData(const Variant& self) const;
    
    /**
     * Set the data through variant objects.
     * 
     * @param self reference variant of an object which type has this property. 
     * @param data Variant containing the data to be set.
     */
    virtual void setData(const Variant& self, const Variant& data) const;
    
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

} // namespace xm

#endif // XM_PROPERTY_HPP
