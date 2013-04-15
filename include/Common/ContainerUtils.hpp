/* 
 * File:   ContainterUtils.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 10 October 2012, 13.51
 */

#ifndef CONTAINERUTILS_HPP
#define	CONTAINERUTILS_HPP

/**
 * Compare two pointer to T objects. T object must have a name_ field.
 * 
 * @param ptr1 Pointer to the first object.
 * @param ptr2 Pointer to the second object.
 * @return true if the name of the first pointed object comes first than the
 * name of the second pointed object.
 */
template<class T>
struct PtrCmpByName
{
    bool operator()(const T* ptr1, const T* ptr2) const
    {
        return ptr1->name_ < ptr2->name_;
    }
};


template<class T>
T* setFindByName(std::set<T*, PtrCmpByName<T> > set, const std::string& name)
{
    T key(name);
    typename std::set<T*, PtrCmpByName<T> >::iterator ite;
    ite = set.find(&key);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T>
T* setRemoveByName(std::set<T*, PtrCmpByName<T> > set, const std::string& name)
{
    T key(name);
    set.erase(&key);
}

#endif	/* CONTAINERUTILS_HPP */

