content = """

#include <XM/Utils/Utils.hpp>
#include <XM/ExtendedMirror.hpp>

using namespace std;
using namespace xm;

Function::Function
(
    const string& name,
    const Type& retType,""" + gen_seq("""
    const Type& paramType$""", XM_FUNCTION_PARAM_MAX, ",") + """
) :
    Item(name),
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
"""
