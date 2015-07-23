/******************************************************************************      
 *      Extended Mirror: RegistrationMacros.hpp                               *
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


#ifndef XM_REGISTRATIONMACROS_HPP
#define	XM_REGISTRATIONMACROS_HPP

#include <XM/TemplateRegistrationMacros.hpp>

/**
 * \def XM_DECLARE_PRIMITIVE(_primitive_type_)
 * Specialize the GetTypeName class for the \a _primitive_type_
 */
#define XM_DECLARE_PRIMITIVE(_primitive_type_)                                \
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
 * \def XM_DECLARE_CLASS(_class_)
 * 
 * GetTypeName template struct is specialized in order to define the right
 * name and category for the type.
 * This information is used during the registration phase of this type.
 * 
 * Enables reflection for the class \a _class_.
 * Place this macro in the same header of the \a _class_ declaration,
 * after the class declaration.
 */
#define XM_DECLARE_CLASS(...)                                                \
namespace xm{                                                                \
                                                                             \
template<>                                                                   \
struct GetTypeName<__VA_ARGS__>                                              \
{                                                                            \
    std::string operator()()                                                 \
    {                                                                        \
        return #__VA_ARGS__;                                                 \
    }                                                                        \
};                                                                           \
                                                                             \
template<>                                                                   \
struct DefineClass<__VA_ARGS__>                                              \
{                                                                            \
    typedef __VA_ARGS__ ClassT;                                              \
    void operator()();                                                       \
};                                                                           \
                                                                             \
template<>                                                                   \
struct CreateType<__VA_ARGS__>                                               \
{                                                                            \
    Type& operator()()                                                       \
    {                                                                        \
        return createClass<__VA_ARGS__ >();                                  \
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


#define XM_DEFINE_CLASS(...) void xm::DefineClass<__VA_ARGS__>::operator()()


/**
 * \def XM_REGISTER_TYPE(_type_)
 * 
 * Ensure the type will be registered at program startup, or when the shared
 * object is loaded dynamically, with no extra code.
 * \a relfected_class is the class to be registered.
 */
#define XM_REGISTER_TYPE(...)                                                \
template class xm::TypeRegisterer<__VA_ARGS__>;                              \


#define XM_BIND_FREE_ITEMS                                                   \
_XM_BIND_FREE_ITEMS(__LINE__)

#define _XM_BIND_FREE_ITEMS(_uid_)                                           \
namespace xm {                                                               \
struct _XM_TOKENPASTE2(FreeBinder, _uid_)                                    \
{                                                                            \
    _XM_TOKENPASTE2(FreeBinder, _uid_)();                                    \
} _XM_TOKENPASTE2(freeBinder, _uid_);                                        \
}                                                                            \
xm::_XM_TOKENPASTE2(FreeBinder, _uid_)::_XM_TOKENPASTE2(FreeBinder, _uid_)()


#endif	/* XM_REGISTRATIONMACROS_HPP */
