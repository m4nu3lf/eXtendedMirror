/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_TYPE_HPP
#define EXTMR_TYPE_HPP

namespace extmr{

class TypeRegister;

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
class Type
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
        CompoundClass = 24,
    };
    
    /**
     * Basic constructor for initialization.
     * 
     * @param name The type name.
     */
    Type(const std::string& name = "");
    
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
     * Get the name of this type.
     * 
     * @return The name of the type. 
     */
    const std::string& getName() const;
    
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
    const std::type_info& getCppType() const;
    
    
    virtual ~Type();
    
    /**
     * Non valid Type.
     * This Type can be used where ever a reference to a non valid Type is
     * needed.
     */
    static const Type Void;
    
protected:
    
    /**
     * Constructor for full initialization.
     * 
     * @param name The type name.
     * @param size The type size.
     * @param cppType The type_info struct of the type.
     */
    Type(const std::string& name, std::size_t size,
            const std::type_info& cppType);
    
    // The name of the type.
    std::string name_;

    // The size of the type.
    size_t size_;
    
    // The type_info struct of the type.
    const std::type_info& cppType_;
    
    // The equal operator must be a friend to access the cppType field.
    friend bool operator==(const Type&, const Type&);
    
    // The not equal operator must be a friend to access the cppType field.
    friend bool operator!=(const Type&, const Type&);
    
    // The less operator must be a friend to access the cppType field.
    friend bool operator<(const Type&, const Type&);
};

bool inline operator==(const Type& t1, const Type& t2)
{
    return t1.cppType_ == t2.cppType_;
}

bool inline operator!=(const Type& t1, const Type& t2)
{
    return t1.cppType_ != t2.cppType_;
}

// type less operator compares the type_info struct with the type_info::before()
// method.
bool inline operator<(const Type& t1, const Type& t2)
{
    return t1.cppType_.before(t2.cppType_);
}

typedef std::set<const Type*, PtrCmpByVal<Type> > Const_Type_SetById;
typedef std::set<Type*, PtrCmpByVal<Type> > Type_SetById;
typedef std::set<const Type*, PtrCmpByName<Type> > Const_Type_SetByName;
typedef std::set<Type*, PtrCmpByName<Type> > Type_Set_ByName;
typedef std::vector<const Type*> Const_Type_Vector;
typedef std::vector<Type*> Type_Vector;

} // namespace extmr

#endif // EXTMR_TYPE_HPP
