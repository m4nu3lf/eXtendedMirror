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
const Type& TypeRegister::registerType()
{
    typedef typename RemoveReference<T>::Type NonRefT;
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type NonQualifiedT;
    
    // call the actual registration method with the unqualified type
    return registerNonQualifiedType<NonQualifiedT>();
}


template<typename T>
const Class& TypeRegister::registerClass()
{
    return dynamic_cast<const Class&>(registerType<T>());
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
    
    if (IsDestructible<T>::value)
        destructor = new extmr::DestructorWrapper<T>;

    if (IsAssignable<T>::value)
        assignOperator = new extmr::AssignOperatorWrapper<T>;
    
    switch(category)
    {
        case Type::Primitive:
            type = new PrimitiveType(name, sizeof(T), typeid(T), constructor, 
                    copyConstructor, destructor, assignOperator);
            break;
            
        case Type::Pointer:
        {
            const Type& pointedType =
                                registerType<typename RemovePointer<T>::Type>();
            
            type = new PointerType(name, sizeof(T), typeid(T), constructor, 
                    copyConstructor, destructor, assignOperator, pointedType);
            break;
        }
            
        case Type::Array:
        {
            std::size_t arraySize = ArraySize<T>::size;
            const Type& elementType =
                                registerType<typename RemoveExtent<T>::Type>();
            
            type = new ArrayType(name, sizeof(T), typeid(T), constructor, 
                    copyConstructor, destructor, assignOperator, arraySize,
                    elementType);
            break;
        }
            
        case Type::Class:
            type = new Class(name, sizeof(T), typeid(T), constructor, 
                    copyConstructor, destructor, assignOperator);
            break;
            
        case Type::CompoundClass:
        {
            ConstTypeVector templateArgs;
            const Type* tmpType;

            tmpType = &registerType<typename TemplateRecognizer<T>::T1>();
            templateArgs.push_back(tmpType);
            
            if (TemplateRecognizer<T>::argN > 1)
            {
                tmpType = &registerType<typename TemplateRecognizer<T>::T2>();
                templateArgs.push_back(tmpType);
                
                if (TemplateRecognizer<T>::argN > 2)
                {
                    tmpType =
                            &registerType<typename TemplateRecognizer<T>::T3>();
                    templateArgs.push_back(tmpType);
                    
                    if (TemplateRecognizer<T>::argN > 3)
                    {
                        tmpType =
                            &registerType<typename TemplateRecognizer<T>::T4>();
                        templateArgs.push_back(tmpType);
                    }
                }
            }

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
            type = new CompoundClass(name, sizeof(T), typeid(T), constructor, 
                    copyConstructor, destructor, assignOperator, *tempjate,
                    templateArgs);
            break;
        }
    }
    
    if (category & Type::Class)
    {   
        Class* clazz = dynamic_cast<Class*>(type);
        
        // call the ClassBuilder of this class to build the class info
        ClassBuilder<T> classBuilder;
        classBuilder(*clazz);
        
        // push the class object into the class sets
        classesById_.insert(clazz);
        classesByName_.insert(clazz);
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
inline const Type& TypeRegister::registerType<void>()
{
    return getType<void>();
}


} // namespca extmr

#endif // EXTMR_TYPEREGISTER_INL
