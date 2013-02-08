/* 
 * File:   MethodImpl.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 20 October 2012, 22.11
 */

#ifndef EXTMR_METHODIMPL_HPP
#define	EXTMR_METHODIMPL_HPP

#include <EXTMR/MemberWrappers.hpp>
#include <EXTMR/Exceptions/ConstnessBreak.hpp>

namespace extmr{

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
    
    /**
     * Constructor for a method with no parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(), bool constant = false)
            : Method(name)
            , methodWrapper(reinterpret_cast<GeneralMethod>(method))
            , constant(constant) 
    {
        // retrieve the type of the returning value
        retType = &TypeRegister::getTypeReg().getType<RetT>();
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with one parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1), bool constant = false)
            : Method(name)
            , methodWrapper(reinterpret_cast<GeneralMethod>(method))
            , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        params.push_back(param1);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with two parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2), bool constant = false)
            : Method(name)
            , methodWrapper(reinterpret_cast<GeneralMethod>(method))
            , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        params.push_back(param1);
        params.push_back(param2);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with three parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3), bool constant = false)
            : Method(name)
            , methodWrapper(reinterpret_cast<GeneralMethod>(method))
            , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with four parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4), bool constant = false)
            : Method(name)
            , methodWrapper(reinterpret_cast<GeneralMethod>(method))
            , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        Parameter* param4 = new Parameter(typeReg.getType<ParamT4>(), IsNonConstReference<ParamT4>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        params.push_back(param4);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with five parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5), bool constant = false)
        : Method(name)
        , methodWrapper(reinterpret_cast<GeneralMethod>(method))
        , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        Parameter* param4 = new Parameter(typeReg.getType<ParamT4>(), IsNonConstReference<ParamT4>::value);
        Parameter* param5 = new Parameter(typeReg.getType<ParamT5>(), IsNonConstReference<ParamT5>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        params.push_back(param4);
        params.push_back(param5);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with six parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6), bool constant = false)
        : Method(name)
        , methodWrapper(reinterpret_cast<GeneralMethod>(method))
        , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        Parameter* param4 = new Parameter(typeReg.getType<ParamT4>(), IsNonConstReference<ParamT4>::value);
        Parameter* param5 = new Parameter(typeReg.getType<ParamT5>(), IsNonConstReference<ParamT5>::value);
        Parameter* param6 = new Parameter(typeReg.getType<ParamT6>(), IsNonConstReference<ParamT6>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        params.push_back(param4);
        params.push_back(param5);
        params.push_back(param6);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with seven parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7), bool constant = false)
        : Method(name)
        , methodWrapper(reinterpret_cast<GeneralMethod>(method))
        , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        Parameter* param4 = new Parameter(typeReg.getType<ParamT4>(), IsNonConstReference<ParamT4>::value);
        Parameter* param5 = new Parameter(typeReg.getType<ParamT5>(), IsNonConstReference<ParamT5>::value);
        Parameter* param6 = new Parameter(typeReg.getType<ParamT6>(), IsNonConstReference<ParamT6>::value);
        Parameter* param7 = new Parameter(typeReg.getType<ParamT7>(), IsNonConstReference<ParamT7>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        params.push_back(param4);
        params.push_back(param5);
        params.push_back(param6);
        params.push_back(param7);
        
        // method has full signature
        fullSignature = true;
    }
    
    /**
     * Constructor for a method with eight parameters.
     * 
     * @param name The method name.
     * @param method The method pointer.
     * @param constant Whether the method is constant.
     */
    MethodImpl(const std::string& name, RetT (ClassT::*method)(ParamT1, ParamT2, ParamT3, ParamT4, ParamT5, ParamT6, ParamT7, ParamT8), bool constant = false)
        : Method(name)
        , methodWrapper(reinterpret_cast<GeneralMethod>(method))
        , constant(constant)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();
        
        // retrieve the type of the returning value
        retType = &typeReg.getType<RetT>();
        
        // build and store the Parameters
        Parameter* param1 = new Parameter(typeReg.getType<ParamT1>(), IsNonConstReference<ParamT1>::value);
        Parameter* param2 = new Parameter(typeReg.getType<ParamT2>(), IsNonConstReference<ParamT2>::value);
        Parameter* param3 = new Parameter(typeReg.getType<ParamT3>(), IsNonConstReference<ParamT3>::value);
        Parameter* param4 = new Parameter(typeReg.getType<ParamT4>(), IsNonConstReference<ParamT4>::value);
        Parameter* param5 = new Parameter(typeReg.getType<ParamT5>(), IsNonConstReference<ParamT5>::value);
        Parameter* param6 = new Parameter(typeReg.getType<ParamT6>(), IsNonConstReference<ParamT6>::value);
        Parameter* param7 = new Parameter(typeReg.getType<ParamT7>(), IsNonConstReference<ParamT7>::value);
        Parameter* param8 = new Parameter(typeReg.getType<ParamT8>(), IsNonConstReference<ParamT8>::value);
        params.push_back(param1);
        params.push_back(param2);
        params.push_back(param3);
        params.push_back(param4);
        params.push_back(param5);
        params.push_back(param6);
        params.push_back(param7);
        params.push_back(param8);
        
        // method has full signature
        fullSignature = true;
    }
    
    bool getReturnByNonConstRef() const
    {
        return IsNonConstReference<RetT>::value;
    }
    
    bool isConst() const
    {
        return constant;
    }
    
    /**
     * Call the method.
     * 
     * @param objPtr A pointer to an object of the class this method belongs to.
     * @param arg1 Argument 1.
     * @param arg2 Argument 2.
     * @param arg3 Argument 3.
     * @param arg4 Argument 4.
     * @param arg5 Argument 5.
     * @param arg6 Argument 6.
     * @param arg7 Argument 7.
     * @param arg8 Argument 8.
     * @return A Variant object containing the return value.
     */
    Variant call(
                    const Variant& objPtr,
                    const Variant& arg1 = Variant(),
                    const Variant& arg2 = Variant(),
                    const Variant& arg3 = Variant(),
                    const Variant& arg4 = Variant(),
                    const Variant& arg5 = Variant(),
                    const Variant& arg6 = Variant(),
                    const Variant& arg7 = Variant(),
                    const Variant& arg8 = Variant()
                ) const
    {        
        ClassT& objRef = *objPtr.to<ClassT*>();
        
        // cannot call a non constant method of a constant instance
        if (objPtr.isPointedConst() && !constant) throw ConstnessBreak(objPtr.getType());
        
        Variant var = methodWrapper(objRef, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        var.setCopyByRef(IsReference<RetT>::value);
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
    > methodWrapper;
    
    /// Whether the method is constant.
    bool constant;
};

} // namespace extmr

#endif	/* EXTMR_METHODIMPL_HPP */

