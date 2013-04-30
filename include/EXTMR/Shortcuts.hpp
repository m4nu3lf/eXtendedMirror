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
const Type& registerType()
{
    return TypeRegister::getTypeReg().registerType<T>();
}


template <class C>
const Class& registerClass()
{
    return TypeRegister::getTypeReg().registerClass<C>();
}


template <typename T>
const Type& getType()
{
    return TypeRegister::getTypeReg().getType<T>();
}


template <typename C>
const Class& getClass()
{
    return TypeRegister::getTypeReg().registerClass<C>();
}


template <typename T>
const Type& getTypeOf(T& var)
{
    return TypeRegister::getTypeReg().getTypeOf<T>(var);
}


template <typename C>
const Class& getClassOf(C& object)
{
    return TypeRegister::getTypeReg().getClassOf<C>(object);
}


template<class C>
bool is(const C& object, const Class& clazz)
{
    const Class& c = getClassOf(object);

    if (c == clazz)
        return true;
    return c.inheritsFrom(clazz);
}


template<class C1, class C2>
bool is(const C2& object)
{
    return dynamic_cast<const C1*>(&object);
}


} //namespace extmr


#endif	/* SHORTCUTS_HPP */

