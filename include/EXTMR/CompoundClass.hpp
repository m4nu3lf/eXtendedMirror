/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_COMPOUNDCLASS_HPP
#define	EXTMR_COMPOUNDCLASS_HPP

namespace extmr {

    
class CompoundClass : public Class
{
public:
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the template descriptor of the template this class is an instance of.
     * 
     * @return The template descriptor.
     */
    const Template& getTemplate() const;
    
    /**
     * Get a vector containing the Type objects of the type arguments of the
     * template.
     * 
     * @return The type descriptors vector.
     */
    const Const_Type_Vector& getTemplateArgs() const;
        
private:
    /**
     * Constructor for full initialization.
     * 
     * @param name The class name.
     * @param size The class size.
     * @param cppType The type_info struct of the class.
     * @param constructor The class constructor wrapper function.
     * @param copyConstructor The type copy constructor wrapper function.
     * @param destructor The class destructor wrapper function.
     * @param assignOperator The class assign operator wrapper function.
     * @param isAbstract If the class is abstract.
     * @param tempjate The template this class is an instance of.
     * @param templateArgs The Type of the template arguments.
     */
    CompoundClass
    (
            const std::string& name,
            uint size,
            const std::type_info& cppType,
            const Constructor& constructor,
            const CopyConstructor& copyConstructor,
            const Destructor& destructor,
            const AssignOperator& assignOperator,
            bool isAbstract,
            const Template& tempjate,
            const Const_Type_Vector& templateArgs
     );
    
    // The template descriptor of the template this class is an instance of.
    const Template* tempjate_;
    
    // The type descriptors of the template arguments.
    Const_Type_Vector templateArgs_;
    
    // Factory function
    template<class T>
    friend Type* createCompoundClass();
};


} // namespace extmr

#endif	/* EXTMR_COMPOUNDCLASS_HPP */

