cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("eXtendedMirror")

# Generate source files from python scripts
if (FUNC_PARAM_MAX)
	set(gen_options "--function-param-max" ${FUNC_PARAM_MAX})
endif()
if (GET_N_SET_EXTR_PARAM_MAX)
	set(gen_options ${gen_options} "--get-n-set-extra-param-max" ${FUNC_PARAM_MAX})
endif()
if (TEMPL_PARAM_MAX)
	set(gen_options ${gen_options} "--template-param-max" ${TEMPL_PARAM_MAX})
endif()
if (TEMPL_DIR)
	set(gen_options ${gen_options} "--template-dir" ${TEMPL_DIR})
endif()
find_package(PythonInterp REQUIRED)
execute_process(COMMAND "${PYTHON_EXECUTABLE}" "gen_templ.py" ${gen_options})


# Set compilation options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warning_flags "-Wall -Wextra -Werror")
	set(std_flags "-std=c++11")
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set (debug_flags "-g")
	endif()
elseif ("{CMAKE_CXX_COMPIER_ID}" STREQUAL "MSVC")
	set(warning_flags "/W4 /WX /EHsc")
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set (debug_flags "/DEBUG")
	endif()
endif()
if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${warning_flags} ${std_flags} ${debug_flags}" 
	    CACHE STRING "Flags used by the c++ compiler for all build types." FORCE)
	set(CMAKE_C_FLAGS "${warning_flags} ${debug_flags}"
	    CACHE STRING "Flags used by the c compiler for all build types." FORCE)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include") 


add_subdirectory("src/XM" "build/${CMAKE_BUILD_TYPE}")

# Testing
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
enable_testing()
add_test(all "build/${CMAKE_BUILD_TYPE}/test/tests")

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")
