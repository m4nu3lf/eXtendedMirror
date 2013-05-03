/* 
 * File:   PrimitiveType.hpp
 * Author: manuele
 *
 * Created on May 2, 2013, 4:02 PM
 */

#ifndef EXTMR_PRIMITIVETYPE_HPP
#define	EXTMR_PRIMITIVETYPE_HPP

namespace extmr {


class PrimitiveType : public Type
{
public:
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    virtual ~PrimitiveType();
    
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
     */
    PrimitiveType
    (
            const std::string& name,
            std::size_t size,
            const std::type_info& cppType,
            Constructor* constructor,
            CopyConstructor* copyConstructor,
            Destructor* destructor,
            AssignOperator* assignOperator
     );
    
    // Factory class
    template<typename T>
    friend class CreateType;
};


} // namespace extmr

#endif	/* EXTMR_PRIMITIVETYPE_HPP */

