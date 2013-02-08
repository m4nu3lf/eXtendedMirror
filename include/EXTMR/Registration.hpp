/* 
 * File:   Registration.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 8 August 2012, 18.04
 */

#ifndef EXTMR_REGISTRATION_HPP
#define	EXTMR_REGISTRATION_HPP

namespace extmr{

/**
 * This template class allow a class to be registered without any extra code inside the main() or any other function.
 * Registration is performed by the constructor on instantiation.
 */
template<class T>
struct AutoRegisterer
{
    AutoRegisterer()
    {
        TypeRegister::getTypeReg().registerType<T>();\
    }
};

/**
 * This function object builds a class info.
 */
template<class T>
struct ClassBuilder
{
    void operator()(Class& clazz, TypeRegister& typeReg) const
    {
        
    }
};

} // namespace extmr

#endif	/* EXTMR_REGISTRATION_HPP */

