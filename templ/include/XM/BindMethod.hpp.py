##############################################################################
#      Extended Mirror: BindMethod.hpp.py                                    #
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


content ="""

#ifndef XM_BINDMETHOD_HPP
#define	XM_BINDMETHOD_HPP


namespace xm {

"""
for n_params in range(1, XM_FUNCTION_PARAM_MAX + 1):
    for is_const in range(2):
        content += """

template
<
    class ClassT,
    typename RetT""" + gen_seq(""",
    typename ParamT$""", (1, n_params)) + """
>
Method& bindMethod
(
    const std::string& name,
    RetT (ClassT::*method)
    ( """ + gen_seq("""
        ParamT$""", (1, n_params), ",") + """
    ) """ + ("const" if is_const else "") + """
)
{
    // ensure the types are registered
    registerType<RetT>();""" + gen_seq("""
    registerType<ParamT$>();""", (1, n_params)) + """
    """ + (("""
    // remove the constness from the method
    RetT (ClassT::*method_nc)() =
        reinterpret_cast
        <
            RetT (ClassT::*)
            (""" + gen_seq("""
                ParamT$""", (1, n_params), ",") + """
            )
        >(method);
    """) if is_const else "") + """
    // create the proper Method
    Method* xmMethod = new MethodImpl_""" + str(n_params) + """_Params
        <
            ClassT,
            RetT""" + gen_seq(""",
            ParamT$""", (1, n_params)) + """
        >
        (
            name""" + (""",
            method_nc,
            true""" if is_const else """,
            method,
            false""") + """
        );

    const_cast<Class&>(getClass<ClassT>()).addMember(*xmMethod);
    return *xmMethod;
}

"""

content += """

} // namespace xm

#endif	/* XM_BINDMETHOD_HPP */"""