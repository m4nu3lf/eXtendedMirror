/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PROPERTYGETTERNSETTER_HPP
#define	EXTMR_PROPERTYGETTERNSETTER_HPP

#include <limits>

#include <EXTMR/NumericalUtils.hpp>
#include <EXTMR/Exceptions/PropertySetException.hpp>
#include <EXTMR/Exceptions/PropertyRangeException.hpp>
#include <EXTMR/MethodWrappers.hpp>

#include "Variant.hpp"
#include "Property.hpp"
#include "TypeTraits.hpp"


namespace extmr{

/**
 * Implementation of the Property class. Handles a property from a getter
 * and setter couple.
 */
template<class ClassT, typename RetT, typename ParamT = Empty,
        typename ExtrParamT1 = Empty, typename ExtrParamT2 = Empty>
class PropertyGetterNSetter : public Property
{
    // define the property type after removing the reference and all the
    // cv qualifiers
    typedef typename RemoveReference<RetT>::Type NonRefT; 
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type PropT;
    
    // A numerical type. The same of PropT if PropT is numerical.
    typedef typename ToNumerical<PropT>::Type NumT;
    
    // general getter method
    typedef RetT (ClassT::*GeneralGetter)(...);
    
    // general setter method
    typedef void (ClassT::*GeneralSetter)(ParamT, ...);
    
    // getter method with no extra parameters
    typedef RetT (ClassT::*Getter0)();
    
    // setter method with no extra parameters
    typedef void (ClassT::*Setter0)(ParamT);
    
    // getter method with one extra parameters
    typedef RetT (ClassT::*Getter1)(ExtrParamT1);
    
    // setter method with one extra parameters
    typedef void (ClassT::*Setter1)(ParamT, ExtrParamT1);
    
    // getter method with two extra parameters
    typedef RetT (ClassT::*Getter2)(ExtrParamT1, ExtrParamT2);
    
    // setter method with two extra parameters
    typedef void (ClassT::*Setter2)(ParamT, ExtrParamT1, ExtrParamT2);
    
public:
    
    /**
     * Constructor for the property object. Takes no extra arguments.
     * 
     * @param name The property name.
     * @param getter The property getter method.
     * @param constGetter Whether the getter method is constant.
     * @param setter The property setter method.
     */
    PropertyGetterNSetter
    (
        const std::string& name,
        Getter0 getter,
        bool constGetter,
        Setter0 setter
    ) 
    : Property(name)
    , getterWrapper_(getter)
    , constGetter_(constGetter)
    , setterWrapper_(setter)
    {
         type_ = &extmr::getType<PropT>();
        
        // if the setter is not null we can set the property
        if (setter) flags_ |= Settable;
         
        // initialize bounds
         getTypeBounds<PropT>(minValue_, maxValue_);
    }
    
    
    /**
     * Constructor for the property object. Takes one extra argument.
     * 
     * @param name The property name.
     * @param getter The property getter method.
     * @param constGetter Whether the getter method is constant.
     * @param setter The property setter method.
     * @param extrArg1 The property extra argument.
     */
    PropertyGetterNSetter
    (
        const std::string& name,
        Getter1 getter,
        bool constGetter,
        Setter1 setter,
        ExtrParamT1 extrArg1
    )
    : Property(name)
    , getterWrapper_(getter)
    , constGetter_(constGetter)
    , setterWrapper_(setter)
    , extrArg1_(extrArg1)
    {
        type_ = &extmr::getType<PropT>();
                
        // if the setter is not null we can set the property
        if (setter) flags_ |= Settable;
        
        // initialize bounds
        getTypeBounds<PropT>(minValue_, maxValue_);
    }
    
    
    /**
     * Constructor for the property object. Takes two extra arguments.
     * 
     * @param name The property name.
     * @param getter The property getter method.
     * @param constGetter Whether the getter method is constant.
     * @param setter The property setter method.
     * @param extraArg1 The first property extra argument.
     * @param extraArg2 The second property extra argument.
     */
    PropertyGetterNSetter
    (
        const std::string& name,
        Getter2 getter,
        bool constGetter,
        Setter2 setter,
        ExtrParamT1 extrArg1,
        ExtrParamT2 extrArg2
    )
    : Property(name)
    , getterWrapper_(getter)
    , constGetter_(constGetter)
    , setterWrapper_(setter)
    , extrArg1_(extrArg1)
    , extrArg2_(extrArg2)
    {
        type_ = &extmr::getType<PropT>();
        
        // if the setter is not null we can set the property
        if (setter) flags_ |= Settable;
        
        // initialize bounds
        getTypeBounds<PropT>(minValue_, maxValue_);
    }
    
    
    char getFlags() const
    {
        return flags_;
    }
    
    
    Property& setFlags(char flags)
    {
        // If the setter pointer is NULL no way we can change the property to a
        // settable one.
        if (!setterWrapper_.setter) flags &= ~Settable;
        
        flags_ = flags;
        return *this;
    }
    
    
    double getMinValue() const
    {
        return minValue_;
    }
    
    
    Property& setMinValue(double minValue)
    {
        minValue_ = minValue;
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
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    
    Property::SetMode getSetMode()
    {
        if (!setterWrapper_.setter)
            return None;
        
        if (IsReference<ParamT>::value)
        {
            if (IsConst<ParamT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }
    
    
    const Variant& getData(const RefVariant& self) const
    {
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = self.as<ClassT>();
        
        // we cannot call a non constant getter of a constant instance
        if (self.isConst() && !constGetter_)
            throw VariantCostnessException(self.getType());
                
        const PropT& data = getterWrapper_(objRef, extrArg1_, extrArg2_);
        return Variant(const_cast<PropT&>(data),
                ReturnVariantFlags<RetT>::flags);
    }
    
    
    void setData(const RefVariant& self, const Variant& data) const
    {
        // check whether the property is settable
        if (!setterWrapper_.setter)
            throw PropertySetException(*this);
        
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = self.as<ClassT>();
        
        // retrieve the new data value
        PropT& extractedValue = data.as<PropT>();
        
        // check whether the new value is into the specified bounds
        if (!checkValueBounds(extractedValue, minValue_, maxValue_)) return;
        
        // the data is set calling the setter method wrapper
        setterWrapper_(objRef, extractedValue, extrArg1_, extrArg2_);
    }
    
private:

    /// The getter method wrapper
    GetterWrapper<ClassT, RetT, ExtrParamT1, ExtrParamT2> getterWrapper_;
    
    /// Whether the getter method is constant
    bool constGetter_;
    
    /// The setter method wrapper
    SetterWrapper<ClassT, ParamT, ExtrParamT1, ExtrParamT2> setterWrapper_;
    
    /// First extra parameter to pass when calling the getter and setter
    ExtrParamT1 extrArg1_;
    
    /// Second extra parameter to pass when calling the getter and setter
    ExtrParamT2 extrArg2_;
    
    /// The minimum allowed value for this property.
    NumT minValue_;
    
    /// The maximum allowed value for this property.
    NumT maxValue_;
};

} // namespace extmr

#endif	/* PROPERTYGETTERNSETTER_HPP */

