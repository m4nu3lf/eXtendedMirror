/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_METHODIMPL_HPP
#define	EXTMR_METHODIMPL_HPP

#include <EXTMR/MethodWrappers.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>


namespace extmr{
    
#define _EXTMR_NORMALMETHOD_CONSTRUCTOR(...)                                   \
MethodImpl(const std::string& name,                                            \
           RetT (ClassT::*method)(__VA_ARGS__),                                \
           bool constant = false) :                                            \
    Method(name, getType<RetT>(), getType<ParamT1>(), getType<ParamT2>(),      \
        getType<ParamT3>(), getType<ParamT4>(), getType<ParamT5>(),            \
        getType<ParamT6>(), getType<ParamT7>(), getType<ParamT8>()),           \
    methodWrapper_(reinterpret_cast<GeneralMethod>(method)),                   \
    constant_(constant)                                                        \
{                                                                              \
}
    

template<typename T>
struct VoidToEmpty
{
    typedef T Type;
};


template<>
struct VoidToEmpty<void>
{
    typedef Empty Type;
};


template
<
        class ClassT,
        typename RetT,
        typename ParamT1 = void,
        typename ParamT2 = void,
        typename ParamT3 = void,
        typename ParamT4 = void,
        typename ParamT5 = void,
        typename ParamT6 = void,
        typename ParamT7 = void,
        typename ParamT8 = void
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
        const Variant& self,
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
            typename VoidToEmpty<ParamT1>::Type,
            typename VoidToEmpty<ParamT2>::Type,
            typename VoidToEmpty<ParamT3>::Type,
            typename VoidToEmpty<ParamT4>::Type,
            typename VoidToEmpty<ParamT5>::Type,
            typename VoidToEmpty<ParamT6>::Type,
            typename VoidToEmpty<ParamT7>::Type,
            typename VoidToEmpty<ParamT8>::Type
    > methodWrapper_;
    
    /// Whether the method is constant.
    bool constant_;
};

} // namespace extmr

#endif	/* EXTMR_METHODIMPL_HPP */

