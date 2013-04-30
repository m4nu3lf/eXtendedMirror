/* 
 * File:   Class.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on December 26, 2012, 11.09
 */

#ifndef EXTMR_CLASS_HPP
#define	EXTMR_CLASS_HPP

#include "Template.hpp"


namespace extmr
{

class Class;
    
typedef std::set<const Class*, PtrCmpByVal<Type> > ConstClassSetById;
typedef std::set<Class*, PtrCmpByVal<Type> > ClassSetById;
typedef std::set<const Class*, PtrCmpByName<Type> > ConstClassSetByName;
typedef std::set<Class*, PtrCmpByName<Type> > ClassSetByName;
    
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
     * Get a vector containing the Type objects of the type arguments of the
     * template.
     * If this class is not a template instance, an empty vector will be
     * returned.
     * 
     * @return The type descriptors vector.
     */
    const ConstTypeVector& getTemplateArgs() const;
    
     /**
     * Retrieve all the base class descriptors.
     * 
     * @return A set containing the pointers to the base Classes.
     */
    const ConstClassSetById& getBaseClasses() const;
    
    /**
     * Retrieve all the derived class descriptors.
     * 
     * @return A set containing the pointers to the derived Classes.
     */
    const ConstClassSetById& getDerivedClasses() const;
    
    /**
     * Retrieve all the property descriptors of this class. Note that the
     * properties inherited form the base classes are not included.
     * 
     * @param inherited Whether to include inherited properties.
     * @return A set containing the pointers to the class property objects.
     */
    const ConstPropertySet& getProperties(bool inherited = true) const;
    
    /**
     * Retrieve all the Methods of this class.
     * 
     * @param inherited Whether to include inherited methods.
     * @return A set containing the pointers to the class method objects.
     */
    const ConstMethodSet& getMethods(bool inherited = true) const;
    
    /**
     * Check whether or not the class has a Property with the given name.
     * 
     * @param propertyName The name of the Property.
     * @param inherited Whether to search through inherited properties too.
     * @return true if the class has the property, false otherwise.
     */
    bool hasProperty(const std::string& propertyName, bool inherited = true)
    const;
    
    /**
     * Check whether or not the class has a Method with the given name.
     * 
     * @param methodName The name of the method.
     * @param inherited Whether to search through inherited methods too.
     * @return true if the class has the method, false otherwise.
     */
    bool hasMethod(const std::string& methodName, bool inherited = true) const;
    
    /**
     * Check whether or not the class has a Method with the given signature.
     * 
     * @param method The Method with the given signature.
     * @param inherited Whether to search through inherited methods too.
     * @return true if the class has the method, false otherwise.
     */
    bool hasMethod(const Method& method, bool inherited = true) const;
    
    /**
     * Check whether or not the class inherits from a class with the given name.
     * 
     * @param baseClassName The name of the class.
     * @return true if the class derives from the given one, false otherwise.
     */
    bool inheritsFrom(const std::string& baseClassName) const;
    
    /**
     * Check whether or not the class derives from a given class.
     * 
     * @param baseClass The type of the derived class
     * @return true if the class derives from the given one, false otherwise. 
     */
    bool inheritsFrom(const Class& baseClass) const;
    
    /**
     * Get the Property with the given property name.
     * 
     * To see if there is a property with that name call first the hasProperty()
     * method.
     * 
     * @param propertyName The name of the property.
     * @return The Property with that name.
     */
    const Property& getProperty(const std::string& propertyName) const;
    
    /**
     * Get the Method of the method with the given name.
     * 
     * To see if there is a method with that name call first the hasMethod()
     * method.
     * If there are more than one overloaded methods registered with the same
     * name the first one according with the sorting rules will be returned.
     * To have more control over the overloaded methods use getMethod with the
     * whole signature information.
     * 
     * @param methodName The name of the method.
     * @return The Method of the method with this name.
     */
    const Method& getMethod(const std::string& methodName) const;
    
    /**
     * Get the Method of the method with the given signature.
     * 
     * To see if there is a method with that name call first the hasMethod()
     * method.
     * 
     * @param method The Method with the signature you want to retrieve.
     * 
     * @return The Method of the method with the specified signature.
     */
    const Method& getMethod(const Method& method) const;
    
    virtual ~Class();
    
    /**
     * Non valid Class.
     * This Class can be used where ever a reference to a non valid Class is
     * needed.
     */
    static const Class Void;
    
protected:
    
    /**
     * Constructor for full initialization.
     * 
     * @param name The class name.
     * @param size The class size.
     * @param cppType The type_info struct of the class.
     * @param constructor The class constructor wrapper function.
     * @param copyConstructor The type copy constructor wrapper function.
     * @param destructor The class destructor wrapper function.
     * @param operatorAssign The class assign operator wrapper function.
     * @param tempjate The template this class is an instance of.
     * @param templateArgs The Type of the template arguments.
     */
    Class
    (
            const std::string& name,
            uint size,
            const std::type_info& cppType,
            Constructor* constructor,
            CopyConstructor* copyConstructor,
            Destructor* destructor,
            AssignOperator* assignOperator,
            const Template& tempjate = Template::None,
            const std::vector<const Type*>& templateArgs =
                        std::vector<const Type*>()
     );
    
    /**
     * Add a base class to this one.
     * 
     * @param type The base Class.
     * @return This class.
     */
    Class& operator << (const Class& baseClass);
    
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
    
    // The template descriptor of the template this class is an instance of.
    const Template* tempjate_;
    
    // The type descriptors of the template arguments.
    ConstTypeVector templateArgs_;
    
    // The types object of the base classes sorted by the type_info structure
    // order.
    ConstClassSetById baseClasses_;

    // The types object of the derived classes sorted by the type_info structure
    // order.
    ConstClassSetById derivedClasses_;

    // The properties of this class.
    ConstPropertySet properties_;
    
    // The properties of this class except those inherited from base classes.
    ConstPropertySet ownProperties_;
    
    // The methods of this class.
    ConstMethodSet methods_;
    
    // The methods of this class except those inherited form base classes.
    ConstMethodSet ownMethods_;
    
    // The type register is the factory for the Class class and need to access
    // the private constructor.
    friend class TypeRegister;
    
    // The ClassBuilder needs to call the stream operator.
    template<class T>
    friend class ClassBuilder;
};

} // namespace extmr
#endif	/* EXTMR_CLASS_HPP */

