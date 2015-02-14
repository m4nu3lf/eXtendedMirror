content = """

#ifndef XM_PARAMLISTS_HPP
#define XM_PARAMLISTS_HPP

#define _XM_FUNCTION_CONSTRUCTOR_PARAMS \\""" + gen_seq("""
const Type& paramType$ = getType<void>()""",
XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_FUNCTION_CALL_PARAMS \\""" + gen_seq("""
const Variant& arg$ = Variant::Null""", XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_FUNCTION_CALLIMPL_PARAMS \\""" + gen_seq("""
Variant& arg$""", XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_METHOD_CONSTRUCTOR_PARAMS \\""" + gen_seq("""
const Type& paramType$ = getType<void>()""", XM_FUNCTION_PARAM_MAX - 1, ", \\") + """

#define _XM_METHOD_CALL_PARAMS \\""" + gen_seq("""
const Variant& arg$ = Variant::Null""",
XM_FUNCTION_PARAM_MAX - 1, ", \\") + """


#endif /*XM_PARAMLISTS_HPP*/

"""