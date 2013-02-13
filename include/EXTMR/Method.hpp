/* 
 * File:   Method.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on October 20, 2012, 21.55
 */

#ifndef EXTMR_METHOD_HPP
#define	EXTMR_METHOD_HPP

#include <EXTMR/Parameter.hpp>

namespace extmr{

// we need some forward declarations
class Type;
bool operator<(const Type&, const Type&);

/**
 * Describes a method of a class that has been registered through the reflection mechanism.
 * Note that a Method is related to the class and not to the object (instances).
 * Use this class only for set querying. Effective functionalities implementation is
 * delegated to subclasses.
 */
class Method
{
public:
    /**
     * Construct a method with no full signature, just the name.
     * 
     * @param name The method name.
     */
    Method(const std::string& name);
    
    /**
     * Construct a Method with the given given signature.
     * 
     * @param name The name of the method.
     * @param retType The Type of the returned type.
     * @param paramType1 The Type of the first parameter type.
     * @param paramType2 The Type of the second parameter type.
     * @param paramType3 The Type of the third parameter type.
     * @param paramType4 The Type of the fourth parameter type.
     * @param paramType5 The Type of the fifth parameter type.
     * @param paramType6 The Type of the sixth parameter type.
     * @param paramType7 The Type of the seventh parameter type.
     * @param paramType8 The Type of the eighth parameter type.
     */
    Method
    (
        const std::string& name,
        const Type& retType,
        const Type& paramType1 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType2 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType3 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType4 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType5 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType6 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType7 = *reinterpret_cast<Type*>(NULL),
        const Type& paramType8 = *reinterpret_cast<Type*>(NULL)
    );
    
    /**
     * Construct a Method with the given given signature.
     * 
     * @param name The name of the method.
     * @param retType The type_info struct of the returned type.
     * @param paramType1 The type_info struct of the first parameter type.
     * @param paramType2 The type_info struct of the second parameter type.
     * @param paramType3 The type_info struct of the third parameter type.
     * @param paramType4 The type_info struct of the fourth parameter type.
     * @param paramType5 The type_info struct of the fifth parameter type.
     * @param paramType6 The type_info struct of the sixth parameter type.
     * @param paramType7 The type_info struct of the seventh parameter type.
     * @param paramType8 The type_info struct of the eighth parameter type.
     */
    Method
    (
        const std::string& name,
        const std::type_info& retType,
        const std::type_info& paramType1 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType2 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType3 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType4 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType5 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType6 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType7 = *reinterpret_cast<std::type_info*>(NULL),
        const std::type_info& paramType8 = *reinterpret_cast<std::type_info*>(NULL)
    );
    
    /**
     * Get the name of the method.
     * 
     * @return The name of the method.
     */
    const std::string& getName() const;
    
    /**
     * Add an other parameter to the parameter list.
     * 
     * @param param The new parameter.
     */
    void addParameter(const Parameter& param);
    
    /**
     * Get the descriptor of the returned type of the method.
     * 
     * @return A reference to a constant Type of the method returned type.
     */
    const Type& getReturnType() const;
    
    /**
     * Ask if the methods returns by a non constant reference.
     * 
     * @return True if the method returns by a non constant reference.
     */
    virtual bool getReturnByNonConstRef() const;
    
    /**
     * Get a vector with the Parameters.
     * 
     * @return A vector containing the Parameters.
     */
    const std::vector<const Parameter*>& getParameters() const;
    
    /**
     * Ask if the method is constant.
     * 
     * @return True if the method is constant, false otherwise.
     */
    virtual bool isConst() const;
    
    /**
     * Call the method.
     * 
     * @param objPtr A pointer to an object of the class this method belongs to.
     * @param arg1 Argument 1.
     * @param arg2 Argument 2.
     * @param arg3 Argument 3.
     * @param arg4 Argument 4.
     * @param arg5 Argument 5.
     * @param arg6 Argument 6.
     * @param arg7 Argument 7.
     * @param arg8 Argument 8.
     * @return A Variant containing the return value.
     */
    virtual Variant call
    (
        const Variant& objPtr,
        const Variant& arg1 = Variant(),
        const Variant& arg2 = Variant(),
        const Variant& arg3 = Variant(),
        const Variant& arg4 = Variant(),
        const Variant& arg5 = Variant(),
        const Variant& arg6 = Variant(),
        const Variant& arg7 = Variant(),
        const Variant& arg8 = Variant()
    ) const
    {
        return Variant();
    }
    
    /** 
     * This function object is used to compare two pointers to this class by the signature information of the pointed objects.
     * If one of the comparing method has no full signature defined then is only performed a name comparison.
     */
    struct PtrCmp
    {
        bool operator()(const Method* methodPtr1, const Method* methodPtr2) const
        {
                if (methodPtr1->name < methodPtr2->name) return true;
                if (!methodPtr1->fullSignature || methodPtr2->fullSignature) return false;
                ushort paramN1 = methodPtr1->params.size();
                ushort paramN2 = methodPtr2->params.size();
                ushort paramN = std::min(paramN1, paramN2);
                for (uint i = 0; i < paramN; i++)
                {
                    if (methodPtr1->params[i]->type < methodPtr2->params[i]->type) return true;
                }
                if (paramN1 < paramN2) return true;
                return false;
        }
    };
    
protected:
    
    /// The method name.
    std::string name;
    
    /// The returned type.
    const Type* retType;
    
    /// whether the method full signature is provided (used in comparing two methods).
    bool fullSignature;
    
    /// The parameter list.
    std::vector<const Parameter*> params;
};

} // namespace extmr

#endif	/* EXTMR_METHOD_HPP */

