/* 
 * File:   PointerType.hpp
 * Author: manuele
 *
 * Created on May 2, 2013, 3:59 PM
 */

#ifndef EXTMR_POINTERTYPE_HPP
#define	EXTMR_POINTERTYPE_HPP

namespace extmr {


class PointerType : public Type
{
public:
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the Type of the type pointed by this one.
     * 
     * @return The pointed Type.
     */
    const Type& getPointedType() const;
    
    virtual ~PointerType();
    
private:
    
    /**
     * Constructor.
     * 
     * @param name The type name.
     * @param size The type size.
     * @param cppType The type_info struct of the type.
     * @param constructor The type constructor wrapper function.
     * @param copyConstructor The type copy constructor wrapper function.
     * @param destructor The type destructor wrapper function.
     * @param assignOperator The type assign operator wrapper function.
     * @param pointedType The type pointed by this one.
     */
    PointerType
    (
            const std::string& name,
            std::size_t size,
            const std::type_info& cppType,
            Constructor* constructor,
            CopyConstructor* copyConstructor,
            Destructor* destructor,
            AssignOperator* assignOperator,
            const Type& pointedType
     );
    
    // the type pointed by this one.
    const Type* pointedType_;
    
    // TypeRegister is the factory class.
    template<typename T>
    friend class CreateType;
};


} // namespace extmr

#endif	/* EXTMR_POINTERTYPE_HPP */

