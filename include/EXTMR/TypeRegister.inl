#ifndef EXTMR_TYPEREGISTER_INL
#define EXTMR_TYPEREGISTER_INL

#include <EXTMR/MemberWrappers.hpp>

namespace extmr{


template<typename T>
const Type& TypeRegister::getTypeOf(const T& obj) const
{   
    return getType(typeid(obj));
}


template<typename T>
const Class& TypeRegister::getClassOf(const T& obj) const
{
    return getClass(typeid(obj));
}


template<typename T>
const Type& TypeRegister::getType() const
{   
    static const Type& type = getType(typeid(T));
    return type;
}


template<typename T>
const Class& TypeRegister::getClass() const
{   
    static const Class& clazz = getClass(typeid(T));
    return clazz;
}


template<typename T>
Type& TypeRegister::registerType()
{
    typedef typename RemoveReference<T>::Type NonRefT;
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type NonQualifiedT;
    
    // call the actual registration method with the unqualified type
    return registerNonQualifiedType<NonQualifiedT>();
}


template<typename T>
Class& TypeRegister::registerClass()
{
    if (TypeRecognizer<T>::category | Type::Class)
        return dynamic_cast<Class&>(registerType<T>());
    else
        return *reinterpret_cast<Class*>(NULL);
}


template<typename T>
Type& TypeRegister::registerNonQualifiedType()
{
    static Type* type = NULL;
    
    // check for already registered type
    if (type) return *type;
    
    // retrieve type information
    std::string name = TypeRecognizer<T>::getName();
    Type::Category category = TypeRecognizer<T>::category;
    
    // method wrappers
    Constructor* constructor = NULL;
    CopyConstructor* copyConstructor = NULL;
    Destructor* destructor = NULL;
    AssignOperator* assignOperator = NULL;
    
    
    // take the method wrappers
    if (IsInstantiable<T>::value)
        constructor = new extmr::ConstructorWrapper<T>;

    if (IsCopyable<T>::value)
        copyConstructor = new extmr::CopyConstructorWrapper<T>;
    
    if (!IsArray<T>::value)
        destructor = new extmr::DestructorWrapper<T>;

    if (IsLvalue<T>::value)
        assignOperator = new extmr::AssignOperatorWrapper<T>;
    
    if (category & Type::Class)
    {
        // template this class is an instance of if any
        Template* tempjate = NULL;
    
        // template type parameters if any
        std::vector<const Type*> templateTypeArgs;
        
        // recursively register the types this class depends on
        if(category == Type::CompoundClass)
        {
            Type& type1 = registerType<typename TemplateRecognizer<T>::T1>();
            Type& type2 = registerType<typename TemplateRecognizer<T>::T2>();
            Type& type3 = registerType<typename TemplateRecognizer<T>::T3>();
            Type& type4 = registerType<typename TemplateRecognizer<T>::T4>();

            if (&type1) templateTypeArgs.push_back(&type1);
            if (&type2) templateTypeArgs.push_back(&type2); 
            if (&type3) templateTypeArgs.push_back(&type3); 
            if (&type4) templateTypeArgs.push_back(&type4); 

            Template* tempjate = new Template(TemplateRecognizer<T>::getName(),
                    TemplateRecognizer<T>::argN);
            TemplateSet::iterator ite;
            ite = templates_.find(tempjate);
            if (ite == templates_.end())
            {
                templates_.insert(tempjate);
            }
            else
            {
                delete tempjate;
                tempjate = *ite;
            }
        }
        
        // create the class object
        Class* clazz = new Class
                    (
                            name,
                            sizeof(T),
                            typeid(T),
                            constructor,
                            copyConstructor,
                            destructor,
                            assignOperator,
                            *tempjate,
                            templateTypeArgs
                    );
        
        // store the registered type
        type = clazz;
        
        // call the ClassBuilder of this class to build the class info
        ClassBuilder<T> classBuilder;
        classBuilder(*clazz);
        
        // push the class object into the class sets
        classesById_.insert(clazz);
        classesByName_.insert(clazz);
    }
    else
    {
        // the type this type point to of the array element type
        Type* relatedType = NULL;
        
        // whether the type is an array
        bool isArray;
        
        // the array size
        std::size_t arraySize = ArraySize<T>::size;
        
        // recursively register the pointed type or the array element type
        if (category == Type::Pointer)
        {
            relatedType = &registerType<typename RemovePointer<T>::Type>();
        }
        else if (category == Type::Array)
        {
            relatedType = &registerType<typename RemoveExtent<T>::Type>();
            isArray = true;
        }
        
        // create the type object
        type = new Type
                (
                        name,
                        sizeof(T),
                        typeid(T),
                        constructor,
                        copyConstructor,
                        destructor,
                        assignOperator,
                        *relatedType,
                        isArray,
                        arraySize
                );
    }
    
    // push the type object into the type sets
    typesById_.insert(type);
    typesByName_.insert(type);
    
    // call the function registered for call back
    if (getRegCallBack())
        getRegCallBack()(*type);
    
    // return the type
    return *type;
}


/*
 * Calling the registerType with a void type has no consequences and a null type
 * reference is returned. This must be ensured because the method registration
 * mechanism call this for the returned method type and this type can be void.
 */
template<>
inline Type& TypeRegister::registerType<void>()
{
    return *reinterpret_cast<Type*>(NULL);
}


} // namespca extmr

#endif // EXTMR_TYPEREGISTER_INL
