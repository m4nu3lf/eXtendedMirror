##############################################################################
#      Extended Mirror: ParamLists.hpp.py                                    #
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

#ifndef XM_PARAMLISTS_HPP
#define XM_PARAMLISTS_HPP

#define _XM_FUNCTION_CONSTRUCTOR_PARAMS \\""" + gen_seq("""
const Type& paramType$ = getType<void>()""",
XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_FUNCTION_CALL_PARAMS \\""" + gen_seq("""
const Variant& arg$ = Variant::Void""", XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_FUNCTION_CALLIMPL_PARAMS \\""" + gen_seq("""
Variant& arg$""", XM_FUNCTION_PARAM_MAX, ", \\") + """

#define _XM_METHOD_CONSTRUCTOR_PARAMS \\""" + gen_seq("""
const Type& paramType$ = getType<void>()""", XM_FUNCTION_PARAM_MAX - 1, ", \\") + """

#define _XM_METHOD_CALL_PARAMS \\""" + gen_seq("""
const Variant& arg$ = Variant::Void""",
XM_FUNCTION_PARAM_MAX - 1, ", \\") + """


#endif /*XM_PARAMLISTS_HPP*/

"""
