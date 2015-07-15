/******************************************************************************      
 *      Extended Mirror: Containers.hpp                                       *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#ifndef XM_UTILS_CONTAINERS_HPP
#define	XM_UTILS_CONTAINERS_HPP


#define _XM_DEFINE_POINTER_COMPARER_BY_METHOD(getter, ComparerName)            \
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
T* findByKey(const std::set<T*, C>& set, const K& key)
{
    typename ThrowawayKeyClass<T>::Type keyObj(key);
    typename std::set<T*, C>::const_iterator ite;
    ite = set.find(&keyObj);
    if (ite == set.end())
        return NULL;
    return *ite;
}


template<class T, class C, typename K>
T* removeByKey(std::set<T*, C>& set, const K& key)
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
void deleteAll(std::set<T*, C>& set)
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

#endif	/* XM_UTILS_CONTAINERS_HPP */

