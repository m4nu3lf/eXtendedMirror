set(GTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0")
include_directories("${GTEST_DIR}/include")
add_subdirectory(${GTEST_DIR} 
		"${CMAKE_CURRENT_SOURCE_DIR}/../build/${MODE_DIR}/test/gtest")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src"
		"${CMAKE_CURRENT_SOURCE_DIR}/../build/${MODE_DIR}/test")
