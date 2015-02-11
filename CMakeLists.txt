cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Extended Mirror")

# Generate source files from python scripts
find_package(PythonInterp)
execute_process(COMMAND "${PYTHON_EXECUTABLE}" "gen_templ.py")

# Set warnings level
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror")
	set(std "-std=c++11")
elseif ("{CMAKE_CXX_COMPIER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc")
endif()
if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${warnings} ${std}" 
	    CACHE STRING "Flags used by the c++ compiler for all build types." FORCE)
	set(CMAKE_C_FLAGS "${warnings}"
	    CACHE STRING "Flags used by the c compiler for all build types." FORCE)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include") 

add_subdirectory("src/XM" "build")

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
