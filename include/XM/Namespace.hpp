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


#ifndef XM_NAMESPACE_HPP
#define	XM_NAMESPACE_HPP

namespace xm {
    
class Type;
class Class;
class Template;
class Function;
class Namespace;


typedef std::map<std::string, Type*> Type_Map;
typedef std::map<std::string, const Type*> Const_Type_Map;
typedef std::map<std::string, Class*> Class_Map;
typedef std::map<std::string, const Class*> Const_Class_Map;
typedef std::map<std::string, Template*> Template_Map;
typedef std::map<std::string, const Template*> Const_Template_Map;
typedef std::map<std::string, const Function*> Const_Function_Map;
typedef std::set<const Namespace*, PtrCmpByName<Namespace> >
    Const_Namespace_Set;


class Namespace : public virtual Name
{
public:
    const Namespace& getNamespace(const std::string& name) const;
    
    const Type& getType(const std::string& typeName) const;
    
    const Class& getClass(const std::string& className) const;

    const Template& getTemplate(const std::string& templateName) const;
    
    const Const_Namespace_Set& getNamespaces() const;

    const Const_Type_Map& getTypes() const;

    const Const_Class_Map& getClasses() const;

    const Const_Template_Map& getTemplates() const;

    const Const_Function_Map& getFunctions() const;
    
    virtual ~Namespace();
    
protected:
    Namespace(const std::string& name, const Namespace& parent);
   
    Namespace(const std::string& name = "");
    
    void defineNamespace(const std::string& name);
    
    void addType(const std::string& name, const Type& type);
    
    void addTemplate(const std::string& name, const Template& templ);
    
    void addFunction(const std::string& name, const Function& function);
    
    Const_Type_Map types_;
    
    Const_Class_Map classes_;
    
    Const_Template_Map templates_;
    
    Const_Function_Map functions_;
    
    Const_Namespace_Set namespaces_;
};


} // namespace xm

#endif	/* XM_NAMESPACE_HPP */

