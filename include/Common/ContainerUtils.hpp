/* 
 * File:   ContainterUtils.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 10 October 2012, 13.51
 */

#ifndef CONTAINERUTILS_HPP
#define	CONTAINERUTILS_HPP


template<class T>
struct PtrCmpByName
{
    bool operator()(const T* ptr1, const T* ptr2) const
    {
        return ptr1->getName() < ptr2->getName();
    }
};


template<class T, class N>
T* setFindByName(std::set<T*, PtrCmpByName<T> > set, const N& name)
{
    T key(name);
    typename std::set<T*, PtrCmpByName<T> >::iterator ite;
    ite = set.find(&key);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T, class N>
T* setRemoveByName(std::set<T*, PtrCmpByName<T> > set, const N& name)
{
    T key(name);
    typename std::set<T*, PtrCmpByName<T> >::iterator ite;
    ite = set.find(&key);
    if (ite == set.end())
        return NULL;
    T* value = *ite;
    set.erase(ite);
    return value;
}


template<class T>
struct PtrCmpById
{
    bool operator()(const T* ptr1, const T* ptr2) const
    {
        return ptr1->getId() < ptr2->getId();
    }
};


template<class T, class I>
T* setFindById(std::set<T*, PtrCmpById<T> > set, const I& id)
{
    T key(id);
    typename std::set<T*, PtrCmpById<T> >::iterator ite;
    ite = set.find(&key);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T, class I>
T* setRemoveById(std::set<T*, PtrCmpById<T> > set, const I& id)
{
    T key(id);
    typename std::set<T*, PtrCmpById<T> >::iterator ite;
    ite = set.find(&key);
    if (ite == set.end())
        return NULL;
    T* value = *ite;
    set.erase(ite);
    return value;
}


template<class T, class C>
T* setDeleteAll(std::set<T*, C> set)
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

#endif	/* CONTAINERUTILS_HPP */

