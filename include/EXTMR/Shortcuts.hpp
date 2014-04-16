/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_SHORTCUTS_HPP
#define	EXTMR_SHORTCUTS_HPP

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


#endif	/* EXTMR_SHORTCUTS_HPP */

