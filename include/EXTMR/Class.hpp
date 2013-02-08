/* 
 * File:   Class.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 29 dicembre 2012, 11.09
 */

#ifndef EXTMR_CLASS_HPP
#define	EXTMR_CLASS_HPP

namespace extmr
{

class Class : public Type
{
public:
    
    /**
     * Basic constructor for initialization.
     * 
     * @param name The type name.
     */
    Class(const std::string& name = "");
    
    /**
     * Basic constructor for initialization.
     * 
     * @param cppType The type_info struct of the type.
     */
    Class(const std::type_info& type);
    
    /**
     * Get the template descriptor of the template this class is an instance of.
     * A NULL reference is returned if this class is not a template instance.
     * 
     * @return The template descriptor.
     */
    const Template& getTemplate() const;
    
    /**
     * Get a vector containing the type descriptors of the type arguments of the template.
     * If this class is not a template instance, an empty vector will be returned.
     * 
     * @return The type descriptors vector.
     */
    const std::vector<const Type*>& getTemplateParamTypes() const;
    
     /**
     * Retrieve all the base class descriptors.
     * 
     * @return A set containig the pointers to the base classes type objects.
     */
    const std::set<const Class*, Class::PtrCmpById>& getBaseClasses() const;
    
    /**
     * Retrieve all the derived class descriptors.
     * 
     * @return A set containig the pointers to the derived classes type objects.
     */
    const std::set<const Class*, Class::PtrCmpById>& getDerivedClasses() const;
    
    /**
     * Retrieve all the property descriptors of this class. Note that the properties inherited
     * form the base classes are not included.
     * 
     * @param inherited Whether to include inherited properties.
     * @return A set containig the pointers to the class property objects.
     */
    const std::set<const Property*, Property::PtrCmp>& getProperties(bool inherited = true) const;
    
    /**
     * Retrieve all the method descpritors of this class. Note that the methods inherited
     * form the base classes are not included.
     * 
     * @param inherited Whether to include inherited methods.
     * @return A set containig the pointers to the class method objects.
     */
    const std::set<const Method*, Method::PtrCmp>& getMethods(bool inherited = true) const;
    
    /**
     * Check whether or not the class has a property with the given name.
     * 
     * @param propertyName The name of the property.
     * @param inherited Whether to search through inherited properties too.
     * @return true if the class has the property, false otherwise.
     */
    bool hasProperty(const std::string& propertyName, bool inherited = true) const;
    
    /**
     * Check whether or not the class has a method with the given name.
     * 
     * @param methodName The name of the method.
     * @param inherited Whether to search through inherited methods too.
     * @return true if the class has the method, false otherwise.
     */
    bool hasMethod(const std::string& methodName, bool inherited = true) const;
    
    /**
     * Check whether or not the class has a method with the given signature.
     * 
     * @param method The Method.
     * @param inherited Whether to search through inherited methods too.
     * @return true if the class has the method, false otherwise.
     */
    bool hasMethod(const Method& method, bool inherited = true) const;
    
    /**
     * Check whether or not the class derives from a class with the given name.
     * 
     * @param baseClassName The name of the class.
     * @return true if the class derives from the given one, flase otherwise.
     */
    bool derivesFrom(const std::string& baseClassName) const;
    
    /**
     * Check whetehr or not the class derives from a given class.
     * 
     * @param baseClass The type of the derived class
     * @return true if the class derives from the given one, flase otherwise. 
     */
    bool derivesFrom(const Class& baseClass) const;
    
    /**
     * Get the Property with the given property name.
     * To see if there is a property with that name call first the HasProperty() method.
     * 
     * @param propertyName The name of the property.
     * @return The Property with that name.
     */
    const Property& getProperty(const std::string& propertyName) const;
    
    /**
     * Get the Method of the method with the given name.
     * To see if there is a method with that name call first the hasMethod() method.
     * If there are more than one overloaded methods registered with the same name
     * the first one according with the sorting rules will be returnd.
     * To have more control over the overloaded methods use getMethod with the whole signature
     * information.
     * 
     * @param methodName The name of the method.
     * @return The Method of the method with this name.
     */
    const Method& getMethod(const std::string& methodName) const;
    
    /**
     * Get the Method of the method with the given signature.
     * To see if there is a method with that name call first the hasMethod() method.
     * 
     * @param method The Method with the signature you want to retrieve.
     * 
     * @return The Method of the method with the specified signature.
     */
    const Method& getMethod(const Method& method) const;
    
    /**
     * Virtual destructor
     */
    virtual ~Class();
    
    /**
     * This function object is used to compare two pointers to this class by the name of the pointed objects.
     */
    typedef ::PtrCmpByName<Class> PtrCmpByName;
    
protected:
    
    /**
     * Constructor for full initialization.
     * 
     * @param name The class name.
     * @param size The class size.
     * @param cppType The type_info struct of the class.
     * @param constructor The class constructor wrapper function.
     * @param destructor The class destructor wrapper function.
     * @param operatorAssign The class assign operator wrapper function.
     * @param typeArgs The type descpriptors of the type arguments.
     */
    Class
    (
            const std::string& name,
            uint size,
            const std::type_info& cppType,
            void* (*constructor)(const void*),
            void (*destructor)(void*),
            void (*operatorAssign)(void*, const void*),
            const Template& templateInfo = *reinterpret_cast<Template*>(NULL),
            const std::vector<const Type*>& templateArgs = std::vector<const Type*>()
     );
    
    /**
     * Add a base class to this one.
     * 
     * @param type The base Class.
     * @return This class.
     */
    Class& operator << (Class& baseClass);
    
    /**
     * Add a property to this class.
     * 
     * @param property The Property.
     * @return This class.
     */
    Class& operator << (Property& property);
    
    /**
     * Add a method to this class.
     * 
     * @param method The Method.
     * @return This class.
     */
    Class& operator <<(Method& method);
    
    /// The template descriptor of the template this class is an instance of.
    const Template* tempjate;
    
    /// The type descriptors of the template arguments.
    std::vector<const Type*> templateParamTypes;
    
    /// The types object of the base classes sorted by the type_info struct order.
    std::set<const Class*, Class::PtrCmpById> baseClasses;

    /// The types object of the derived classes sorted by the type_info struct order.
    std::set<const Class*, Class::PtrCmpById> derivedClasses;

    /// The properties of this class.
    std::set<const Property*, Property::PtrCmp> properties;
    
    /// The properties of this class except those inherited from base classes.
    std::set<const Property*, Property::PtrCmp> ownProperties;
    
    /// The methods of this class.
    std::set<const Method*, Method::PtrCmp> methods;
    
    /// The methods of this class except those inherited form base classes.
    std::set<const Method*, Method::PtrCmp> ownMethods;
    
    /// PtrCmpByName must be a friend of this class to access the name attribute.
    friend class ::PtrCmpByName<Class>;
    
    /// The type register is the factory for the Class class and need to access the private constructor.
    friend class TypeRegister;
    
    /// The Autoregister need to call the addBaseClass(), addProperty() and addMethod() methods.
    template<class T>
    friend class ClassBuilder;
};

} // namespace extmr
#endif	/* EXTMR_CLASS_HPP */

