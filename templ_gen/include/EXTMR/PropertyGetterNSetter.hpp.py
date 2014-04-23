content = """
/******************************************************************************      
 *      Extended Mirror: PropertyGetterNSetter.hpp                            *
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

""" + WARNING_MESSAGE + """

#ifndef EXTMR_PROPERTYGETTERNSETTER_HPP
#define	EXTMR_PROPERTYGETTERNSETTER_HPP

#include <limits>

#include <EXTMR/NumericalUtils.hpp>
#include <EXTMR/Exceptions/PropertySetException.hpp>
#include <EXTMR/Exceptions/PropertyRangeException.hpp>

#include "Variant.hpp"
#include "Property.hpp"
#include "TypeTraits.hpp"


namespace extmr{


template<typename T>
struct ReturnVariantFlags
{
    static const char flags =
        (IsReference<T>::value * (Variant::Reference | Variant::CpyByRef)) |
        (IsConst<T>::value * Variant::Const);
};


/**
 * Implementation of the Property class. Handles a property from a getter
 * and setter couple.
 */"""
for n_extr_param in range(EXTMR_GET_N_SET_EXTRA_PARAM_MAX + 1):
    content += """
template
<
    class ClassT,
    typename RetT,
    typename ParamT""" + gen_seq(""",
    typename ExtrParamT$""", n_extr_param) + """
>
class PropertyGetterNSetter_""" + str(n_extr_param) + """_ExtrParams : public Property
{
public:
    
    // define the property type after removing the reference and all the
    // cv qualifiers
    typedef typename RemoveReference<RetT>::Type NonRefT; 
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type PropT;
    
    // A numerical type. The same of PropT if PropT is numerical.
    typedef typename ToNumerical<PropT>::Type NumT;
    
    // getter method signature
    typedef RetT (ClassT::*Getter)
    (""" + gen_seq("""
        ExtrParamT$""", n_extr_param, ",") + """
    );
    
    // setter method signature
    typedef void (ClassT::*Setter)
    (
        ParamT""" + gen_seq(""",
        ExtrParamT$""", n_extr_param) + """
    );
    
    PropertyGetterNSetter_""" + str(n_extr_param) + """_ExtrParams
    (
        const std::string& name,
        Getter getter,
        bool constGetter,
        Setter setter""" + gen_seq(""",
        ExtrParamT$ extrArg$""", n_extr_param) + """
    ) : Property(extmr::getClass<ClassT>(), name),
        getter_(getter),
        constGetter_(constGetter),
        setter_(setter)""" + gen_seq(""",
        extrArg$_(extrArg$)""", n_extr_param) + """
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
        if (!setter_) flags &= ~Settable;
        
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
        if (!setter_)
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
    
    
    Variant getData(const RefVariant& self) const
    {
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = self.as<ClassT>();
        
        // we cannot call a non constant getter of a constant instance
        if (self.isConst() && !constGetter_)
            throw VariantCostnessException(self.getType());
                
        const PropT& data = (objRef.*getter_)
        (""" + gen_seq("""
            extrArg$_""", n_extr_param, ",") + """
        );
        return Variant(const_cast<PropT&>(data),
                ReturnVariantFlags<RetT>::flags);
    }
    
    
    void setData(const RefVariant& self, const Variant& data) const
    {
        // check whether the property is settable
        if (!setter_)
            throw PropertySetException(*this);
        
        // the pointer is retrieved from the variant and stored as a reference
        ClassT& objRef = self.as<ClassT>();
        
        // retrieve the new data value
        PropT& extractedValue = data.as<PropT>();
        
        // check whether the new value is into the specified bounds
        if (!checkValueBounds(extractedValue, minValue_, maxValue_)) return;
        
        // the data is set calling the setter method wrapper
        (objRef.*setter_)
        (
            extractedValue""" + gen_seq(""",
            extrArg$_""", n_extr_param) + """
        );
    }
    
private:
    
    /// Whether the getter method is constant
    bool constGetter_;

    Getter getter_;
    Setter setter_;
    
    /// Extra parameter to pass when calling the getter and setter
    """ + gen_seq("""ExtrParamT$ extrArg$_;
    """, n_extr_param) + """
    /// The minimum allowed value for this property.
    NumT minValue_;
    
    /// The maximum allowed value for this property.
    NumT maxValue_;
};

"""

content += """

} // namespace extmr

#endif	/* EXTMR_PROPERTYGETTERNSETTER_HPP */"""

