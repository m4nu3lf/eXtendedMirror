#ifndef EXTMR_TYPE_HPP
#define EXTMR_TYPE_HPP

namespace extmr{

class TypeRegister;
class Method;

/**
 * Holds information about a registered type for the reflection mechanism.
 * The type can be a primitive (\a Primitive), a pointer (\a Pointer), an array (\a Array),
 * a reflected class (\a Class) or a template instance (\a CompClass).
 * Each one of these type categories is identified by the internal enum Category.
 * Except for the a\ Primitive each one of the others categories is implemented in a subclass.
 * This class should be instantiate only when registering a type by the TypeRegister.
 */
class Type
{
public:
    
    /**
     * Enum of supported type categories.
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
         *  A type that depends on other types, i.e. a template instance.
         */
        CompClass = 24,
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
     * Construct a new instance of the type. If a pointer to
     * another instance is provided than the copy constructor is called.
     * 
     * @param toBeCopiedPtr The pointer to the object to be copied.
     * @return A new instance pointer.
     */
    void* newInstance(const void* toBeCopiedPtr = NULL) const;
    
    /**
     * Destroy an object of this type calling its constructor.
     * 
     * @param toBeDeletedPtr A pointer to an object of this type.
     */
    void deleteInstance(void* toBeDeletedPtr) const;
    
    /**
     * Perfor an assignment between two object instances of this type.
     * 
     * @param lvaluePtr A pointer to an object of this type to be used as lvalue.
     * @param rvaluePtr A pointer to an object of this type to be used as rvalue.
     */
    void assignInstance(void* lvaluePtr, const void* rvaluePtr) const;
    
    /**
     * Get a value of Category that represent the type category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the name of this type.
     * 
     * @return The name of the type. 
     */
    const std::string& getName() const;
    
    /**
     * Get the size of this type, the same of the one given by the sizeof() function
     * 
     * @return The type size.
     */
    std::size_t getSize() const;
    
    /**
     * Get the type_info struct of this type, the same of the one given by the typeid() function
     * 
     * @return The type_info struct.
     */
    const std::type_info& getCpptype() const;
    
    /**
     * Get the Type of the type pointed by this one.
     * If the type is not a pointer then a NULL reference is returned.
     * 
     * @return The pointed Type.
     */
    const Type& getPointedType() const;
    
    /**
     * Get the Type of the array elemets.
     * If the type is not an array then a NULL reference is returned.
     * 
     * @return The element Type.
     */
    const Type& getArrayElementType() const;
    
    /**
     * Get the size of the array.
     * If the type is not an array then 0 is returned.
     * 
     * @return The type size.
     */
    const std::size_t getArraySize() const;
    
    /**
     * Ask if the property is of a numerical type.
     * 
     * @return true if the property is of a numerical type.
     */
    // TODO: this method is not yet implemented. Decide whether and how to implement this method.
    bool isNumerical() const;
    
    /**
     * Virtual destructor
     */
    virtual ~Type();
    
    /// This function object is used to compare two pointers to this class by the name of the pointed objects.
    typedef ::PtrCmpByName<Type> PtrCmpByName;
    
    /// This function object is used to compare two pointers to this class by the '<' operator of the pointed objects
    struct PtrCmpById
    {
        bool operator()(const Type* ptr1, const Type* ptr2) const
        {
            return *ptr1 < *ptr2;
        }
    };
    
protected:
    
    /**
     * Constructor for full initialization.
     * 
     * @param name The type name.
     * @param size The type size.
     * @param cppType The type_info struct of the type.
     * @param constructor The type constructor wrapper function.
     * @param destructor The type destructor wrapper function.
     * @param operatorAssign The type assign operator wrapper function.
     * @param relatedType The Type of the type pointed by this 
     * one or the array element type of this one depending of the next parameter.
     * @param isArray If true relatedType is the array element type, otherwise is the pointed type.
     * @param arraySize The size of the array.
     */
    Type
    (
            const std::string& name,
            std::size_t size,
            const std::type_info& cppType,
            void* (*constructor)(const void*),
            void (*destructor)(void*),
            void (*operatorAssign)(void*, const void*),
            const Type& relatedType = *reinterpret_cast<Type*>(NULL),
            bool isArray = false,
            std::size_t arraySize = 0
     );
    
    /// The name of the type.
    std::string name;

    /// The size of the type.
    size_t size;
    
    /// The type_info struct of the type.
    const std::type_info& cppType;
    
    /// The type category.
    Category category;
    
    /// The constructor function pointer.
    void* (*constructor)(const void*);
    
    /// The destructor function pointer
    void (*destructor)(void*);
    
    /// The assign operator function pointer
    void (*operatorAssign)(void*, const void*);
    
    /// A pointer to the Type of the type pointed by this one or the one this type is an array of.
    const Type* relatedType;
    
    /// The size of the array.
    size_t arraySize;
    
    /// PtrCmpByName must be a friend of this class to access the name attribute.
    friend class ::PtrCmpByName<Type>;
    
    /// The type register is the factory for the type class and need to access the private constructor.
    friend class TypeRegister;
    
    /// The less operator must be a friend to access the type field.
    friend bool operator<(const Type&, const Type&);
};

/// The type equal operator compares the Type addresses.
bool inline operator==(const Type& t1, const Type& t2)
{
    return &t1 == &t2;
}

/// The type not_equal operator compares the Type addresses.
bool inline operator!=(const Type& t1, const Type& t2)
{
    return &t1 != &t2;
}

/// type less operator compares the type_info struct with the type_info::before() method.
bool inline operator<(const Type& t1, const Type& t2)
{
    return t1.cppType.before(t2.cppType);
}

} // namespace extmr

#endif // EXTMR_TYPE_HPP
