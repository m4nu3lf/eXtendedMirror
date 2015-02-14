content = """

#include <XM/ExtendedMirror.hpp>

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