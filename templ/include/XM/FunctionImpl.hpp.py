##############################################################################
#      Extended Mirror: FunctionImpl.hpp.py                                  #
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

#ifndef XM_FUNCTIONIMPL_HPP
#define	XM_FUNCTIONIMPL_HPP

namespace xm{

"""
for n_params in range(XM_FUNCTION_PARAM_MAX + 1):
    for ret_t_void in range(2):
        content += """
template
<""" + ("""
    typename RetT""" if not ret_t_void else "") \
+ ("," if not ret_t_void and n_params else "") + gen_seq("""
    typename ParamT$""", n_params, ",") + """
>
class FunctionImpl_""" + str(n_params) + """_Params""" + (("""
<
    void""" + gen_seq(""",
    ParamT$""", n_params) + """
>""") if ret_t_void else "") + """ : public Function
{
public: """ + ("""
    /// type of the return value without any cv-qualifier and no reference
    typedef typename RemoveConst<typename RemoveReference<RetT>::Type>::Type
        NqRetT;""" if not ret_t_void else """
        typedef void RetT;""") + """

    /// type of the arguments without any cv-qualifier and no reference""" \
    + gen_seq("""
    typedef typename RemoveConst<typename RemoveReference<ParamT$>::Type>::Type
        NqParamT$;""", n_params) + """
    
    FunctionImpl_""" + str(n_params) + """_Params(
        const std::string& uName,
        const xm::Namespace& name_space,
        RetT function
        (""" + gen_seq("""
            ParamT$""", n_params, ",") + """
        )) :
        Item(uName, name_space),
        Function(
            uName,
            getType<RetT>()""" + ("," if n_params > 0 else """
            """) + gen_seq("""
            getType<ParamT$>()""", (0, n_params), ",") + """
        ),
        function_(function)
    {
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
    
    
    Variant callImpl
    (   """ + gen_seq("""
        Variant& arg$""", XM_FUNCTION_PARAM_MAX, ",") + """
        
    ) const
    {""" + gen_seq("""
        (void)(arg$);""", (n_params, XM_FUNCTION_PARAM_MAX)) + (("""
        const NqRetT& returnValue = function_
        (""" + gen_seq("""
            arg$.as<NqParamT$>()""", n_params, ",") + """
        );
        return Variant(const_cast<NqRetT&>(returnValue),
                ReturnVariantFlags<RetT>::flags);
        """) if not ret_t_void else """
        function_
        (""" + gen_seq("""
            arg$.as<NqParamT$>()""", n_params, ",") + """
        );
        return Variant::Null;
        """) + """
    }

private:
    RetT (*function_)
    (""" + gen_seq("""
        ParamT$""", n_params, ",") + """
    );
};

"""

content += """

} // namespace xm

#endif /* XM_FUNCTIONIMPL_HPP */"""
