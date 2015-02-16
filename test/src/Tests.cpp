#include <gtest/gtest.h>
#include <MyButton.hpp>

TEST(DummyGUITest, GetType)
{
    const xm::Type& type = xm::getType<MyButton>();
	ASSERT_STREQ(type.getName().c_str(), "::MyButton");
}

int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
