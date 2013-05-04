/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef CONTAINERUTILS_HPP
#define	CONTAINERUTILS_HPP


#define DEFINE_POINTER_COMPARER_BY_METHOD(getter, ComparerName)                \
                                                                               \
template<class T>                                                              \
struct ComparerName                                                            \
{                                                                              \
    bool operator()(const T* ptr1, const T* ptr2) const                        \
    {                                                                          \
        return ptr1->getter() < ptr2->getter();                                \
    }                                                                          \
};                                                                             \


template<class T>
struct PtrCmpByVal
{
    bool operator()(const T* ptr1, const T* ptr2) const
    {
        return *ptr1 < *ptr2;
    }
};


namespace ptrSet {

    
template<class T>
struct ThrowawayKeyClass
{
    typedef T Type;
};
    

template<class T, class C, typename K>
T* findByKey(std::set<T*, C> set, const K& key)
{
    typename ThrowawayKeyClass<T>::Type keyObj(key);
    typename std::set<T*, C>::iterator ite;
    ite = set.find(&keyObj);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T, class C, typename K>
T* removeByKey(std::set<T*, C> set, const K& key)
{
    typename ThrowawayKeyClass<T>::Type keyObj(key);
    typename std::set<T*, C>::iterator ite;
    ite = set.find(&keyObj);
    if (ite == set.end())
        return NULL;
    T* value = *ite;
    set.erase(ite);
    return value;
}


template<class T, class C>
T* deleteAll(std::set<T*, C> set)
{
    typename std::set<T*, C>::iterator ite = set.begin();
    while(ite != set.end())
    {
        T* element = *ite;
        set.erase(ite);
        delete element;
        ite ++;
    }
}


} // namespace ptrSet

#define DEFINE_PTRSET_THROWAWAY_KEY_CLASS(Class, KeyClass)                     \
                                                                               \
class Class;                                                                   \
class KeyClass;                                                                \
                                                                               \
namespace ptrSet {                                                             \
                                                                               \
template<>                                                                     \
struct ThrowawayKeyClass<Class>                                                \
{                                                                              \
    typedef KeyClass Type;                                                     \
};                                                                             \
                                                                               \
} // namespace ptrSet

#endif	/* CONTAINERUTILS_HPP */

