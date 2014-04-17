/******************************************************************************      
 *      Extended Mirror: MethodImpl.hpp                                       *
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


#ifndef EXTMR_METHODIMPL_HPP
#define	EXTMR_METHODIMPL_HPP

#include <EXTMR/MethodWrappers.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>


namespace extmr{
    
#define _EXTMR_NORMALMETHOD_CONSTRUCTOR(...)                                   \
MethodImpl(const std::string& name,                                            \
           RetT (ClassT::*method)(__VA_ARGS__),                                \
           bool constant = false) :                                            \
    Method(getClass<ClassT>(), name, getType<RetT>(), getType<ParamT1>(),      \
    getType<ParamT2>(), getType<ParamT3>(), getType<ParamT4>(),                \
    getType<ParamT5>(), getType<ParamT6>(), getType<ParamT7>(),                \
    getType<ParamT8>()),                                                       \
    methodWrapper_(reinterpret_cast<GeneralMethod>(method)),                   \
    constant_(constant)                                                        \
{                                                                              \
}


template
<
        class ClassT,
        typename RetT,
        typename ParamT1 = Empty,
        typename ParamT2 = Empty,
        typename ParamT3 = Empty,
        typename ParamT4 = Empty,
        typename ParamT5 = Empty,
        typename ParamT6 = Empty,
        typename ParamT7 = Empty,
        typename ParamT8 = Empty
>
class MethodImpl : public Method
{
public:
    
    /// type of a generic method belonging to ClassT
    typedef void (ClassT::*GeneralMethod)(...);
    
    
     _EXTMR_NORMALMETHOD_CONSTRUCTOR()
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3, ParamT4)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3, ParamT4,
             ParamT5)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3, ParamT4,
             ParamT5, ParamT6)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3, ParamT4,
             ParamT5, ParamT6, ParamT7)
     _EXTMR_NORMALMETHOD_CONSTRUCTOR(ParamT1, ParamT2, ParamT3, ParamT4,
             ParamT5, ParamT6, ParamT7, ParamT8)
    
    
    Method::ReturnMode getReturnMode() const
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
    
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (
        const RefVariant& self,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
     ) const
    {        
        ClassT& objRef = self.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (self.isConst() && !constant_)
            throw VariantCostnessException(self.getType());
        
        Variant var = methodWrapper_(objRef, arg1, arg2, arg3, arg4, arg5, arg6,
                arg7, arg8);
        if (IsConst<RetT>::value) var.setConst();
        return var;
    }
    
private:
    /// Store the pointer to the method into a wrapper.
    MethodWrapper
    <
            ClassT,
            RetT,
            ParamT1,
            ParamT2,
            ParamT3,
            ParamT4,
            ParamT5,
            ParamT6,
            ParamT7,
            ParamT8
    > methodWrapper_;
    
    /// Whether the method is constant.
    bool constant_;
};

} // namespace extmr

#endif	/* EXTMR_METHODIMPL_HPP */

