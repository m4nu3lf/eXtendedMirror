/******************************************************************************      
 *      Extended Mirror: Method.hpp                                         *
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


#ifndef XM_METHOD_HPP
#define	XM_METHOD_HPP

#include <XM/Parameter.hpp>
#include <XM/ParamLists.hpp>


namespace xm{

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
     * @param uName The unqualified method name.
     */
    Method(const std::string& uName = "");
    
    /**
     * Construct a method with just the owner and the name.
     * 
     * @param uName The unqualified method name.
     * @param owner The owner class.
     */
    Method(const std::string& uName, const Class &owner);
        
    /**
     * Construct a Method with the given owner and given signature.
     * 
     * @param uName The unqualified name of the method.
     * @param retType The Type of the returned value.
     * @param paramType<N> The Type of the Nth parameter.
     */
    Method
    (
        const std::string& uName,
        const Type& retType,
        const Class& owner,
        _XM_METHOD_CONSTRUCTOR_PARAMS
    );

    /**
     * If the method has a complete signature.
     *
     * @return  True if the method has full signature.
     */
    bool hasFullSignature() const;
    
    /**
     * Get the method signature.
     * 
     * @return The method signature.
     */
    std::string getSignature() const;
    
    /**
     * Ask if the method is constant.
     * 
     * @return True if the method is constant, false otherwise.
     */
    virtual bool isConst() const;

    bool before(const Item& item) const;
    
protected:

    std::string signature_;
    
    /// Whether the method is constant.
    bool constant_;
    
    friend bool operator<(const Method& m1, const Method& m2);
};


bool inline operator<(const Method& m1, const Method& m2)
{
    return dynamic_cast<const Function&>(m1)
            < dynamic_cast<const Function&>(m2);
}


typedef std::set<Method*, PtrCmpByVal<Method> > Method_Set;
typedef std::set<const Method*, PtrCmpByVal<Method> > Const_Method_Set;

} // namespace xm

#endif	/* XM_METHOD_HPP */

