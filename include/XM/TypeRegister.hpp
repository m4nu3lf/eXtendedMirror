/******************************************************************************      
 *      Extended Mirror: TypeRegister.hpp                                     *
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


#ifndef XM_TYPEXM_HPP
#define XM_TYPEXM_HPP

namespace xm{


typedef std::set<const Type*, PtrCmpById<Type> > Const_Type_SetById;
typedef std::set<const Class*, PtrCmpById<Class> > Const_Class_SetById;


class TypeRegister
{
public:
    const Type& getType(const std::string& typeName) const;
    
    const Type& getType(const std::type_info& cppType) const;
    
    const Class& getClass(const std::string& className) const;
    
    const Class& getClass(const std::type_info& cppType) const;
    
    const Template& getTemplate(const std::string& templateName) const;
    
    template<typename T>
    const Type& getTypeOf(const T& obj) const;
    
    template<typename T>
    const Class& getClassOf(const T& obj) const;
    
    template<typename T>
    const Type& getType() const;
    
    template<typename T>
    const Class& getClass() const;
    
    const Namespace& getNamespace(const std::string& name = "");
    
    template<typename T> const Type& registerType();
    
    template<typename T> const Class& registerClass();
    
    void unregisterType(const std::string& typeName);
     
    void unregisterType(const std::type_info& cppType);
    
    /**
     * Set a function that is called whenever a type is registered within the
     * type register and the registered type is passed to this function.
     * 
     * @param callBackFnc
     */
    void setRegCallBack(void (*callBackFnc)(const Type&));
    
    static TypeRegister& getSingleton();
    
private:

     /*
      * Singleton restrictions.
      */
    TypeRegister();
    
    TypeRegister(const TypeRegister&);
    TypeRegister& operator=(const TypeRegister&);
    
    ~ TypeRegister();
    
    /**
     * This method is called by registerType, after the type qualifiers are
     * removed from the type.
     * 
     * @return the registered type.
     */
    template<typename T> Type& registerType_();
    
    /**
     * Return the function pointer of the callback function to call after each
     * type registration.
     * 
     * @return The callback function pointer.
     */
    static void (*getRegCallBack())(const Type&);
    
    // the global ( or root ) namespace
    Namespace globalNamespace_;
    
    // types and classes sets sorted by type id.
    Const_Type_SetById types_;
    Const_Class_SetById classes_;
    
    // this function needs to add Templates to the register
    template<typename T>
    friend Type* createCompoundClass();
};

} // namespace xm

#endif // TYPEXM_HPP
