add_executable("tests"
	"Button.cpp"
	"Control.cpp"
	"MyButton.cpp"
	"Rectangle.cpp"
	"Shape.cpp"
	"FactoryFunctions.cpp"
	"Tests.cpp")
link_directories("${CURRENT_CMAKE_SOURCE_DIR}/../../build")
link_directories("${CURRENT_CMAKE_SOURCE_DIR}/../gtest-1.7.0")
target_link_libraries(tests "xMirror" "gtest_main" "gtest")

