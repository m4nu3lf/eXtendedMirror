#ifndef EXTMR_TYPEEXTMR_HPP
#define EXTMR_TYPEEXTMR_HPP

namespace extmr{

/**
 * Holds all the type descriptors of the registered types and provide
 * methods to access or manipulate them. This class is meant to be singleton
 * so there is no public constructor. Instead the instance can be safely
 * retrieved through the getTypeReg method in constructors of static objects
 * or you can simply use the global variable typeReg to access the type register
 * from any other point in your program.
 */
class TypeRegister
{
public:
    /**
     * Get the Type of the type with the given name if any.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @param typeName The name of the type.
     * @return The Type.
     */
    const Type& getType(const std::string& typeName) const;
    
    /**
     * Get the Type of the type with the given type_info.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @param cppType The type_info struct of the type.
     * @return The Type.
     */
    const Type& getType(const std::type_info& cppType) const;
    
    /**
     * Get the Class of the class with the given name if any.
     * Return a NULL reference if the type is not a class,
     * or is nota registered one.
     * 
     * @param className The name of the class.
     * @return The Class.
     */
    const Class& getClass(const std::string& className) const;
    
    /**
     * Get the Class of the class with the given type_info.
     * Return a NULL reference if the type is not a class,
     * or is not a registered one.
     * 
     * @param cppType The type_info struct of the class.
     * @return The Class.
     */
    const Class& getClass(const std::type_info& cppType) const;
    
    /**
     * Get the Type of the type of the given object.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @param obj The object instance
     * @return The Type.
     */
    template<typename T>
    const Type& getTypeOf(const T& obj) const;
    
    /**
     * Get the Class of the class of the given object.
     * Return a NULL reference if the type is not a class,
     * or is not a registered one.
     * 
     * @param obj The object instance
     * @return The Class.
     */
    template<typename T>
    const Class& getClassOf(const T& obj) const;
    
    /**
     * Get the Type of the given type.
     * Return a NULL reference if the type is not a registered one.
     * 
     * @tparam T The given type.
     * @return The Type.
     */
    template<typename T>
    const Type& getType() const;
    
    /**
     * Get the Class of the given class type.
     * Return a NULL reference if the type is not a class,
     * or is not a registered one.
     * 
     * @tparam T The given type.
     * @return The Class.
     */
    template<typename T>
    const Class& getClass() const;
    
    /**
     * Get the template descriptor of the template with the given name if any.
     * Return a NULL reference if the template is not a registered one.
     * 
     * @param templateName The name of the template.
     * @return The template descriptor.
     */
    const Template& getTemplate(const std::string& templateName) const;
    
    /**
     * Get a set containing the pointers to the type descriptors of all
     * the registered types.
     * 
     * @return The Type pointer set. 
     */
    const ConstTypeSetById& getTypes();
    
    /**
     * Get a set containing the pointers to the class descriptors of all
     * the registered classes.
     * 
     * @return The Class pointer set. 
     */
    const ConstClassSetById& getClasses();
    
    /**
     * Get a set containing the pointers to the template descriptors of all
     * the registered templates.
     * 
     * @return The template descriptor pointer set. 
     */
    const std::set<const Template*, Template::PtrCmp>& getTemplates();
    
    /**
     * Start the registration mechanism for the given type. You should not call
     * this method unless you know what you are doing.
     * Registration macros will handle automatic type registration and call this method for you.
     * 
     * @return The registered type.
     */
    template<typename T> Type& registerType();
    
    /**
     * The same of registerType() except this is only valid for class types and
     * return a Class instead of a Type.
     * 
     * @return The registered type.
     */
    template<typename T> Class& registerClass();
    
    /**
     * Set a function that is called whenever a type is registered within the
     * type register and the registered type is passed to this function.
     * 
     * @param callBackFnc
     */
    void setRegCallBack(void (*callBackFnc)(const Type&));
    
    /**
     * Used to safely retrieve the type register singleton when the
     * program starts up (before the main function execution) preventing the
     * static initialization order fiasco.
     * 
     * @return The type register.
     */
    static TypeRegister& getTypeReg();
    
private:

    /**
     * Constructor.
     * 
     * @param callBackFnc A function that is called every time a Type is
     * registered.
     */
    TypeRegister(void (*callBackFnc)(const Type&));
    
    /**
     * This method is called by registerType, after the type qualifiers are
     * removed
     * from the type.
     * 
     * @return the registered type.
     */
    template<typename T> Type& registerNonQualifiedType();
    
     /**
      * Make this object non copyable.
      */
    TypeRegister(const TypeRegister&);
    TypeRegister& operator=(const TypeRegister&);

    // A set containing the pointers to all the registered type descriptors
    //sorted by type name.
    TypeSetByName typesByName_;
    
    // A set containing the pointers to all the registered type descriptors
    //sorted by type_info struct order.
    TypeSetById typesById_;
    
    // A set containing the pointers to all the registered class descriptors
    // sorted by type name.
    ClassSetByName classesByName_;
    
    // A set containing the pointers to all the registered class descriptors
    // sorted by type_info struct order.
    ClassSetById classesById_;
    
    // A set containing the template descriptors of all the instantiated
    //templates.
    std::set<Template*, Template::PtrCmp> templates_;
    
    // The call back function to call whenever a type is registered.
    void (*callBackFnc_) (const Type&);
};

} // namespace extmr

#endif // TYPEEXTMR_HPP
