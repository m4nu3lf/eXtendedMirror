content = """

#include <XM/ExtendedMirror.hpp>

using namespace std;
using namespace xm;

Method::Method
(
    const string& name,
    const Type& retType,
    const Class& owner,""" + gen_seq("""
    const Type& paramType$""", XM_FUNCTION_PARAM_MAX - 1, ",") + """
) :
    Item(owner, name),
    Function
    (
	name,
	retType,
	owner,""" + gen_seq("""
	paramType$""", XM_FUNCTION_PARAM_MAX - 1, ",") + """
    )
{
}
"""
