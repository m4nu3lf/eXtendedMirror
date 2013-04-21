/* 
 * File:   ContainterUtils.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 10 October 2012, 13.51
 */

#ifndef CONTAINERUTILS_HPP
#define	CONTAINERUTILS_HPP


#define DEFINE_SIMPLE_POINTER_COMPARER(getter, ComparerName)                   \
                                                                               \
template<class T>                                                              \
struct ComparerName                                                            \
{                                                                              \
    bool operator()(const T* ptr1, const T* ptr2) const                        \
    {                                                                          \
        return ptr1->getter() < ptr2->getter();                                \
    }                                                                          \
};                                                                             \


namespace ptrSet {

    
template<class T>
struct KeyObjectSubclass
{
    typedef T Type;
};
    

template<class T, class C, typename K>
T* findByKey(std::set<T*, C> set, const K& key)
{
    typename KeyObjectSubclass<T>::Type value(key);
    typename std::set<T*, C>::iterator ite;
    ite = set.find(&value);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T, class C, typename K>
T* removeByKey(std::set<T*, C> set, const K& key)
{
    typename KeyObjectSubclass<T>::Type keyObj(key);
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

#define DEFINE_PTRSET_KEYOBJECT_SUBCLASS(Class, Subclass)                      \
                                                                               \
class Class;                                                                   \
class Subclass;                                                                \
                                                                               \
namespace ptrSet {                                                             \
                                                                               \
template<>                                                                     \
struct KeyObjectSubclass<Class>                                                \
{                                                                              \
    typedef Subclass Type;                                                     \
};                                                                             \
                                                                               \
} // namespace ptrSet

#endif	/* CONTAINERUTILS_HPP */

