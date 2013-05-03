#ifndef EXTMR_TYPE_HPP
#define EXTMR_TYPE_HPP

namespace extmr{

class TypeRegister;
class Method;

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
     * Ask if the type is instantiable.
     * 
     * @return True if the type is instatiable.
     */
    bool isInstatiable();
    
    /**
     * Ask if the type is copyable.
     * 
     * @return True if the type is copyable.
     */
    bool isCopyable();
    
    /**
     * Ask if the type can be assigned to.
     * 
     * @return True if the type can be assigned to.
     */
    bool isAssignable();
    
    /**
     * Ask if the type is destructible.
     * 
     * @return True if the type can be destroyed.
     */
    bool isDestructible();
    
    /**
     * Construct a new instance of the type.
     * 
     * @param addres If not NULL the placement constructor is called to this
     * address.
     * @return The pointer to the new instance.
     */
    void* newInstance(void* address = NULL) const;
    
    /**
     * Copy an instance of the type.
     * 
     * @param originAddr The address of the instance to be copied.
     * @param destAddr If not NULL the placement copy constructor is called to
     * this address.
     * @return The pointer of the new copied instance.
     */
    void* copyInstance(void* originAddr, void* destAddr = NULL) const;
    
    /**
     * Destroy an instance of the type.
     * 
     * @param address The pointer to the instance to be deleted.
     * @param dallocate If true the delete operator is called causing the memory
     * to be deallocated otherwise the destructor is called explicity.
     */
    void deleteInstance(void* address, bool deallocate = true) const;
    
    /**
     * Perfor an assignment between two object instances of this type.
     * 
     * @param lvalueAddr A pointer to an object of this type to be used as
     * lvalue.
     * @param rvalueAddr A pointer to an object of this type to be used as
     * rvalue.
     */
    void assignInstance(void* lvalueAddr, const void* rvalueAddr) const;
    
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
     * @param constructor The type constructor wrapper function.
     * @param copyConstructor The type copy constructor wrapper function.
     * @param destructor The type destructor wrapper function.
     * @param assignOperator The type assign operator wrapper function.
     */
    Type
    (
            const std::string& name,
            std::size_t size,
            const std::type_info& cppType,
            Constructor* constructor,
            CopyConstructor* copyConstructor,
            Destructor* destructor,
            AssignOperator* assignOperator
     );
    
    // The name of the type.
    std::string name_;

    // The size of the type.
    size_t size_;
    
    // The type_info struct of the type.
    const std::type_info& cppType_;
    
    // The constructor function object.
    Constructor* constructor_;
    
    // The copy constructor function object.
    CopyConstructor* copyConstructor_;
    
    // The destructor function object.
    Destructor* destructor_;
    
    // The assign operator function object.
    AssignOperator* assignOperator_;
    
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

typedef std::set<const Type*, PtrCmpByVal<Type> > ConstTypeSetById;
typedef std::set<Type*, PtrCmpByVal<Type> > TypeSetById;
typedef std::set<const Type*, PtrCmpByName<Type> > ConstTypeSetByName;
typedef std::set<Type*, PtrCmpByName<Type> > TypeSetByName;
typedef std::vector<const Type*> ConstTypeVector;
typedef std::vector<Type*> TypeVector;

} // namespace extmr

#endif // EXTMR_TYPE_HPP
