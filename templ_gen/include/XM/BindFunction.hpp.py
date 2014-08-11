content ="""
/******************************************************************************      
 *      Extended Mirror: BindFunction.hpp                                     *
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

#ifndef XM_BINDFUNCTION_HPP
#define	XM_BINDFUNCTION_HPP


#define XM_FUNCTION_PARAM_MAX """ + \
str(XM_FUNCTION_PARAM_MAX) + """


namespace xm {

"""
for n_params in range(XM_FUNCTION_PARAM_MAX + 1):
    content += """
template
<
    typename RetT""" + gen_seq(""",
    typename ParamT$""", n_params) + """
>
Function& bindFunction
(
    const std::string& name,
    Namespace& name_space,
    RetT (*function)
    ( """ + gen_seq("""
        ParamT$""", n_params, ",") + """
    )
)
{
    // ensure the types are registered
    registerType<RetT>();""" + gen_seq("""
    registerType<ParamT$>();""", n_params) + """

    // create the proper Function
    Function* xmFunction = new FunctionImpl_""" + str(n_params) + """_Params
        <
            RetT""" + gen_seq(""",
            ParamT$""", n_params) + """
        >
        ( name, function );
    name_space.add<Function>(*xmFunction);
    return *xmFunction;
}

"""

content += """

} // namespace xm

#endif	/* XM_BINDFUNCTION_HPP */"""