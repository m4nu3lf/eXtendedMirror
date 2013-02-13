/* 
 * File:   PropertyGetterNSetter.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on February 2, 2013, 20.14
 */

#ifndef EXTMR_PROPERTYGETTERNSETTER_HPP
#define	EXTMR_PROPERTYGETTERNSETTER_HPP

#include <limits>

#include <EXTMR/BoundsCheck.hpp>
#include <EXTMR/Exceptions/PropertySetException.hpp>
#include <EXTMR/Exceptions/PropertyRangeException.hpp>
#include <EXTMR/MemberWrappers.hpp>

#include "Variant.hpp"


namespace extmr{

/**
 * Implementation of the Property class. Handles a property from a getter
 * and setter couple.
 */
template<class ClassT, typename RetT, typename ParamT = Empty, typename ExtrParamT1 = Empty, typename ExtrParamT2 = Empty>
class PropertyGetterNSetter : public Property
{
    /// define the property type after removing the cv-qualifier and the constness of RetT
    typedef typename RemoveAllCVQualifiers<typename RemoveReference<RetT>::Type>::Type PropT;
    
    /// A numerical type. The same of PropT if PropT is numerical.
    typedef typename ToNumerical<PropT>::Type NumT;
    
    /// general getter method
    typedef RetT (ClassT::*GeneralGetter)(...);
    
    /// general setter method
    typedef void (ClassT::*GeneralSetter)(ParamT, ...);
    
    /// getter method with no extra parameters
    typedef RetT (ClassT::*Getter0)();
    
    /// setter method with no extra parameters
    typedef void (ClassT::*Setter0)(ParamT);
    
    /// getter method with one extra parameters
    typedef RetT (ClassT::*Getter1)(ExtrParamT1);
    
    /// setter method with one extra parameters
    typedef void (ClassT::*Setter1)(ParamT, ExtrParamT1);
    
    /// getter method with two extra parameters
    typedef RetT (ClassT::*Getter2)(ExtrParamT1, ExtrParamT2);
    
    /// setter method with two extra parameters
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
    , getterWrapper(getter)
    , constGetter(constGetter)
    , setterWrapper(setter)
    {
         type = &TypeRegister::getTypeReg().getType<PropT>();
        
        // if the setter is not null we can set the property
        if (setter) flags |= Settable;
         
        // initialize bounds
         getTypeBounds<PropT>(minValue, maxValue);
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
    , getterWrapper(getter)
    , constGetter(constGetter)
    , setterWrapper(setter)
    , extrArg1(extrArg1)
    {
        type = &TypeRegister::getTypeReg().getType<PropT>();
                
        // if the setter is not null we can set the property
        if (setter) flags |= Settable;
        
        // initialize bounds
        getTypeBounds<PropT>(minValue, maxValue);
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
    , getterWrapper(getter)
    , constGetter(constGetter)
    , setterWrapper(setter)
    , extrArg1(extrArg1)
    , extrArg2(extrArg2)
    {
        type = &TypeRegister::getTypeReg().getType<PropT>();
        
        // if the setter is not null we can set the property
        if (setter) flags |= Settable;
        
        // initialize bounds
        getTypeBounds<PropT>(minValue, maxValue);
    }
    
    char getFlags() const
    {
        return flags;
    }
    
    Property& setFlags(char flags)
    {
        // If the setter pointer is NULL no way we can change the property to a settable one.
        if (!setterWrapper.setter) flags &= ~Settable;
        
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
    
    bool getGetByNonConstRef()
    {
        return IsReference<RetT>::value && !IsConst<RetT>::value;
    }
    
    bool getSetByNonConstRef()
    {
        return IsReference<ParamT>::value && !IsConst<RetT>::value;
    }
    
    Variant getData(const Variant& objPtr) const
    {
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = *objPtr.to<ClassT*>();
        
        // we cannot call a non constant getter of a constant instance
        if (objPtr.isPointedConst() && !constGetter) throw VariantCostnessException(objPtr.getType());
                
        const PropT& data = getterWrapper(objRef, extrArg1, extrArg2);
        return Variant(const_cast<PropT&>(data), ReturnVariantFlags<RetT>::flags);
    }
    
    void setData(const Variant& objPtr, const Variant& data) const
    {
        // check whether the property is settable
        if (!setterWrapper.setter) throw PropertySetException(*this);
        
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = *objPtr.to<ClassT*>();
        
        // retrieve the new data value
        PropT& extractedValue = data.to<PropT>();
        
        // check whether the new value is into the specified bounds
        if (!checkValueBounds(extractedValue, minValue, maxValue)) return;
        
        // the data is set calling the setter method wrapper
        setterWrapper(objRef, extractedValue, extrArg1, extrArg2);
    }
    
private:

    /// The getter method wrapper
    GetterWrapper<ClassT, RetT, ExtrParamT1, ExtrParamT2> getterWrapper;
    
    /// Whether the getter method is constant
    bool constGetter;
    
    /// The setter method wrapper
    SetterWrapper<ClassT, ParamT, ExtrParamT1, ExtrParamT2> setterWrapper;
    
    /// First extra parameter to pass when calling the getter and setter
    ExtrParamT1 extrArg1;
    
    /// Second extra parameter to pass when calling the getter and setter
    ExtrParamT2 extrArg2;
    
    /// The minimum allowed value for this property.
    NumT minValue;
    
    /// The maximum allowed value for this property.
    NumT maxValue;
};

} // namespace extmr

#endif	/* PROPERTYGETTERNSETTER_HPP */

