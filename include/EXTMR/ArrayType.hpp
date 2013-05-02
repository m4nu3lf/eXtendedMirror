/* 
 * File:   ArrayType.hpp
 * Author: manuele
 *
 * Created on May 2, 2013, 4:00 PM
 */

#ifndef EXTMR_ARRAYTYPE_HPP
#define	EXTMR_ARRAYTYPE_HPP

namespace extmr {


class ArrayType : public Type
{
public:
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the Type of the array elements.
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
    
    virtual ~ArrayType();
    
private:
    
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
     * @param arraySize The length of the array.
     * @param elementType The type of the array elements.
     */
    ArrayType
    (
            const std::string& name,
            std::size_t size,
            const std::type_info& cppType,
            Constructor* constructor,
            CopyConstructor* copyConstructor,
            Destructor* destructor,
            AssignOperator* assignOperator,
            std::size_t arraySize,
            const Type& elementType
     );
    
    
    // The array elements type.
    const Type* elementType_;
    
    // The size of the array.
    size_t arraySize_;
    
    // TypeRegister is the factory class.
    friend class TypeRegister;
};


} // namespace extmr

#endif	/* EXTMR_ARRAYTYPE_HPP */

