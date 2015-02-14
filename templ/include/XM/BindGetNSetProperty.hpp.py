##############################################################################
#      Extended Mirror: BindGetNSetProperty.hpp.py                           #
##############################################################################
#      Copyright (c) 2012-2015, Manuele Finocchiaro                          #
#      All rights reserved.                                                  #
##############################################################################
# Redistribution and use in source and binary forms, with or without         #
# modification, are permitted provided that the following conditions         #
# are met:                                                                   #
#                                                                            #
#    1. Redistributions of source code must retain the above copyright       #
#       notice, this list of conditions and the following disclaimer.        #
#                                                                            #
#    2. Redistributions in binary form must reproduce the above copyright    #
#       notice, this list of conditions and the following disclaimer in      #
#       the documentation and/or other materials provided with the           #
#       distribution.                                                        #
#                                                                            #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"# 
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE #
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  #
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       #
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   #
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    #
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    #
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     #
# THE POSSIBILITY OF SUCH DAMAGE.                                            #
##############################################################################


content = """

#ifndef XM_BINDGETNSETPROPERTY_HPP
#define	XM_BINDGETNSETPROPERTY_HPP


#define XM_GET_N_SET_EXTRA_PARAM_MAX """ + \
str(XM_GET_N_SET_EXTRA_PARAM_MAX) + """


namespace xm{

"""
for n_extr_params in range(XM_GET_N_SET_EXTRA_PARAM_MAX + 1):
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
    Property* xmProperty =
        new PropertyGetterNSetter_""" + str(n_extr_params) + \
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
    const_cast<Class&>(getClass<ClassT>()).addMember(*xmProperty);
    return *xmProperty;
}

"""

content += """

} // namespace xm

#endif	/* XM_BINDGETNSETPROPERTY_HPP */"""

