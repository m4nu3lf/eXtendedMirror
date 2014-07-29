content = """
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

""" + WARNING_MESSAGE + """

#ifndef EXTMR_MACROS_HPP
#define	EXTMR_MACROS_HPP


/**
 * \def EXTMR_ENABLE_PRIMITIVE(_primitive_type_)
 * Specialize the GetTypeName class for the \\a _primitive_type_
 */
#define EXTMR_ENABLE_PRIMITIVE(_primitive_type_)                             \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
struct GetTypeName<_primitive_type_>                                         \\
{                                                                            \\
    std::string operator()()                                                 \\
    {                                                                        \\
        return #_primitive_type_;                                            \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
} // namespace extmr


/**
 * \def EXTMR_ENABLE_CLASS(_class_)
 * 
 * GetTypeName template struct is specialized in order to define the right
 * name and category for the type.
 * This information is used during the registration phase of this type.
 * 
 * Enables reflection for the class \\a _class_.
 * Place this macro in the same header of the \\a _class_ declaration,
 * after the class declaration.
 */
#define EXTMR_ENABLE_CLASS(_class_)                                          \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
struct GetTypeName<_class_ >                                                 \\
{                                                                            \\
    std::string operator()()                                                 \\
    {                                                                        \\
        return #_class_;                                                     \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
template<>                                                                   \\
struct BuildClass<_class_>                                                   \\
{                                                                            \\
    typedef _class_ ClassT;                                                  \\
    void operator()();                                                       \\
};                                                                           \\
                                                                             \\
template<>                                                                   \\
struct CreateType<_class_>                                                   \\
{                                                                            \\
    Type* operator()()                                                       \\
    {                                                                        \\
        return createClass<_class_ >();                                      \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
} // namespace extmr


#define EXTMR_ASSUME_NON_COPYABLE(_class_)                                   \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
class CopyConstructorImpl<_class_ > : public CopyConstructor                 \\
{                                                                            \\
public:                                                                      \\
    CopyConstructorImpl(const Class& owner) : CopyConstructor(owner) {};     \\
};                                                                           \\
                                                                             \\
} //namespace extmr


#define EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                               \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
class ConstructorImpl<_class_ > : public Constructor                         \\
{                                                                            \\
public:                                                                      \\
    ConstructorImpl(const Class& owner) : Constructor(owner) {};             \\
};                                                                           \\
                                                                             \\
} //namespace extmr


#define EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                 \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
class AssignOperatorImpl<_class_ > : public AssignOperator                   \\
{                                                                            \\
public:                                                                      \\
    AssignOperatorImpl(const Class& owner) : AssignOperator(owner) {};       \\
};                                                                           \\
                                                                             \\
} //namespace extmr


#define EXTMR_ASSUME_NON_DESTRUCTIBLE(_class_)                               \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
class DestructorImpl<_class_ > : public Constructor                          \\
{                                                                            \\
public:                                                                      \\
    DestructorImpl(const Class& owner) : DestructorImpl(owner) {};           \\
};                                                                           \\
                                                                             \\
} //namespace extmr


#define EXTMR_ASSUME_ABSTRACT(_class_)                                       \\
namespace extmr{                                                             \\
                                                                             \\
template<>                                                                   \\
struct IsAbstract<_class_ > : public TrueType{};                             \\
                                                                             \\
} /*namespace extmr*/                                                        \\
EXTMR_ASSUME_NON_INSTANTIABLE(_class_)                                       \\
EXTMR_ASSUME_NON_ASSIGNABLE(_class_)                                         \\
EXTMR_ASSUME_NON_COPYABLE(_class_)


#define EXTMR_BUILD_CLASS(...) void extmr::BuildClass<__VA_ARGS__>::operator()()


/**
 * \def EXTMR_AUTOREG(_class_)
 * 
 * Ensure the class will be registered at program startup, or when the shared
 * object is loaded dynamically, with no extra code.
 * \\a relfected_class is the class to be registered.
 */
#define EXTMR_AUTOREG(_class_)                                               \\
template class extmr::AutoRegisterer<_class_ >;


#define EXTMR_TEMPLATE_PARAM_MAX """ + str(EXTMR_TEMPLATE_PARAM_MAX) + """
"""

for n_temp_params in range(1, EXTMR_TEMPLATE_PARAM_MAX + 1):
    content += """

/**
 * \def EXTMR_ENABLE_TEMPLATE_""" + str(n_temp_params) + """(_template_)
 * 
 * Use to enable instances of template class to be registered as such.
 * 
 * Works only with two type parameters template classes.
 * After this macro, specify the body of the building function.
 */
#define EXTMR_ENABLE_TEMPLATE_""" + str(n_temp_params) + """(_template_)     \\
namespace extmr{                                                             \\
                                                                             \\
template                                                                     \\
<                                                                            \\
  typename T0""" + gen_seq(""",                                              \\
  typename T$""", (1, n_temp_params)) + """                                  \\
>                                                                            \\
struct GetTypeName                                                           \\
<                                                                            \\
    _template_                                                               \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    >                                                                        \\
>                                                                            \\
{                                                                            \\
    std::string operator()()                                                 \\
    {                                                                        \\
        std::string str = std::string(#_template_) + "<";                    \\
        str += GetTypeName<T0>()();""" + gen_seq("""                         \\
        str += ", " + GetTypeName<T$>()();""", (1, n_temp_params)) + """     \\
        if (str[str.length() - 1] == '>')                                    \\
        {                                                                    \\
            str += " ";                                                      \\
        }                                                                    \\
        str += ">";                                                          \\
        return str;                                                          \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
template                                                                     \\
<                                                                            \\
    typename T0""" + gen_seq(""",                                            \\
    typename T$""", (1, n_temp_params)) + """                                \\
>                                                                            \\
struct GetTemplateName                                                       \\
<                                                                            \\
    _template_                                                               \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    >                                                                        \\
>                                                                            \\
{                                                                            \\
    std::string operator()()                                                 \\
    {                                                                        \\
        return #_template_;                                                  \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
template                                                                     \\
<                                                                            \\
    typename T0""" + gen_seq(""",                                            \\
    typename T$""", (1, n_temp_params)) + """                                \\
>                                                                            \\
struct GetTemplateArgs                                                       \\
<                                                                            \\
    _template_                                                               \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    >                                                                        \\
>                                                                            \\
{                                                                            \\
    Const_Type_Vector operator()()                                           \\
    {                                                                        \\
        Const_Type_Vector templateArgs;                                      \\
        TypeRegister& typeReg = TypeRegister::getSingleton();                \\
        templateArgs.push_back(&typeReg.registerType<T0>());""" + gen_seq("""\\
        templateArgs.push_back(&typeReg.registerType<T$>());""", \
        (1, n_temp_params)) + """ \\
        return templateArgs;                                                 \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
template                                                                     \\
<                                                                            \\
    typename T0""" + gen_seq(""",                                            \\
    typename T$""", (1, n_temp_params)) + """                                \\
>                                                                            \\
struct BuildClass                                                            \\
<                                                                            \\
    _template_                                                               \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    >                                                                        \\
>                                                                            \\
{                                                                            \\
    typedef _template_                                                       \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    > ClassT;                                                                \\
    void operator()();                                                       \\
};                                                                           \\
                                                                             \\
template                                                                     \\
<                                                                            \\
    typename T0""" + gen_seq(""",                                            \\
    typename T$""", (1, n_temp_params)) + """                                \\
>                                                                            \\
struct CreateType                                                            \\
<                                                                            \\
    _template_                                                               \\
    <                                                                        \\
        T0""" + gen_seq(""",                                                 \\
        T$""", (1, n_temp_params)) + """                                     \\
    >                                                                        \\
>                                                                            \\
{                                                                            \\
    Type* operator()()                                                       \\
    {                                                                        \\
        return createCompoundClass                                           \\
                <                                                            \\
                    _template_                                               \\
                    <                                                        \\
                        T0""" + gen_seq(""",                                 \\
                        T$""", (1, n_temp_params)) + """                     \\
                    >                                                        \\
                >();                                                         \\
    }                                                                        \\
};                                                                           \\
                                                                             \\
} // namespace extmr

"""

content += """

#endif	/* EXTMR_MACROS_HPP */"""

