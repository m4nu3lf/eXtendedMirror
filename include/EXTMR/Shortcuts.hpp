/* 
 * File:   Shortcuts.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on April 20, 2013, 12:26 AM
 */

#ifndef SHORTCUTS_HPP
#define	SHORTCUTS_HPP

namespace extmr {
    

template <typename T>
const Type& getType()
{
    return TypeRegister::getTypeReg().registerType<T>();
}


template <typename C>
const Class& getClass()
{
    return TypeRegister::getTypeReg().registerClass<C>();
}


template <typename T>
const Type& typeOf(T& var)
{
    return TypeRegister::getTypeReg().getTypeOf<T>(var);
}


template <typename C>
const Class& classOf(C& object)
{
    return TypeRegister::getTypeReg().getClassOf<C>(object);
}


template<class C1, class C2>
bool is(const C2& object)
{
    TypeRegister& typeReg = TypeRegister::getTypeReg();

    const Class& c1 = typeReg.getClass<C1>();
    const Class& c2 = typeReg.getClassOf(object);

    if (c1 == c2)
        return true;
    return c2.inheritsFrom(c1);
}


} //namespace extmr


#endif	/* SHORTCUTS_HPP */

