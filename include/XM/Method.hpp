/******************************************************************************      
 *      Extended Mirror: Method.hpp                                         *
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


#ifndef XM_METHOD_HPP
#define	XM_METHOD_HPP

#include <XM/Parameter.hpp>


namespace xm{


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
class Method : public Member, public Function
{
public:
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
     * @param paramType0 The Type of the first parameter type.
     * @param paramType1 The Type of the second parameter type.
     * @param paramType2 The Type of the third parameter type.
     * @param paramType3 The Type of the fourth parameter type.
     * @param paramType4 The Type of the fifth parameter type.
     * @param paramType5 The Type of the sixth parameter type.
     * @param paramType6 The Type of the seventh parameter type.
     * @param paramType7 The Type of the eighth parameter type.
     */
    Method
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
     * Construct a Method with the given owner and given signature.
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
    Method
    (
        const Class& owner,
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
     * Get the method signature.
     * 
     * @return The method signature.
     */
    const std::string& getSignature() const;
    
    /**
     * Ask if the method is constant.
     * 
     * @return True if the method is constant, false otherwise.
     */
    virtual bool isConst() const;
    
protected:

    std::string signature_;
    
    /// Whether the method is constant.
    bool constant_;
    
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

} // namespace xm

#endif	/* XM_METHOD_HPP */

