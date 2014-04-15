/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_MACROS_HPP
#define	EXTMR_MACROS_HPP


/**
 * \def EXTMR_ENABLE_PRIMITIVE(_primitive_type_)
 * Specialize the GetTypeName class for the \a _primitive_type_
 */
#define EXTMR_ENABLE_PRIMITIVE(_primitive_type_)                               \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeName<_primitive_type_>                                           \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_primitive_type_;                                              \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_CLASS(_class_)
 * 
 * GetTypeName template struct is specialized in order to define the right
 * name and category for the type.
 * This information is used during the registration phase of this type.
 * 
 * Enables reflection for the class \a _class_.
 * Place this macro in the same header of the \a _class_ declaration,
 * after the class declaration.
 */
#define EXTMR_ENABLE_CLASS(_class_)                                            \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeName<_class_ >                                                   \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_class_;                                                       \
    }                                                                          \
};                                                                             \
                                                                               \
template<>                                                                     \
struct BuildClass<_class_>                                                     \
{                                                                              \
    void operator()(Class& clazz) const;                                       \
};                                                                             \
                                                                               \
template<>                                                                     \
struct CreateType<_class_>                                                     \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createClass<_class_ >();                                        \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


#define EXTMR_ASSUME_NON_COPYABLE(_class_)                                     \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeCopyConstructor<_class_ >                                        \
{                                                                              \
    CopyConstructor* operator()()                                              \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                                 \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeConstructor<_class_ >                                            \
{                                                                              \
    Constructor* operator()()                                                  \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                   \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeAssignOperator<_class_ >                                         \
{                                                                              \
    AssignOperator* operator()()                                               \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_NON_DESTRUCTIBLE(_class_)                                 \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct GetTypeDestructor<_class_ >                                             \
{                                                                              \
    Destructor* operator()()                                                   \
    {                                                                          \
        return NULL;                                                           \
    }                                                                          \
};                                                                             \
                                                                               \
} //namespace extmr


#define EXTMR_ASSUME_ABSTRACT(_class_)                                         \
namespace extmr{                                                               \
                                                                               \
template<>                                                                     \
struct IsAbstract<_class_ > : public TrueType{};                               \
                                                                               \
} /*namespace extmr*/                                                          \
EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                                         \
EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                           \
EXTMR_ASSUME_NON_COPYABLE(_class_)


#define EXTMR_BUILD_CLASS(...)                                                 \
void extmr::BuildClass<__VA_ARGS__>::operator()(Class& clazz) const


/**
 * \def EXTMR_AUTOREG(_class_)
 * 
 * Ensure the class will be registered at program startup, or when the shared
 * object is loaded dynamically, with no extra code.
 * \a relfected_class is the class to be registered.
 */
#define EXTMR_AUTOREG(_class_)                                                 \
template class extmr::AutoRegisterer<_class_ >;


/**
 * \def EXTMR_ENABLE_TEMPLATE_1(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with one type parameter template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_1(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1>                                                          \
struct GetTypeName<_template_<T1> >                                            \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct GetTemplateName<_template_<T1> >                                        \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct GetTemplateArgs<_template_<T1> >                                        \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct BuildClass<_template_<T1> >                                             \
{                                                                              \
    void operator()(Class& clazz) const;                                       \
};                                                                             \
                                                                               \
template<typename T1>                                                          \
struct CreateType<_template_<T1> >                                             \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1> >();                         \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_2(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with two type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_2(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTypeName<_template_<T1, T2> >                                        \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()();                                            \
        str += ", " + GetTypeName<T2>()();                                     \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTemplateName<_template_<T1, T2> >                                    \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct GetTemplateArgs<_template_<T1, T2> >                                    \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2>                                            \
struct BuildClass<_template_<T1, T2> >                                         \
{                                                                              \
    void operator()(Class& clazz) const;                                       \
};                                                                             \
                                                                               \
template<typename T1, typename T2>                                             \
struct CreateType<_template_<T1, T2> >                                         \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2> >();                     \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_3(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with three type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_3(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1,  typename T2,  typename T3>                              \
struct GetTypeName<_template_<T1, T2, T3> >                                    \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()() + ", ";                                     \
        str += GetTypeName<T2>()() + ", ";                                     \
        str += GetTypeName<T3>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct GetTemplateName<_template_<T1, T2, T3> >                                \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct GetTemplateArgs<_template_<T1, T2, T3> >                                \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        templateArgs.push_back(&typeReg.registerType<T3>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2,  typename T3>                              \
struct BuildClass<_template_<T1, T2, T3> >                                     \
{                                                                              \
    void operator()(Class& clazz) const;                                       \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3>                                \
struct CreateType<_template_<T1, T2, T3> >                                     \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2, T3> >();                 \
    }                                                                          \
};                                                                             \
                                                                               \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_ENABLE_TEMPLATE_4(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with four type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_4(_template_)                                    \
namespace extmr{                                                               \
                                                                               \
template<typename T1,  typename T2,  typename T3,  typename T4>                \
struct GetTypeName<_template_<T1, T2, T3, T4> >                                \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        std::string str = std::string(#_template_) + "<";                      \
        str += GetTypeName<T1>()() + ", ";                                     \
        str += GetTypeName<T2>()() + ", ";                                     \
        str += GetTypeName<T3>()() + ", ";                                     \
        str += GetTypeName<T4>()();                                            \
        if (str[str.length() - 1] == '>')                                      \
        {                                                                      \
            str += " ";                                                        \
        }                                                                      \
        str += ">";                                                            \
        return str;                                                            \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct GetTemplateName<_template_<T1, T2, T3, T4> >                            \
{                                                                              \
    std::string operator()()                                                   \
    {                                                                          \
        return #_template_;                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct GetTemplateArgs<_template_<T1, T2, T3, T4> >                            \
{                                                                              \
    Const_Type_Vector operator()()                                             \
    {                                                                          \
        Const_Type_Vector templateArgs;                                        \
        TypeRegister& typeReg = TypeRegister::getSingleton();                  \
        templateArgs.push_back(&typeReg.registerType<T1>());                   \
        templateArgs.push_back(&typeReg.registerType<T2>());                   \
        templateArgs.push_back(&typeReg.registerType<T3>());                   \
        templateArgs.push_back(&typeReg.registerType<T4>());                   \
        return templateArgs;                                                   \
    }                                                                          \
};                                                                             \
                                                                               \
template<typename T1,  typename T2,  typename T3,  typename T4>                \
struct BuildClass<_template_<T1, T2, T3, T4> >                                 \
{                                                                              \
    void operator()(Class& clazz) const;                                       \
};                                                                             \
                                                                               \
template<typename T1, typename T2, typename T3, typename T4>                   \
struct CreateType<_template_<T1, T2, T3, T4> >                                 \
{                                                                              \
    Type* operator()()                                                         \
    {                                                                          \
        return createCompoundClass<_template_<T1, T2, T3, T4> >();             \
    }                                                                          \
};                                                                             \
                                                                               \
} // namespace extmr


/**
 * \def EXTMR_SETCALLBACK(fnc)
 * Set the call back function to call every time a type is registered.
 * Put this macro into a cpp file.
 * 
 * \a fnc The function for callback. The function must take a const Type
 * reference as argument and have a void return value.
 * 
 */
#define EXTMR_SETCALLBACK(fnc)                                                 \
namespace extmr {                                                              \
                                                                               \
void (*TypeRegister::getRegCallBack())(const Type&)                            \
{                                                                              \
    return fnc;                                                                \
}                                                                              \
                                                                               \
} // namespace extmr


/** \def EXTMR_GET_N_SET_EXTRA_PARAM_MAX
 * The maximum number of supported extra parameter for getters and setters
 */ 
#define EXTMR_GET_N_SET_EXTRA_PARAM_MAX 3


/** \def EXTMR_METHOD_PARAM_MAX
 * The maximum number of parameters for supported methods
 */ 
#define EXTMR_METHOD_PARAM_MAX 8


/** \def EXTMR_TEMPLATE_PARAM_MAX
 * The maximum number of parameter for supported template classes
 */ 
#define EXTMR_TEMPLATE_PARAM_MAX 4


#endif	/* EXTMR_MACROS_HPP */

