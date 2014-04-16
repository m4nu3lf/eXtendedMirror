/* 
 * File:   Variant.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 3 September 2012, 12.04
 */

#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

const Variant Variant::Null = Variant();

Variant::Variant() : flags_(0)
{
    data_ = NULL;
    type_ = &extmr::getType<void>();
}


RefVariant Variant::getRefVariant() const
{
    RefVariant refVar;
    refVar.data_ = data_;
    refVar.type_ = type_;
    refVar.flags_ = flags_ | Reference;
    
    // need a const cast to help compiler choose the copy constructor
    // instead of the template constructor
    return const_cast<const RefVariant&>(refVar);
}


Variant::Variant(const Variant& orig) : flags_(0)
{
    if (orig.flags_ | CpyByRef)
    {
        // copy by reference
        data_ = orig.data_;
        type_ = orig.type_;
        flags_ = orig.flags_;
        flags_ |= Reference;
    }
    else
    {
        std::size_t size = orig.type_->getSize();
        
        //TODO: allow custom allocator
        // allocate memory
        data_ = ::operator new(size);
        
        // if class copy with copy constructor
        const Class* clazz = dynamic_cast<const Class*>(orig.type_);
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            
            try
            {
                cpyC.copy(*this, orig);
            }
            catch(NonCopyableException& e)
            {
                ::operator delete(data_); //TODO allow custom allocator
                throw e;
            }
        }
        else
        {
            // perform raw memory copy
            std::memcpy(data_, orig.data_, size);
        }
    }
}


const Variant& Variant::operator=(const Variant& other)
{
    if (flags_ | Reference)
    {
        // copy reference
        data_ = other.data_;
        type_ = other.type_;
        flags_ = other.flags_;
        flags_ |= Reference;
    }
    else
    {
        std::size_t size = other.type_->getSize();
        
        //TODO: allow custom allocator
        // allocate memory
        data_ = ::operator new(size);
        
        // if class, assign with assign operator
        const Class* clazz = dynamic_cast<const Class*>(other.type_);
        if (clazz)
        {
            const AssignOperator& assignOp = clazz->getAssignOperator();
            
            try
            {
                assignOp.assign(*this, other);
            }
            catch(NonAssignableException& e)
            {
                ::operator delete(data_); //TODO allow custom allocator
                throw e;
            }
        }
        else
        {
            // perform raw memory copy
            std::memcpy(data_, other.data_, size);
        }
    }
}


Variant::~Variant()
{
    if(!data_) return;
    
    if (!flags_ & Reference)
    {        
        const Class* clazz = dynamic_cast<const Class*>(type_);
        if (clazz)
        {
            // call destructor
            clazz->getDestructor().destroy(*this);
        }
        
        //TODO: allow custom allocator
        ::operator delete(data_);
    }
}


// A variant can always be converted to an Empty object. 
template<>
Empty& Variant::as<Empty>() const
{
    static Empty empty;
    return empty;
}

