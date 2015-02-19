#include <gtest/gtest.h>
#include <MyButton.hpp>

TEST(GetItem, GetType)
{
    const xm::Type& type = xm::getType<MyButton>();
	ASSERT_STREQ(type.getName().c_str(), "::MyButton");
}


TEST(GetItem, GetClass)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    ASSERT_STREQ(clazz.getName().c_str(), "::MyButton");
}


TEST(GetItem, GetProperty)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("name");
    ASSERT_STREQ(property.getName().c_str(), "::Control::name");
}


int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
