
/******************************************************************************      
 *      Extended Mirror: RegistrationMacros.hpp                               *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
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


#ifndef XM_MACROS_HPP
#define	XM_MACROS_HPP

#include <XM/TemplateRegistrationMacros.hpp>

/**
 * \def XM_ENABLE_PRIMITIVE(_primitive_type_)
 * Specialize the GetTypeName class for the \a _primitive_type_
 */
#define XM_ENABLE_PRIMITIVE(_primitive_type_)                                \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
struct GetTypeName<_primitive_type_>                                         \
{                                                                            \
    std::string operator()()                                                 \
    {                                                                        \
        return #_primitive_type_;                                            \
    }                                                                        \
};                                                                           \
                                                                             \
} // namespace xm


/**
 * \def XM_ENABLE_CLASS(_class_)
 * 
 * GetTypeName template struct is specialized in order to define the right
 * name and category for the type.
 * This information is used during the registration phase of this type.
 * 
 * Enables reflection for the class \a _class_.
 * Place this macro in the same header of the \a _class_ declaration,
 * after the class declaration.
 */
#define XM_ENABLE_CLASS(_class_)                                             \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
struct GetTypeName<_class_ >                                                 \
{                                                                            \
    std::string operator()()                                                 \
    {                                                                        \
        return #_class_;                                                     \
    }                                                                        \
};                                                                           \
                                                                             \
template<>                                                                   \
struct BuildClass<_class_>                                                   \
{                                                                            \
    typedef _class_ ClassT;                                                  \
    void operator()();                                                       \
};                                                                           \
                                                                             \
template<>                                                                   \
struct CreateType<_class_>                                                   \
{                                                                            \
    Type& operator()()                                                       \
    {                                                                        \
        return Class::create<_class_ >();                                    \
    }                                                                        \
};                                                                           \
                                                                             \
} // namespace xm


#define XM_ASSUME_NON_COPYABLE(_class_)                                      \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
class CopyConstructorImpl<_class_ > : public CopyConstructor                 \
{                                                                            \
public:                                                                      \
    CopyConstructorImpl(const Class& owner) : CopyConstructor(owner) {};     \
};                                                                           \
                                                                             \
} //namespace xm


#define XM_ASSUME_NON_INSTANTIABLE(_class_)                                  \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
class ConstructorImpl<_class_ > : public Constructor                         \
{                                                                            \
public:                                                                      \
    ConstructorImpl(const Class& owner) : Constructor(owner) {};             \
};                                                                           \
                                                                             \
} //namespace xm


#define XM_ASSUME_NON_DESTRUCTIBLE(_class_)                                  \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
class DestructorImpl<_class_ > : public Constructor                          \
{                                                                            \
public:                                                                      \
    DestructorImpl(const Class& owner) : DestructorImpl(owner) {};           \
};                                                                           \
                                                                             \
} //namespace xm


#define XM_ASSUME_ABSTRACT(_class_)                                          \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
struct IsAbstract<_class_ > : public TrueType{};                             \
                                                                             \
} /*namespace xm*/                                                           \
XM_ASSUME_NON_INSTANTIABLE(_class_)                                          \
XM_ASSUME_NON_COPYABLE(_class_)


#define XM_BUILD_CLASS(...) void xm::BuildClass<__VA_ARGS__>::operator()()


/**
 * \def XM_AUTOREG(_class_)
 * 
 * Ensure the class will be registered at program startup, or when the shared
 * object is loaded dynamically, with no extra code.
 * \a relfected_class is the class to be registered.
 */
#define XM_AUTOREG(_class_)                                               \
template class xm::AutoRegisterer<_class_ >;                              \



#endif	/* XM_MACROS_HPP */
