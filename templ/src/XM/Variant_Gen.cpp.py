##############################################################################
#      Extended Mirror: Variant_Gen.cpp.py                                   #
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

#include <XM/xMirror.hpp>

using namespace std;
using namespace xm;

Variant Variant::call
(
    const std::string& methodName,""" + gen_seq("""
    const Variant& arg$""", XM_FUNCTION_PARAM_MAX - 1, ",") + """
)
{   
    const Class* clazz = dynamic_cast<const Class*>(type_);
    if (clazz)
    {
        Method keyMethod
        (
            methodName,
            xm::getType<void>(),
            *clazz,""" + gen_seq("""
            arg$.getType()""", XM_FUNCTION_PARAM_MAX - 1, ",") + """
        );
        const Method& callableMethod = clazz->getMethod(keyMethod);
        
        return callableMethod.call(
                                      *this,""" + gen_seq("""
                                      arg$""",
XM_FUNCTION_PARAM_MAX - 1, ",") + """
        );
    }
    else
    {
        // TODO: throw something appropriate
        throw 0;
    }
}


Variant Variant::callV(const std::string& methodName,
        vector<Variant>& args)
{
    args.resize(XM_FUNCTION_PARAM_MAX, Variant::Null);
    return call
    (
        methodName,""" + gen_seq("""
        args[$]""", XM_FUNCTION_PARAM_MAX - 1, ",") + """
    );
}
"""