/* 
 * File:   Macros.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on August 4, 2012, 13.13
 */

#ifndef EXTMR_MACROS_HPP
#define	EXTMR_MACROS_HPP

/**
 * \def EXTMR_ENABLE_PRIMITIVE(primitive_type)
 * Specialize the TypeRecognizer class for the \a primitive_type
 */
#define EXTMR_ENABLE_PRIMITIVE(primitive_type)\
namespace extmr{\
\
template<>\
struct TypeRecognizer<primitive_type>\
{\
    /**
     * Get the same name returned by TypeRegister::getTypeName<T>();.
     * 
     * @return The type name.
     */\
    static std::string getName()\
    {\
        return #primitive_type;\
    }\
    \
    static const Type::Category category = Type::Primitive;\
};\
\
} // namespace extmr

/**
 * \def EXTMR_ENABLE_CLASS(reflected_class)
 * 
 * Enables reflection for the class \a reflected_class.
 * Place this macro in the same header of the \a reflected_class declaration, after the class declaration.
 */
#define EXTMR_ENABLE_CLASS(reflected_class)\
namespace extmr{\
\
/* TypeRecognizer template struct must be specialized in order to define the right name and category for the type.
This information is used during the registration phase of this type */\
template<>\
struct TypeRecognizer<reflected_class>\
{\
    static std::string getName()\
    {\
        return #reflected_class;\
    }\
\
    static const Type::Category category = Type::Class;\
};\
\
template<>\
struct ClassBuilder<reflected_class>\
{\
    void operator()(Class& clazz, TypeRegister& typeReg) const;\
};\
\
} // namespace extmr

/**
 * \def EXTMR_BUILD_CLASS(reflected_class)
 * 
 * Ensure the class will be registered at program start with no extra code.
 * \a relfected_class is the class to be build.
 */
#define EXTMR_BUILD_CLASS(reflected_class)\
void extmr::ClassBuilder<reflected_class>::operator()(Class& clazz, TypeRegister& typeReg) const

/**
 * \def EXTMR_AUTOREG(reflected_class)
 * 
 * Ensure the class will be registered at program start with no extra code.
 * \a relfected_class is the class to be registered.
 */
#define EXTMR_AUTOREG(reflected_class)\
static extmr::AutoRegisterer<reflected_class> autoRegisterer;

/**
 * \def EXTMR_PROPERTY_FLD(q_field)
 * 
 * Build a Property from a class field with the same name of the field.
 * the \a q_field parameter must be qualified with the class name.
 */
#define EXTMR_PROPERTY_FLD(q_field)\
buildProperty(getNonQualifiedName(#q_field), &q_field)

/**
 * \def EXTMR_METHOD(q_method)
 * 
 * Build a Method with the same name of the provided method.
 * \a q_method is the qualified method name.
 */
#define EXTMR_METHOD(q_method)\
buildMethod(getNonQualifiedName(#q_method), &q_method)

/**
 * \def EXTMR_ENABLE_N_BUILD_TCLASS_1(reflected_tclass)
 * 
 * Use to enable a template class instances to be registered within the reflection mechanism.
 * Works only with one typename parameter template classes.
 * After this macro, specify the body of the build funcion.
 */
#define EXTMR_ENABLE_N_BUILD_TCLASS_1(reflected_tclass)\
namespace extmr{\
\
template<typename T1>\
struct TypeRecognizer<reflected_tclass<T1> >\
{\
    static std::string getName()\
    {\
        std::string str = std::string(#reflected_tclass) + "<";\
        str += TypeRecognizer<T1>::getName();\
        if (str[str.length() - 1] == '>')\
        {\
            str += " ";\
        }\
        str += ">";\
        return str;\
    }\
    \
    static const Type::Category category = Type::CompClass;\
};\
\
template<typename _T1>\
struct TemplateRecognizer<reflected_tclass<_T1> >\
{\
    typedef _T1 T1;\
    typedef void T2;\
    typedef void T3;\
    typedef void T4;\
    static std::string getName()\
    {\
        return #reflected_tclass;\
    }\
    static const uint argN = 1;\
};\
\
template<typename T1>\
struct ClassBuilder<reflected_tclass<T1> >\
{\
    void operator()(Class& clazz, TypeRegister& typeReg) const;\
};\
\
} /* namespace extmr */ \
\
template<typename T1>\
void extmr::ClassBuilder<reflected_tclass<T1> >::operator()(Class& clazz, TypeRegister& typeReg) const

/**
 * \def EXTMR_ENABLE_N_BUILD_TCLASS_2(reflected_tclass)
 * 
 * Use to enable a template class instances to be registered within the reflection mechanism.
 * Works only with two typename parameters template classes.
 * After this macro, specify the body of the build function.
 */
#define EXTMR_ENABLE_N_BUILD_TCLASS_2(reflected_tclass)\
namespace extmr{\
\
template<typename T1, typename T2>\
struct TypeRecognizer<reflected_tclass<T1, T2> >\
{\
    static std::string getName()\
    {\
        std::string str = std::string(#reflected_tclass) + "<";\
        str += TypeRecognizer<T1>::getName() + ", " + TypeRecognizer<T2>::getName();\
        if (str[str.length() - 1] == '>')\
        {\
            str += " ";\
        }\
        str += ">";\
        return str;\
    }\
    \
    static const Type::Category category = Type::CompClass;\
};\
\
template<typename _T1, typename _T2>\
struct TemplateRecognizer<reflected_tclass<_T1, _T2> >\
{\
    typedef _T1 T1;\
    typedef _T2 T2;\
    typedef void T3;\
    typedef void T4;\
    static std::string getName()\
    {\
        return #reflected_tclass;\
    }\
    static const uint argN = 2;\
};\
\
template<typename T1,  typename T2>\
struct ClassBuilder<reflected_tclass<T1, T2> >\
{\
    void operator()(Class& clazz, TypeRegister& typeReg) const;\
};\
\
} /* namespace extmr */ \
\
template<typename T1, typename T2>\
void extmr::ClassBuilder<reflected_tclass<T1, T2> >::operator()(Class& clazz, TypeRegister& typeReg) const


/**
 * \def EXTMR_ENABLE_N_BUILD_TCLASS_3(reflected_tclass)
 * 
 * Use to enable a template class instances to be registered within the reflection mechanism.
 * Works only with three typename parameters template classes.
 * After this macro, specify the body of the build function.
 */
#define EXTMR_ENABLE_N_BUILD_TCLASS_3(reflected_tclass)\
namespace extmr{\
\
template<typename T1,  typename T2,  typename T3>\
struct TypeRecognizer<reflected_tclass<T1, T2, T3> >\
{\
    static std::string getName()\
    {\
        std::string str = std::string(#reflected_tclass) + "<";\
        str += TypeRecognizer<T1>::getName() + ", ";\
        str += TypeRecognizer<T2>::getName() + ", ";\
        str += TypeRecognizer<T3>::getName();\
        if (str[str.length() - 1] == '>')\
        {\
            str += " ";\
        }\
        str += ">";\
        return str;\
    }\
    \
    static const Type::Category category = Type::CompClass;\
};\
\
template<typename _T1,  typename _T2,  typename _T3>\
struct TemplateRecognizer<reflected_tclass<_T1, _T2, _T3> >\
{\
    typedef _T1 T1;\
    typedef _T2 T2;\
    typedef _T3 T3;\
    typedef void T4;\
    static std::string getName()\
    {\
        return #reflected_tclass;\
    }\
    static const uint argN = 3;\
};\
\
template<typename T1,  typename T2,  typename T3>\
struct ClassBuilder<reflected_tclass<T1, T2, T3> >\
{\
    void operator()(Class& clazz, TypeRegister& typeReg) const;\
};\
\
} /* namespace extmr */ \
\
template<typename T1, typename T2, typename T3>\
void extmr::ClassBuilder<reflected_tclass<T1, T2, T3> >::operator()(Class& clazz, TypeRegister& typeReg) const


/**
 * \def EXTMR_ENABLE_N_BUILD_TCLASS_4(reflected_tclass)
 * 
 * Use to enable a template class instances to be registered within the reflection mechanism.
 * Works only with four typename parameters template classes.
 * After this macro, specify the body of the build function.
 */
#define EXTMR_ENABLE_N_BUILD_TCLASS_4(reflected_tclass)\
namespace extmr{\
\
template<typename T1,  typename T2,  typename T3,  typename T4>\
struct TypeRecognizer<reflected_tclass<T1, T2, T3, T4> >\
{\
    static std::string getName()\
    {\
        std::string str = std::string(#reflected_tclass) + "<";\
        str += TypeRecognizer<T1>::getName() + ", ";\
        str += TypeRecognizer<T2>::getName() + ", ";\
        str += TypeRecognizer<T3>::getName() + ", ";\
        str += TypeRecognizer<T4>::getName();\
        if (str[str.length() - 1] == '>')\
        {\
            str += " ";\
        }\
        str += ">";\
        return str;\
    }\
    \
    static const Type::Category category = Type::CompClass;\
};\
\
template<typename _T1,  typename _T2,  typename _T3,  typename _T4>\
struct TemplateRecognizer<reflected_tclass<_T1, _T2, _T3, _T4> >\
{\
    typedef _T1 T1;\
    typedef _T2 T2;\
    typedef _T3 T3;\
    typedef _T4 T4;\
    static std::string getName()\
    {\
        return #reflected_tclass;\
    }\
    static const uint argN = 4;\
};\
\
template<typename T1,  typename T2,  typename T3,  typename T4>\
struct ClassBuilder<reflected_tclass<T1, T2, T3, T4> >\
{\
    void operator()(Class& clazz, TypeRegister& typeReg) const;\
};\
\
} /* namespace extmr */ \
\
template<typename T1, typename T2, typename T3, typename T4>\
void extmr::ClassBuilder<reflected_tclass<T1, T2, T3, T4> >::operator()(Class& clazz, TypeRegister& typeReg) const

/**
 * \def EXTMR_SETCALLBACK(reflected_tclass)
 * Set the call back function to call every time a type is registered.
 * Put this macro into a cpp file.
 * 
 * \a fnc The function for callback. The function must take a const Type reference as
 * argument and have a void return value.
 * 
 */
#define EXTMR_SETCALLBACK(fnc)\
void (*extmr::getRegCallBack())(const Type&)\
{\
    return fnc;\
}

/** \def EXTMR_METHOD_PARAM_MAX
 * The maximum number of parameter for supported methods
 */ 
#define EXTMR_METHOD_PARAM_MAX 8

/** \def EXTMR_TCLASS_PARAM_MAX
 * The maximum number of parameter for supported template classes
 */ 
#define EXTMR_TCLASS_PARAM_MAX 4

#endif	/* EXTMR_MACROS_HPP */

