#include <gtest/gtest.h>
#include <MyButton.hpp>

TEST(GetItem, GetType)
{
    const xm::Type& type = xm::getType<MyButton>();
    ASSERT_STREQ("::MyButton", type.getName().c_str());
}


TEST(GetItem, GetClass)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    ASSERT_STREQ("::MyButton", clazz.getName().c_str());
}


TEST(GetItem, GetProperty)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("name");
    ASSERT_STREQ("::Control::name", property.getName().c_str());
}


TEST(GetItem, GetMethod)
{
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& method = clazz.getMethod("onMouseClick");
    ASSERT_STREQ("::Control::onMouseClick", method.getName().c_str());
}


TEST(GetItem, GetFunction)
{
    const xm::Function& func = xm::getFunction("::dgui_factories::makeButton");
    ASSERT_STREQ("::dgui_factories::makeButton", func.getName().c_str());
}


TEST(GetItem, GetNamespace)
{
    const xm::Namespace& ns = xm::getNamespace("::dgui_factories");
    ASSERT_STREQ("::dgui_factories", ns.getName().c_str());
}


int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
