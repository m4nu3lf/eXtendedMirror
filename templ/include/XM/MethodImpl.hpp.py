##############################################################################
#      Extended Mirror: MethodImpl.hpp.py                                    #
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

#ifndef XM_METHODIMPL_HPP
#define	XM_METHODIMPL_HPP

#include <XM/Exceptions/VariantCostnessException.hpp>

namespace xm{

"""
for n_params in range(1, XM_FUNCTION_PARAM_MAX + 1):
    for ret_t_void in range(2):
        content += """
template
<
    class ClassT""" + (""",
    typename RetT""" if not ret_t_void else "") + gen_seq(""",
    typename ParamT$""", (1, n_params)) + """
>
class MethodImpl_""" + str(n_params) + """_Params""" + (("""
<
    ClassT,
    void""" + gen_seq(""",
    ParamT$""", (1, n_params)) + """
>""") if ret_t_void else "") + """ : public Method
{
public: """ + ("""
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;""" if not ret_t_void else """
        typedef void RetT;""") + """

    /// type of the arguments without any cv-qualifier and no reference""" \
    + gen_seq("""
    typedef typename RemoveConst<typename RemoveReference<ParamT$>::Type>::Type
        NqParamT$;""", (1, n_params)) + """
    
    MethodImpl_""" + str(n_params) + """_Params(const std::string& uName,
        RetT (ClassT::*method)
        (""" + gen_seq("""
            ParamT$""", (1, n_params), ",") + """
        ),
        bool constant = false) :
        Item(uName, getClass<ClassT>()),
        method_(method),
        constant_(constant)
    {
        addParameter(*new Parameter(getType<ClassT>())); """ + gen_seq("""
        addParameter(*new Parameter(getType<ParamT$>()));""", (1, n_params)) + """
    }

    """ + ("""
    Function::ReturnMode getReturnMode() const
    {
        if (IsReference<RetT>::value)
        {
            if (IsConst<RetT>::value)
                return ConstReference;
            else
                return Reference;
        }
        else
            return Value;
    }""" if not ret_t_void else """
    Function::ReturnMode getReturnMode() const
    {
        return None;
    }
    """) + """
    
    bool isConst() const
    {
        return constant_;
    }
    
    
    Variant callImpl
    (   """ + gen_seq("""
        const Variant& arg$""", XM_FUNCTION_PARAM_MAX, ",") + """
        
    ) const
    {
        ClassT& objRef = arg0.as<ClassT>();
        
        // cannot call a non constant method of a constant instance
        if (arg0.isConst() && !constant_)
            throw VariantCostnessException(arg0.getType());
        """ + (("""
        const NqRetT& returnValue = (arg0.as<ClassT>().*method_)
        (""" + gen_seq("""
            arg$.as<NqParamT$>()""", (1, n_params), ",") + """
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        """) if not ret_t_void else """
        (arg0.as<ClassT>().*method_)
        (""" + gen_seq("""
            arg$.as<NqParamT$>()""", (1, n_params), ",") + """
        );
        return Variant::Null;
        """) + """
    }

private:
    RetT (ClassT::*method_)
    (""" + gen_seq("""
        ParamT$""", (1, n_params), ",") + """
    );

    /// Whether the method is constant.
    bool constant_;
};

"""

content += """

} // namespace xm

#endif /* XM_METHODIMPL_HPP */"""