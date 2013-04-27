/* 
 * File:   Member.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on April 27, 2013, 4:39 PM
 */

#ifndef EXTMR_MEMBER_HPP
#define	EXTMR_MEMBER_HPP

namespace extmr {

class Class;

/**
 * Describes a member of a class.
 */
class Member
{
public:
    /**
     * Basic constructor for initialization.
     * 
     * @param name The member name.
     */
    Member(const std::string& name = "");
    
    /**
     * Get the name of the member.
     * 
     * @return The name of the member.
     */
    const std::string& getName() const;
    
    /**
     * Get the owner Class of the member.
     * 
     * @return The owner Class.
     */
    const Class& getOwner() const;
    
    /**
     * Set the owner Class of the member.
     * 
     * @param owner The owner Class.
     */
    void setOwner(const Class& owner);

    virtual ~Member();
    
protected:
    // The member name.
    std::string name_;
    
    // The member owner class
    const Class* owner_;
};


} // namespace extmr

#endif	/* EXTMR_MEMBER_HPP */

