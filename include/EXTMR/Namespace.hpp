/******************************************************************************      
 *      Extended Mirror: Namespace.hpp                                        *
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


#ifndef EXTMR_NAMESPACE_HPP
#define	EXTMR_NAMESPACE_HPP

namespace extmr {
    
class Type;
class Class;
class Template;

typedef std::set<const Type*, PtrCmpByVal<Type> > Const_Type_SetById;
typedef std::set<Type*, PtrCmpByVal<Type> > Type_SetById;
typedef std::set<const Type*, PtrCmpByName<Type> > Const_Type_SetByName;
typedef std::set<Type*, PtrCmpByName<Type> > Type_Set_ByName;
typedef std::set<const Class*, PtrCmpByVal<Type> > Const_Class_SetById;
typedef std::set<Class*, PtrCmpByVal<Type> > Class_SetById;
typedef std::set<const Class*, PtrCmpByName<Type> > Const_Class_SetByName;
typedef std::set<Class*, PtrCmpByName<Type> > Class_SetByName;
typedef std::set<const Template*, PtrCmpByName<Template> > Const_Template_Set;
typedef std::set<const Function*, PtrCmpByName<Function> > Const_Namespace_Set;
typedef std::set<const Namespace*, PtrCmpByName<Namespace> >
    Const_Namespace_Set;

/**
 * Describes a namespace.
 */
class Namespace
{
public:    
    /**
     * Basic constructor for initialization.
     * 
     * @param name The namespace name.
     * @param parent The parent namespace
     */
    Namespace(const std::string& name = "", const Namespace& parent);
   
    /**
     * Basic constructor for initialization.
     * 
     * @param name The namespace name.
     */
    Namespace(const std::string& name = "");
    
    /**
     * Get the name of the namespace.
     * 
     * @return The name of the member.
     */
    const std::string& getName() const;
    
    /**
     * Get the full name of the namespace.
     * 
     * @return The full name of the member.
     */
    const std::string& getFullName() const;
    
    /**
     * Get the owner Class of the member.
     * 
     * @return The parent namespace.
     */
    const Class& getParent() const;
    
    /**
     * Get the Type of the type with the given name if any.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @param typeName The name of the type.
     * @return The Type.
     */
    const Type& getType(const std::string& typeName) const;
    
    /**
     * Get the Type of the type with the given type_info.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @param cppType The type_info struct of the type.
     * @return The Type.
     */
    const Type& getType(const std::type_info& cppType) const;
    
    /**
     * Get the Class of the class with the given name if any.
     * Return a NULL reference if the type is not a class,
     * or is not a registered one.
     * 
     * @param className The name of the class.
     * @return The Class.
     */
    const Class& getClass(const std::string& className) const;
    
    /**
     * Get the Class of the class with the given type_info.
     * Return a NULL reference if the type is not a class,
     * or is not a registered one.
     * 
     * @param cppType The type_info struct of the class.
     * @return The Class.
     */
    const Class& getClass(const std::type_info& cppType) const;
    
    /**
     * Get the template descriptor of the template with the given name if any.
     * Return a NULL reference if the template is not a registered one.
     * 
     * @param templateName The name of the template.
     * @return The template descriptor.
     */
    const Template& getTemplate(const std::string& templateName) const;
    
    /**
     * Get a set containing the pointers to the type descriptors of all
     * the registered types.
     * 
     * @return The Type pointer set. 
     */
    const Const_Type_SetById& getTypes() const;
    
    /**
     * Get a set containing the pointers to the class descriptors of all
     * the registered classes.
     * 
     * @return The Class pointer set. 
     */
    const Const_Class_SetById& getClasses() const;
    
    /**
     * Get a set containing the pointers to the template descriptors of all
     * the registered templates.
     * 
     * @return The template descriptor pointer set. 
     */
    const Const_Template_Set& getTemplates() const;
    
    /**
     * Get a set containing the pointers to the function descriptors of all
     * the registered functions.
     * 
     * @return The function descriptor pointer set. 
     */
    const Const_Function_Set& getFunctions() const;
    
    /**
     * Get a set containing the pointers to the function descriptors of all
     * the registered functions.
     * 
     * @return The function descriptor pointer set. 
     */
    const Const_Namespace_Set& getNamespaces() const;
    

    virtual ~Namespace();
    
protected:
    // The member name.
    std::string name_;
    
    // The member owner class
    const Namespace* parent_;
    
    // Types
    Type_SetById typesById_;
    Type_Set_ByName typesByName_;
    
    // Classes
    Class_SetById classesById_;
    
    // Templates
    Const_Template_Set templates_;
    
    // Functions
    Const_Function_Set functions_;
    
    // Namespaces
    Const_Namespace_Set namespaces_;
    
    
    friend bool operator<(const Namespace& n1, const Namespace& n2);
};


} // namespace extmr

#endif	/* EXTMR_NAMESPACE_HPP */

