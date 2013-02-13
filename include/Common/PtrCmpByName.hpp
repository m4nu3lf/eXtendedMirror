/* 
 * File:   PtrCmpByName.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on October 10, 2012, 13.51
 */

#ifndef PTRCMPBYNAME_HPP
#define	PTRCMPBYNAME_HPP

/**
 * Compare two pointer to T objects. T object must have a name field.
 * 
 * @param ptr1 Pointer to the first object.
 * @param ptr2 Pointer to the second object.
 * @return true if the name of the first pointed object comes first than the name of the second pointed object.
 */
template<class T>
struct PtrCmpByName
{
    bool operator()(const T* ptr1, const T* ptr2) const
    {
        return ptr1->name < ptr2->name;
    }
};

#endif	/* PTRCMPBYNAME_HPP */

