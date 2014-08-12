/******************************************************************************      
 *      Extended Mirror: Function.hpp                                         *
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


#ifndef XM_FUNCTION_HPP
#define	XM_FUNCTION_HPP

#include <XM/Parameter.hpp>

namespace xm{

class Type;
bool operator<(const Type&, const Type&);

/**
 * Describes a function that has been registered into the reflection
 * mechanism.
 * 
 */
class Function : public virtual Name
{
public:
    enum ReturnMode
    {
        None = 0,
        Value = 1,
        Reference = 2,
        ConstReference = 6
    };
    
    /**
     * Construct a method with just the name.
     * 
     * @param name The method name.
     */
    Function(const std::string& name);
    
    /**
     * Construct a method with just the name.
     * 
     * @param name The method name.
     */
    Function(const Namespace& name_space, const std::string& name);
    
    /**
     * Construct a Method with the given given signature.
     * 
     * @param name The name of the method.
     * @param retType The Type of the returned type.
     * @param paramType0 The Type of the first parameter type.
     * @param paramType1 The Type of the second parameter type.
     * @param paramType2 The Type of the third parameter type.
     * @param paramType3 The Type of the fourth parameter type.
     * @param paramType4 The Type of the fifth parameter type.
     * @param paramType5 The Type of the sixth parameter type.
     * @param paramType6 The Type of the seventh parameter type.
     * @param paramType7 The Type of the eighth parameter type.
     */
    Function
    (
        const std::string& name,
        const Type& retType,
        const Type& paramType0 = getType<void>(),
        const Type& paramType1 = getType<void>(),
        const Type& paramType2 = getType<void>(),
        const Type& paramType3 = getType<void>(),
        const Type& paramType4 = getType<void>(),
        const Type& paramType5 = getType<void>(),
        const Type& paramType6 = getType<void>(),
        const Type& paramType7 = getType<void>()
    );
    
    /**
     * Add an other parameter to the parameter list.
     * 
     * @param param The new parameter.
     */
    void addParameter(const Parameter& param);
    
    /**
     * Get the descriptor of the returned type of the function.
     * 
     * @return A reference to a constant Type of the function returned type.
     */
    const Type& getReturnType() const;
    
    /**
     * Ask for the mode the function returns, that is by value, reference
     * or constant reference.
     * 
     * @return The return mode.
     */
    virtual Function::ReturnMode getReturnMode() const;
    
    /**
     * Get a vector with the Parameters.
     * 
     * @return A vector containing the Parameters.
     */
    const Const_Prameter_Vector& getParameters() const;
    
    /**
     * Call the function.
     * 
     * @param arg0 Argument 0 ( instance for non static methods )
     * @param arg1 Argument 1.
     * @param arg2 Argument 2.
     * @param arg3 Argument 3.
     * @param arg4 Argument 4.
     * @param arg5 Argument 5.
     * @param arg6 Argument 6.
     * @param arg7 Argument 7.
     * @return A Variant containing the return value.
     */
    Variant call
    (
        const Variant& arg0 = Variant::Null,
        const Variant& arg1 = Variant::Null,
        const Variant& arg2 = Variant::Null,
        const Variant& arg3 = Variant::Null,
        const Variant& arg4 = Variant::Null,
        const Variant& arg5 = Variant::Null,
        const Variant& arg6 = Variant::Null,
        const Variant& arg7 = Variant::Null
    ) const;
    
    /**
     * Call the function.
     * 
     * @param args A vector containing the arguments of the function.
     * @return A Variant containing the return value.
     */
    Variant callV(std::vector<Variant> args) const;
    
    /**
     * Set the default argument list.
     * 
     * @param arg# the nth default argument.
     */
    void setDefaultArgs
    (
        const Variant& arg0 = Variant::Null,
        const Variant& arg1 = Variant::Null,
        const Variant& arg2 = Variant::Null,
        const Variant& arg3 = Variant::Null,
        const Variant& arg4 = Variant::Null,
        const Variant& arg5 = Variant::Null,
        const Variant& arg6 = Variant::Null,
        const Variant& arg7 = Variant::Null
    );
    
protected:
    virtual Variant callImpl
    (
        Variant& arg0,
        Variant& arg1,
        Variant& arg2,
        Variant& arg3,
        Variant& arg4,
        Variant& arg5,
        Variant& arg6,
        Variant& arg7
    ) const;
    
    // The returned type
    const Type* retType_;
    
    // Whether the function full signature is provided
    // (used in comparing two functions)
    bool fullSignature_;
    
    // The parameter list
    Const_Prameter_Vector params_;
    
    std::vector<Variant> defaults_;
    
    friend bool operator<(const Function& f1, const Function& f2);
};


bool inline operator<(const Function& f1, const Function& f2)
{
    if (f1.name_ < f2.name_)
        return true;
    
    if (f2.name_ < f1.name_)
        return false;
    
    if (!f1.fullSignature_ || !f2.fullSignature_)
        return false;
    
    ushort paramN1 = f1.params_.size();
    ushort paramN2 = f2.params_.size();
    ushort paramN = std::min(paramN1, paramN2);
    for (uint i = 0; i < paramN; i++)
    {
        if (f1.params_[i]->type
            < f2.params_[i]->type)
            return true;
    }
    if (paramN1 < paramN2) return true;
    return false;
}


typedef std::set<Function*, PtrCmpByVal<Function> > Function_Set;
typedef std::set<const Function*, PtrCmpByVal<Function> > Const_Function_Set;


#define _XM_FUNCTION_PUSH_PARAMS                     \
this->retType_ = &retType;                              \
if (paramType0 != getType<void>())                      \
    params_.push_back(new Parameter(paramType0));       \
if (paramType1 != getType<void>())                      \
    params_.push_back(new Parameter(paramType1));       \
if (paramType2 != getType<void>())                      \
    params_.push_back(new Parameter(paramType2));       \
if (paramType3 != getType<void>())                      \
    params_.push_back(new Parameter(paramType3));       \
if (paramType4 != getType<void>())                      \
    params_.push_back(new Parameter(paramType4));       \
if (paramType5 != getType<void>())                      \
    params_.push_back(new Parameter(paramType5));       \
if (paramType6 != getType<void>())                      \
    params_.push_back(new Parameter(paramType6));       \
if (paramType7 != getType<void>())                      \
    params_.push_back(new Parameter(paramType7));       \

} // namespace xm

#endif	/* XM_FUNCTION_HPP */

