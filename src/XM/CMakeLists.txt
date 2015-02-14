include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Utils") 
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Exceptions") 

add_library("xMirror" STATIC
	    "ArrayType.cpp"
	    "Class.cpp"
	    "CompoundClass.cpp"
	    "Function.cpp"
	    "Item.cpp"
	    "Member.cpp"
	    "Method.cpp"
	    "Namespace.cpp"
	    "PointerType.cpp"
	    "PrimitiveType.cpp"
	    "Property.cpp"
	    "Register.cpp"
	    "SpecialMembers.cpp"
	    "Template.cpp"
	    "Type.cpp"
	    "Variant.cpp")
target_link_libraries("xMirror" "utils" "exceptions")