/* 
 * File:   Registration.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on August 8, 2012, 18.04
 */

#ifndef EXTMR_REGISTRATION_HPP
#define	EXTMR_REGISTRATION_HPP

namespace extmr{

/**
 * This template class allow a class to be registered without any extra code
 * inside the main() or any other function.
 * Registration is performed by the constructor on instantiation.
 */
template<class T>
class AutoRegisterer
{
    AutoRegisterer()
    {
        TypeRegister::getTypeReg().registerType<T>();\
    }
    
    static AutoRegisterer autoregisterer;
};

template<class T>
AutoRegisterer<T> AutoRegisterer<T>::autoregisterer;

/**
 * This function object builds a class info.
 */
template<class T>
struct ClassBuilder
{
    void operator()(Class& clazz) const
    {
        
    }
};

} // namespace extmr

#endif	/* EXTMR_REGISTRATION_HPP */

