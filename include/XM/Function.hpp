/******************************************************************************      
 *      Extended Mirror: Function.hpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
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
#include <XM/ParamLists.hpp>

namespace xm{

class Type;
bool operator<(const Type&, const Type&);

/**
 * Describes a function that has been registered into the reflection
 * mechanism.
 * 
 */
class Function : public virtual Item
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
    Function(const std::string& name = "");
    
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
     * @param retType The Type of the returned value.
     * @param paramType<N> The Type of the Nth parameter.
     */
    Function
    (
        const std::string& name,
        const Type& retType,
	_XM_FUNCTION_CONSTRUCTOR_PARAMS
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
     * @param arg<N> The Nth Argument.
     * @return A Variant containing the return value.
     */
    Variant call
    (
	_XM_FUNCTION_CALL_PARAMS
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
	_XM_FUNCTION_CALL_PARAMS
    );
    
protected:
    virtual Variant callImpl
    (
	_XM_FUNCTION_CALLIMPL_PARAMS
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
    if (f1.getName() < f2.getName())
        return true;
    
    if (f2.getName() < f1.getName())
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


} // namespace xm

#endif	/* XM_FUNCTION_HPP */

