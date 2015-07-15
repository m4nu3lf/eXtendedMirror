#include <gtest/gtest.h>
#include <MyButton.hpp>

TEST(Register, GetType)
{
    const xm::Type& type = xm::getType<MyButton>();
    ASSERT_STREQ("::MyButton", type.getName().c_str());
}


TEST(Register, GetClass)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    ASSERT_STREQ("::MyButton", clazz.getName().c_str());
}


TEST(Register, GetConstant)
{
    const xm::Constant& const_ = xm::getConstant("::Button::A_Const");
    ASSERT_STREQ("::Button::A_Const", const_.getName().c_str());
    ASSERT_EQ(::Button::A_Const, static_cast<const int&>(const_.getValue()));
}


TEST(Register, GetFunction)
{
    const xm::Function& func = xm::getFunction("::dgui_factories::makeButton");
    ASSERT_STREQ("::dgui_factories::makeButton", func.getName().c_str());
}


TEST(Register, GetNamespace)
{
    const xm::Namespace& ns = xm::getNamespace("::dgui_factories");
    ASSERT_STREQ("::dgui_factories", ns.getName().c_str());
}


TEST(Class, GetProperty)
{
    const xm::Class& clazz = xm::getClass<Control>();
    const xm::Property& property = clazz.getProperty("name");
    ASSERT_STREQ("::Control::name", property.getName().c_str());
}


TEST(Class, GetBaseProperty)
{
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("name");
    ASSERT_STREQ("::Control::name", property.getName().c_str());
}


TEST(Class, GetMethod)
{
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& method = clazz.getMethod("onMouseClick");
    ASSERT_STREQ("::Control::onMouseClick", method.getName().c_str());
}


TEST(Class, GetBaseMethod)
{
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& method1 = clazz.getMethod("Control::onMouseClick");
    ASSERT_STREQ("::Control::onMouseClick", method1.getName().c_str());
    const xm::Method& method2 = clazz.getMethod("Button::onMouseClick");
    ASSERT_STREQ("::Control::onMouseClick", method2.getName().c_str());
}


TEST(Class, GetOverloadedMethod)
{
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& signature = xm::Method("onMouseClick",
                                             xm::getType<void>(),
                                             clazz,
                                             xm::getType<int>(),
                                             xm::getType<int>());
    const xm::Method& method = clazz.getMethod(signature);
    ASSERT_STREQ("int", method.getParameters()[1]->type.getName().c_str());
}


TEST(PropertyField, GetData)
{
    Button* button = new MyButton();
    button->name = new char[100];
    strcpy(button->name, "buttonname");
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("name");
    ASSERT_STREQ("buttonname", property.getData(xm::ref(*button)).as<char*>());
    delete button->name;
    delete button;
}


TEST(PropertyField, SetData)
{
    Button* button = new MyButton();
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("name");
    char* name = new char[100];
    strcpy(name, "buttonname");
    property.setData(xm::ref(*button), name);
    ASSERT_STREQ("buttonname", button->name);
    delete name;
    delete button;
}


TEST(PropertyGetNSet, GetData)
{
    Button* button = new MyButton(10, 20, 30, 40);
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("width");
    ASSERT_EQ(30, property.getData(xm::ref(*button)).as<int>());
    delete button;
}


TEST(PropertyGetNSet, SetData)
{
    Button* button = new MyButton();
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("width");
    property.setData(xm::ref(*button), 10);
    ASSERT_EQ(10, button->getWidth());
    delete button;
}


TEST(PropertyArrayField, GetData)
{
    Button* button = new MyButton();
    const xm::Class& clazz = xm::getClass<MyButton>();
    const xm::Property& property = clazz.getProperty("children");
    ASSERT_EQ(button->children,
              property.getData(xm::ref(*button)).as<Control**>());
    delete button;
}


TEST(Function, Call)
{
    const xm::Function& func = xm::getFunction("::dgui_factories::makeButton");
    Button* button = func.call(10, 20, 30, 40).as<Button*>();
    ASSERT_EQ(button->getWidth(), 30);
    delete button;
}


TEST(Method, Call_Void)
{
    MyButton* button = new MyButton();
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& signature = xm::Method("onMouseClick",
                                             xm::getType<void>(),
                                             clazz,
                                             xm::getType<int>(),
                                             xm::getType<int>());
    const xm::Method& method = clazz.getMethod(signature);
    method.call(xm::ref(*button), 10, 20);
    ASSERT_EQ(static_cast<unsigned int>(1), button->getClickCount());
    ASSERT_EQ(10, button->getClickX());
    delete button;
}


TEST(Method, Call)
{
    MyButton* button = new MyButton();
    const xm::Class&  clazz = xm::getClass<MyButton>();
    button->onMouseClick();
    const xm::Method& method = clazz.getMethod("getClickCount");
    unsigned int clicks = method.call(xm::ref(*button));
    ASSERT_EQ(clicks, button->getClickCount());
    delete button;
}


TEST(Method, CallV_Void)
{
    MyButton* button = new MyButton();
    const xm::Class&  clazz = xm::getClass<MyButton>();
    const xm::Method& signature = xm::Method("onMouseClick",
                                             xm::getType<void>(),
                                             clazz,
                                             xm::getType<int>(),
                                             xm::getType<int>());
    const xm::Method& method = clazz.getMethod(signature);
    std::vector<xm::Variant> argV;
    argV.push_back(xm::ref(*button));
    argV.push_back(10);
    argV.push_back(20);
    method.callV(argV);
    ASSERT_EQ(static_cast<unsigned int>(1), button->getClickCount());
    ASSERT_EQ(10, button->getClickX());
    delete button;
}


TEST(Variant, Call_Void)
{
    MyButton* button = new MyButton();
    xm::Variant var = xm::ref(*button);
    var.call("onMouseClick");
    ASSERT_EQ(static_cast<unsigned int>(1), button->getClickCount());
    delete button;
}


TEST(Variant, CallV)
{
    MyButton* button = new MyButton();
    button->onMouseClick();
    xm::Variant var = xm::ref(*button);
    std::vector<xm::Variant> argV;
    unsigned int clicks = var.callV("getClickCount", argV).as<unsigned int>();
    ASSERT_EQ(clicks, button->getClickCount());
    delete button;
}


int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
