/* 
 * File:   Template.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 2 January 2013, 13.23
 */

#ifndef EXTMR_TEMPLATE_HPP
#define	EXTMR_TEMPLATE_HPP

namespace extmr{

/**
 * Holds some information about template types.
 */
class Template
{
public:
    /**
     * A basic constructor.
     * 
     * @param name The name of the template.
     */
    Template(const std::string& name, uint argN = 0); 
    
    /**
     * Get the name of the template.
     * 
     * @return The template name string.
     */
    const std::string& getName() const;
    
    /**
     * Get the number of the template parameters.
     * 
     * @return The template parameter number.
     */
    uint getArgN() const;
    
    /// This function object is used to compare two pointers to this class by the name of the pointed objects.
    typedef ::PtrCmpByName<Template> PtrCmp;
    
private:
    
    /// The name of the template.
    std::string name;
    
    /// The number of arguments.
    uint argN;
    
    /// PtrCmpByName must be a friend of this class to access the name attribute.
    friend class ::PtrCmpByName<Template>;
};

} // namespace extmr

#endif	/* EXTMR_TEMPLATE_HPP */

