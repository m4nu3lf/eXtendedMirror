/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_VARIANT_HPP
#define	EXTMR_VARIANT_HPP

namespace extmr{

class Type;
class RefVariant;

/**
 * This class can store data from each type that is registrable or already
 * registered within the type register.
 * For store we mean that data can be both copied and stored or just referenced. 
 * In the second case is up to the programmer to ensure the data will remain
 * valid and to deallocate this data after the variant object is destroyed.
 * The copy construct has in any case the effect to copy the content of the
 * variant so that changes on the data of the newly created variant never affect
 * the original variant.
 */
class Variant
{
public:
    /**
     * Some variant flags.
     */
    enum Flags
    {
        // Variant data is a reference to external data.
        Reference = 1,
        
        // Variant holds constant data
        Const = 2,

        // Variant data is a pointer to a constant.
        Ptr2Const = 4,
        
        // Variant get copied by ref.
        CpyByRef = 8
    };
    
    /**
     * Build a void variant.
     */
    Variant();
    
    /**
     * Construct a variant from the given object.
     * The object data is copied with its class copy constructor and the data is
     * stored internally.
     * 
     * @param data
     */
    template<typename T>
    Variant(const T data);
    
    /**
     * Construct a variant from the given object.
     * By default the object is copied with its class copy constructor and the
     * data is stored internally.
     * If you want to change this behavior specify the second parameter.
     * 
     * @param data The object from which to take the data form.
     * @param flags The variant flags.
     */
    template<typename T>
    Variant(T& data, char flags);
    
    /**
     * Get the Type for the data.
     * 
     * @return The Type.
     */
    const Type& getType() const;
    
    /*
     * Create and return a RefVariant to the content.
     * 
     * @return The RefVariant
     */
    RefVariant getRefVariant() const;
    
    /**
     * Ask if this variant data is a reference to an external data.
     * 
     * @return true if the variant data is a reference, false otherwise.
     */
    bool isReference() const;
    
    /**
     * Ask if this variant holds constant data.
     * 
     * @return true if the variant holds constant data, false otherwise.
     */
    bool isConst() const;
    
    /**
     * Ask if this variant holds a pointer to constant data.
     * 
     * @return true if the variant holds a pointer to constant data,
     * false otherwise.
     */
    bool isPointerToConst() const;
    
    /**
     * Set the variant data to be constant, after a variant has been marked as
     * constant, the constness cannot be removed anymore.
     */
    void setConst();
    
    /**
     * Cast operator, get the data of the variant by reference.
     * This method only works if the template parameter
     * is either the same of the contained data or, given that the
     * data is an object of a class or a pointer
     * to an object of a class, then the specified type
     * is respectively a base class of the that class or a pointer to
     * a base class of that class.
     * In other words this would only work if a reinterpret_cast<> from the
     * pointer to the contained data type to a pointer of the target type would 
     * lead to a meaningful conversion.
     * In all other cases a VariantTypeException arises.
     * 
     * @return The variant data.
     */
    template<typename T>
    operator T&() const;
    
    /**
     * This is just a shortcut to static_cast<T>(*this)
     * 
     * @return The variant data.
     */
    template<typename T>
    T& as() const;
    
    /**
     * Copy constructor. The data is copied through the copy constructor.
     * 
     * @param orig The variant to copy.
     */
    Variant(const Variant& orig);
    
    /**
     * Operator for assignment.
     * The data is copied through the type assign operator.
     * If the data of the lvalue variant has not yet been allocated is then
     * allocated through the standard constructor.
     * It types are different, then the lvalue variant data is first
     * deallocated, and then types are set the same.
     * 
     * @param other The other variant object.
     * @return The variant
     */
    const Variant& operator=(const Variant& other);
    
    /**
     * Operator for assignment.
     * The data of the rvalue is stored into the variant after it has been
     * copied through the assignment operator of the specified type.
     * If current type of the variant is different form that of the rvalue then
     * the previous data is deallocated with the destructor and a new object of
     * the new type is allocated with its default constructor.
     * The assignment is then performed.
     * 
     * @param rvalue The rvalue object
     * @return A reference to the rvalue
     */
    template<typename T>
    const T& operator=(const T& rvalue);
    
    //TODO: add support for all others operators
    
    /**
     * Destructor. The data is deallocated calling the destructor.
     */
    virtual ~Variant();
    
    static const Variant Null;
    
protected:
    // Pointer the data.
    void* data_;
    
    // Pointer to the Type of data.
    const Type* type_;
    
    // Some flags
    char flags_;
    
    /**
     * Initialize a variant.
     */
    template<typename T>
    struct Initialize
    {
        Initialize(Variant& variant);

        void operator()(T& data);

    private:
        // The variant that is being initialized
        Variant& variant_;
    };
    
};


} // namespace extmr

#endif	/* EXTMR_VARIANT_HPP */

