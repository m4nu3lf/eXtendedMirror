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
    return TypeRegister::getSingleton().registerType<T>();
}


template <class C>
const Class& registerClass()
{
    return TypeRegister::getSingleton().registerClass<C>();
}


template <typename T>
const Type& getType()
{
    return TypeRegister::getSingleton().getType<T>();
}


inline
const Type& getType(const std::string& name)
{
    return TypeRegister::getSingleton().getType(name);
}


template <typename C>
const Class& getClass()
{
    return TypeRegister::getSingleton().registerClass<C>();
}


inline
const Class& getClass(const std::string& name)
{
    return TypeRegister::getSingleton().getClass(name);
}


template <typename T>
const Type& getTypeOf(T& var)
{
    return TypeRegister::getSingleton().getTypeOf<T>(var);
}


template <typename C>
const Class& getClassOf(C& object)
{
    return TypeRegister::getSingleton().getClassOf<C>(object);
}


template<class C>
bool is(const C& object, const Class& clazz)
{
    const Class& c = getClassOf(object);

    if (c == clazz)
        return true;
    return c.inheritsFrom(clazz);
}


inline
const void unregisterType(const std::string& name)
{
    return TypeRegister::getSingleton().unregisterType(name);
}


inline
const void unregisterType(const std::type_info& typeId)
{
    return TypeRegister::getSingleton().unregisterType(typeId);
}


} //namespace extmr


#endif	/* SHORTCUTS_HPP */

