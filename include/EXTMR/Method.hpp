/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_METHOD_HPP
#define	EXTMR_METHOD_HPP

#include <EXTMR/Parameter.hpp>

#include "Variant.hpp"

namespace extmr{

// we need some forward declarations
class Type;
bool operator<(const Type&, const Type&);

/**
 * Describes a method of a class that has been registered into the reflection
 * mechanism.
 * 
 * Note that a Method is related to the class and not to the object (instances).
 * This class is can be used as a key for set containers but the effective
 * implementation is delegated to subclasses.
 */
class Method : public Member
{
public:
    enum ReturnMode
    {
        Value = 0,
        Reference = 1,
        ConstReference = 3
    };
    
    /**
     * Construct a method with just the name.
     * 
     * @param name The method name.
     */
    Method(const std::string& name);
    
    
    /**
     * Construct a method with just the owner and the name.
     * 
     * @param owner The owner class.
     * @param name The method name.
     */
    Method(const Class& owner, const std::string& name);
    
    /**
     * Construct a Method with the given given signature.
     * 
     * @param name The name of the method.
     * @param retType The Type of the returned type.
     * @param paramType1 The Type of the first parameter type.
     * @param paramType2 The Type of the second parameter type.
     * @param paramType3 The Type of the third parameter type.
     * @param paramType4 The Type of the fourth parameter type.
     * @param paramType5 The Type of the fifth parameter type.
     * @param paramType6 The Type of the sixth parameter type.
     * @param paramType7 The Type of the seventh parameter type.
     * @param paramType8 The Type of the eighth parameter type.
     */
    Method
    (
        const std::string& name,
        const Type& retType,
        const Type& paramType1 = getType<void>(),
        const Type& paramType2 = getType<void>(),
        const Type& paramType3 = getType<void>(),
        const Type& paramType4 = getType<void>(),
        const Type& paramType5 = getType<void>(),
        const Type& paramType6 = getType<void>(),
        const Type& paramType7 = getType<void>(),
        const Type& paramType8 = getType<void>()
    );
    
    /**
     * Construct a Method with the given owner and given signature.
     * 
     * @param name The name of the method.
     * @param retType The Type of the returned type.
     * @param paramType1 The Type of the first parameter type.
     * @param paramType2 The Type of the second parameter type.
     * @param paramType3 The Type of the third parameter type.
     * @param paramType4 The Type of the fourth parameter type.
     * @param paramType5 The Type of the fifth parameter type.
     * @param paramType6 The Type of the sixth parameter type.
     * @param paramType7 The Type of the seventh parameter type.
     * @param paramType8 The Type of the eighth parameter type.
     */
    Method
    (
        const Class& owner,
        const std::string& name,
        const Type& retType,
        const Type& paramType1 = getType<void>(),
        const Type& paramType2 = getType<void>(),
        const Type& paramType3 = getType<void>(),
        const Type& paramType4 = getType<void>(),
        const Type& paramType5 = getType<void>(),
        const Type& paramType6 = getType<void>(),
        const Type& paramType7 = getType<void>(),
        const Type& paramType8 = getType<void>()
    );
    
    
    /**
     * Add an other parameter to the parameter list.
     * 
     * @param param The new parameter.
     */
    void addParameter(const Parameter& param);
    
    /**
     * Get the descriptor of the returned type of the method.
     * 
     * @return A reference to a constant Type of the method returned type.
     */
    const Type& getReturnType() const;
    
    /**
     * Ask for the mode the methods returns, that is by value, reference
     * or constant reference.
     * 
     * @return The return mode.
     */
    virtual Method::ReturnMode getReturnMode() const;
    
    /**
     * Get a vector with the Parameters.
     * 
     * @return A vector containing the Parameters.
     */
    const Const_Prameter_Vector& getParameters() const;
    
    /**
     * Ask if the method is constant.
     * 
     * @return True if the method is constant, false otherwise.
     */
    virtual bool isConst() const;
    
    /**
     * Call the method.
     * 
     * @param self A reference to an object.
     * @param arg1 Argument 1.
     * @param arg2 Argument 2.
     * @param arg3 Argument 3.
     * @param arg4 Argument 4.
     * @param arg5 Argument 5.
     * @param arg6 Argument 6.
     * @param arg7 Argument 7.
     * @param arg8 Argument 8.
     * @return A Variant containing the return value.
     */
    Variant call
    (
        const RefVariant& self,
        const Variant& arg1 = Variant::Null,
        const Variant& arg2 = Variant::Null,
        const Variant& arg3 = Variant::Null,
        const Variant& arg4 = Variant::Null,
        const Variant& arg5 = Variant::Null,
        const Variant& arg6 = Variant::Null,
        const Variant& arg7 = Variant::Null,
        const Variant& arg8 = Variant::Null
    ) const;
    
    /**
     * Call the method.
     * 
     * @param self A reference to an object.
     * @param args A vector containing the arguments of the method.
     * @return A Variant containing the return value.
     */
    Variant callV(const RefVariant& self, std::vector<Variant> args)
    const;
    
    /**
     * Set the default argument list.
     * 
     * @param arg# the nth default argument.
     */
    void setDefaultArgs
    (
        const Variant& arg1 = Variant::Null,
        const Variant& arg2 = Variant::Null,
        const Variant& arg3 = Variant::Null,
        const Variant& arg4 = Variant::Null,
        const Variant& arg5 = Variant::Null,
        const Variant& arg6 = Variant::Null,
        const Variant& arg7 = Variant::Null,
        const Variant& arg8 = Variant::Null
    );
    
protected:
    virtual Variant callImpl
    (
        const RefVariant& objPtr,
        const Variant& arg1,
        const Variant& arg2,
        const Variant& arg3,
        const Variant& arg4,
        const Variant& arg5,
        const Variant& arg6,
        const Variant& arg7,
        const Variant& arg8
    ) const;
    
    // The returned type
    const Type* retType_;
    
    // Whether the method full signature is provided
    // (used in comparing two methods)
    bool fullSignature_;
    
    // The parameter list
    Const_Prameter_Vector params_;
    
    std::vector<Variant> defaults_;
    
    // Need to know if the method has a full signature
    friend class MethodNotFoundException;
    
    friend bool operator<(const Method& m1, const Method& m2);
};


bool inline operator<(const Method& m1, const Method& m2)
{
    if (static_cast<const Member&>(m1) < static_cast<const Member&>(m2))
        return true;
    
    if (static_cast<const Member&>(m2) < static_cast<const Member&>(m1))
        return false;
    
    if (!m1.fullSignature_ || !m2.fullSignature_)
        return false;
    
    ushort paramN1 = m1.params_.size();
    ushort paramN2 = m2.params_.size();
    ushort paramN = std::min(paramN1, paramN2);
    for (uint i = 0; i < paramN; i++)
    {
        if (m1.params_[i]->type
            < m2.params_[i]->type)
            return true;
    }
    if (paramN1 < paramN2) return true;
    return false;
}


typedef std::set<Method*, PtrCmpByVal<Method> > Method_Set;
typedef std::set<const Method*, PtrCmpByVal<Method> > Const_Method_Set;

} // namespace extmr

#endif	/* EXTMR_METHOD_HPP */

