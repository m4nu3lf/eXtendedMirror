/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
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
    Member(const Class& owner, const std::string& name = "");
    
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
    

    virtual ~Member();
    
protected:
    // The member name.
    std::string name_;
    
    // The member owner class
    const Class* owner_;
    
    // Class needs to access the owner_ attribute.
    friend class Class;
    
    friend bool operator<(const Member& m1, const Member& m2);
};


} // namespace extmr

#endif	/* EXTMR_MEMBER_HPP */

