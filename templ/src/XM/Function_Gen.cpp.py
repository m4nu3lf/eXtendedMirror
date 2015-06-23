##############################################################################
#      Extended Mirror: Function_Gen.cpp.py                                  #
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

#include <XM/Utils/Utils.hpp>
#include <XM/xMirror.hpp>

using namespace std;
using namespace xm;

Function::Function
(
    const string& uName,
    const Type& retType,""" + gen_seq("""
    const Type& paramType$""", XM_FUNCTION_PARAM_MAX, ",") + """
) :
    Item(uName),
    retType_(&retType),
    fullSignature_(true)
{
    this->retType_ = &retType;""" + gen_seq("""
    if (paramType$ != getType<void>())
	params_.push_back(new Parameter(paramType$));""",
XM_FUNCTION_PARAM_MAX) + """
}

Variant Function::call
(""" + gen_seq("""
    const Variant& arg$""", XM_FUNCTION_PARAM_MAX, ",") + """
) const
{""" + gen_seq("""
    Variant& ncArg$ = const_cast<Variant&>(arg$);""",
XM_FUNCTION_PARAM_MAX) + """
    
    // variants are const anyway
    vector<Variant>& defaults = const_cast<vector<Variant>& >(defaults_);
    
    """
for i in range(XM_FUNCTION_PARAM_MAX):
  if i != 0:
    content += "\n    else "
  content +="""if (&ncArg""" + str(i) + """ == &Variant::Null)
    {
        return callImpl
        (""" + gen_seq("""
            ncArg$""", i, ",") + ("," if i!=0 else "") + gen_seq("""
            defaults[$]""", (i, XM_FUNCTION_PARAM_MAX), ",") + """
        );
    }"""
content += """
    else
    {
        return callImpl
        (""" + gen_seq("""
            ncArg$""", XM_FUNCTION_PARAM_MAX, ",") + """
        );
    }
}


Variant Function::callV(vector<Variant> args) const
{
    args.resize(XM_FUNCTION_PARAM_MAX, Variant::Null);
    return call
    (""" + gen_seq("""
        args[$]""" , XM_FUNCTION_PARAM_MAX, ",") + """
    );
}


Variant Function::callImpl
(""" + gen_seq("""
    Variant& arg$""", XM_FUNCTION_PARAM_MAX, ",") + """
) const
{""" + gen_seq("""
    (void)(arg$);""", XM_FUNCTION_PARAM_MAX) + """
    return Variant::Null;
}


void Function::setDefaultArgs
(""" + gen_seq("""
    const Variant& arg$""", XM_FUNCTION_PARAM_MAX, ",") + """
)
{""" + gen_seq("""
    Variant& ncArg$ = const_cast<Variant&>(arg$);""",
XM_FUNCTION_PARAM_MAX) + """
    
    defaults_.clear();
    defaults_.resize(XM_FUNCTION_PARAM_MAX);""" + gen_seq("""
    ncArg$.setConst();
    defaults_[$] = arg$;""", XM_FUNCTION_PARAM_MAX) + """
}


Function::~Function()
{
    Const_Prameter_Vector::iterator ite = params_.begin();
    while(ite != params_.end())
    {
        delete *ite;
        ite ++;
    }
}
"""
