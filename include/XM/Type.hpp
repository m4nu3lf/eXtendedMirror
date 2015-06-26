/******************************************************************************
 *      Extended Mirror: Type.hpp                                         *
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


#ifndef XM_TYPE_HPP
#define XM_TYPE_HPP

namespace xm{

class Register;
typedef std::set<std::string> String_Set;

/**
 * Holds information about a registered type for the reflection mechanism.
 * 
 * The type can be a primitive (\a Primitive), a pointer (\a Pointer),
 * an array (\a Array), a reflected class (\a Class) or a template instance
 * (\a CompoudClass). Each one of these type categories is identified by the
 * internal enum Category.
 * Except for the a\ Primitive each one of the others categories is 
 * implemented in a subclass.
 * This class should be instantiate only when registering a type by
 * the TypeRegister.
 */
class Type : public virtual Item
{
public:
    
    /**
     * Type categories.
     */
    enum Category
    {
        /**
         * A primitive type.
         */
        Primitive = 1,
        
        /**
         * A pointer to another supported type.
         */
        Pointer = 2,
        
        /**
         * An array of another supported type.
         */
        Array = 4,
        
        /**
         * A reflected class.
         */
        Class = 8,
        
        /**
         *  A template instance.
         */
        CompoundClass = 24
    };
    
    /**
     * Basic constructor for initialization.
     * 
     * @param uName The unqualified type name.
     */
    Type(const std::string& uName = "");

     /**
     * Basic constructor for initialization.
     *
     * @param uName The unqualified type name.
     * @param name_space The belonging namespace.
     */
    Type(const std::string& uName, const Namespace& name_space);

    /**
     * Basic constructor for initialization.
     * 
     * @param cppType The type_info struct of the type.
     */
    Type(const std::type_info& cppType);
    
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    virtual Category getCategory() const;
    
    /**
     * Get the aliases of this type.
     * 
     * @return The set of aliases.
     */
    const String_Set& getAliases() const;
    
    /**
     * Get the size of this type, the same of the one given by sizeof().
     * 
     * @return The type size.
     */
    std::size_t getSize() const;
    
    /**
     * Get the type_info struct of this type,
     * the same of the one given by the typeid().
     * 
     * @return The type_info struct.
     */
    const std::type_info& getId() const;

    Item::Category getItemCategory() const;

    bool before(const Item& item) const;

    virtual ~Type();
    
protected:
    
    /**
     * Constructor for full initialization.
     * 
     * @param size The type size.
     * @param cppType The type_info struct of the type.
     */
    Type(std::size_t size,
         const std::type_info& cppType);
    
    /**
     * Add an alias to the type.
     * 
     * @param alias
     */
    void addAlias(const std::string& alias);
    
    // The aliases of the type.
    String_Set aliases_;

    // The size of the type.
    size_t size_;
    
    // The type_info struct of the type.
    const std::type_info& id_;
    
    // The equal operator must be a friend to access the cppType field.
    friend bool operator==(const Type&, const Type&);
    
    // The not equal operator must be a friend to access the cppType field.
    friend bool operator!=(const Type&, const Type&);
    
    // The less than operator must be a friend to access the id_ field.
    friend bool operator<(const Type&, const Type&);
};

inline
bool operator==(const Type& t1, const Type& t2)
{
    return t1.id_ == t2.id_;
}

inline
bool operator!=(const Type& t1, const Type& t2)
{
    return t1.id_ != t2.id_;
}

// type less operator compares the type_info struct with the type_info::before()
// method.
inline
bool operator<(const Type& t1, const Type& t2)
{
    return t1.id_.before(t2.id_);
}


typedef std::vector<const Type*> Const_Type_Vector;
typedef std::vector<Type*> Type_Vector;

} // namespace xm

#endif // XM_TYPE_HPP
