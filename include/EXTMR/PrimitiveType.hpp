/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PRIMITIVETYPE_HPP
#define	EXTMR_PRIMITIVETYPE_HPP

namespace extmr {


class PrimitiveType : public Type
{
public:
    Category getCategory() const;
    
    virtual ~PrimitiveType();
    
private:
    PrimitiveType(const std::string& name, std::size_t size,
            const std::type_info& cppType);
    
    // Factory class
    template<typename T>
    friend class CreateType;
};


} // namespace extmr

#endif	/* EXTMR_PRIMITIVETYPE_HPP */

