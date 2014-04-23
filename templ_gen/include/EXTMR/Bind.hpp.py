content ="""
/******************************************************************************      
 *      Extended Mirror: Bind.hpp                                             *
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

#ifndef EXTMR_BIND_HPP
#define	EXTMR_BIND_HPP


#define EXTMR_GET_N_SET_EXTRA_PARAM_MAX """ + \
str(EXTMR_GET_N_SET_EXTRA_PARAM_MAX) + """
#define EXTMR_METHOD_PARAM_MAX """ + \
str(EXTMR_METHOD_PARAM_MAX) + """


#define EXTMR_MNP(member) #member, &ClassT::member
#define EXTMR_BIND_BASE(BaseT) bindBase<ClassT, BaseT>();
#define EXTMR_BIND_PASE(BaseT) bindPmBase<ClassT, BaseT>(); // polymorphic base


namespace extmr{


template<class ClassT, class BaseT>
void bindBase()
{
    // ensure that base class is registered
    registerType<BaseT>();
    
    Class& clazz = const_cast<Class&>(getClass<ClassT>());
    Class& base = const_cast<Class&>(getClass<BaseT>());
    
    // bind them together
    clazz & base;
    
    // bind RefCaster to base
    clazz & *new RefCasterImpl<ClassT, BaseT>();
}


template<class ClassT, class BaseT>
void bindPmBase()
{
    bindBase<ClassT, BaseT>();
    
    // bind RefCast from BaseT to CassT
    const_cast<Class&>(getClass<BaseT>()) & *new RefCasterImpl<BaseT, ClassT>();
}


/*
 * Collection of functions to allow registration of properties and methods
 * through the parameter type deduction mechanism.
 */

template<class ClassT, typename FieldT>
Property& bindProperty(const std::string& name, FieldT ClassT::* field)
{
    // ensure that the type is registered
    registerType<FieldT>();
    
    // build the Property  and add it to the Class
    return const_cast<Class&>(getClass<ClassT>())
            & *new PropertyField<ClassT, FieldT>(name, field);
}


template<class ClassT, typename FieldT, std::size_t size>
Property& bindProperty(const std::string& name,
        FieldT (ClassT::* field) [size])
{
    // ensure that the type is registered
    registerType<FieldT[size]>();
    
    // build the Property  and add it to the Class
    return const_cast<Class&>(getClass<ClassT>())
            & *new PropertyArrayField<ClassT, FieldT[size]>(name, field);
}

"""
for n_extr_params in range(EXTMR_GET_N_SET_EXTRA_PARAM_MAX + 1):
    for has_setter in range(2):
        for has_const_getter in range(2):
            content +="""
template
<
    class ClassT,
    typename RetT""" + (""",
    typename ParamT""" if has_setter else "") + gen_seq(""",
    typename ExtrParamT$""", n_extr_params) + """
>
Property& bindProperty(
    const std::string& name,
    RetT (ClassT::*getter)
    ( """ + gen_seq("""
        ExtrParamT$""", n_extr_params, ",") + """
    )""" + (" const" if has_const_getter else "") + (""",
    void (ClassT::*setter)
    (
        ParamT""" + gen_seq(""",
        ExtrParamT$""", n_extr_params) + """
    )""" if has_setter else "") + gen_seq(""",
    ExtrParamT$ extrArg$""", n_extr_params) + """
)
{   
    // ensure that the type is registered
    registerType<RetT>();
    """ + (("""
    // remove constness from the getter method
    RetT (ClassT::*getter_nc)() =
        reinterpret_cast
        <
            RetT (ClassT::*)
            (""" + gen_seq("""
                ExtrParamT$""", n_extr_params, ",") + """
            )
        >(getter);
        """) if has_const_getter else "") + ("""
    // setter points to NULL
    void (ClassT::*setter)(Empty) =
        static_cast<void(ClassT::*)(Empty)>(NULL);"""
            if not has_setter else "") + """
    
    // build the Property
    return const_cast<Class&>(getClass<ClassT>())
        & *new PropertyGetterNSetter_""" + str(n_extr_params) + \
        """_ExtrParams
        <
            ClassT,
            RetT""" + (""",
            ParamT""" if has_setter else """,
            Empty""") + gen_seq(""",
            ExtrParamT$""", n_extr_params) + """
        >
        (
            name""" + (""",
            getter_nc,
            true""" if has_const_getter else """,
            getter,
            false""") + """,
            setter""" + gen_seq(""",
            extrArg$""", n_extr_params) + """
        );
}

"""

for n_params in range(EXTMR_METHOD_PARAM_MAX + 1):
    for is_const in range(2):
        content += """
template
<
    class ClassT,
    typename RetT""" + gen_seq(""",
    typename ParamT$""", n_params) + """
>
Method& bindMethod
(
    const std::string& name,
    RetT (ClassT::*method)
    ( """ + gen_seq("""
        ParamT$""", n_params, ",") + """
    ) """ + ("const" if is_const else "") + """
)
{
    // ensure the types are registered
    registerType<RetT>();""" + gen_seq("""
    registerType<ParamT$>();""", n_params) + """
    """ + (("""
    // remove the constness from the method
    RetT (ClassT::*method_nc)() =
        reinterpret_cast
        <
            RetT (ClassT::*)
            (""" + gen_seq("""
                ParamT$""", n_params, ",") + """
            )
        >(method);
    """) if is_const else "") + """
    // create the proper Method
    return const_cast<Class&>(getClass<ClassT>())
        & *new MethodImpl_""" + str(n_params) + """_Params
        <
            ClassT,
            RetT""" + gen_seq(""",
            ParamT$""", n_params) + """
        >
        (
            name""" + (""",
            method_nc,
            true""" if is_const else """,
            method,
            false""") + """
        );
}

"""

content += """
} // namespace extmr

#endif	/* EXTMR_BIND_HPP */"""

