/******************************************************************************      
 *      Extended Mirror: Variant.hpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


/* TODO: Add a call() method that takes the name of a method and a number of
   variant args. This method should check if the variant is an object that
   have such a method and call it. This method should also check for virtuality
   (need to provide this information in Method objects) and overloads. */

#ifndef XM_VARIANT_HPP
#define	XM_VARIANT_HPP

#include<XM/ParamLists.hpp>

namespace xm{

class Type;


class Variant
{
public:
    /**
     * Some variant flags.
     */
    enum Flags
    {
        // Variant data is a reference to external data.
        Reference = 1,
        
        // Variant holds constant data
        Const = 2,
        
        // Variant get copied by ref.
        CpyByRef = 8
    };
    
    /**
     * Build a void variant.
     */
    Variant();
    
    /**
     * Construct a variant from the given object.
     * The object data is copied with its class copy constructor and the data is
     * stored internally.
     * 
     * @param data
     */
    template<typename T>
    Variant(const T& data);
    
    /**
     * Construct a variant from the given object.
     * By default the object is copied with its class copy constructor and the
     * data is stored internally.
     * If you want to change this behavior specify the second parameter.
     * 
     * @param data The object from which to take the data form.
     * @param flags The variant flags.
     */
    template<typename T>
    Variant(T& data, char flags);
    
    /**
     * Get the Type for the data.
     * 
     * @return The Type.
     */
    const Type& getType() const;
    
    /*
     * Create and return a RefVariant to the content.
     * 
     * @return The RefVariant
     */
    Variant getRefVariant() const;
    
    /**
     * Ask if this variant data is a reference to an external data.
     * 
     * @return true if the variant data is a reference, false otherwise.
     */
    bool isReference() const;
    
    /**
     * Ask if this variant holds constant data.
     * 
     * @return true if the variant holds constant data, false otherwise.
     */
    bool isConst() const;
    
    /**
     * Set the variant data to be constant, after a variant has been marked as
     * constant, the constness cannot be removed anymore.
     */
    void setConst();
    
    /**
     * Cast operator, get the data of the variant by reference.
     * This method only works if the template parameter
     * is either the same of the contained data or, given that the
     * data is an object of a class or a pointer
     * to an object of a class, then the specified type
     * is respectively a base class of the that class or a pointer to
     * a base class of that class.
     * In other words this would only work if a reinterpret_cast<> from the
     * pointer to the contained data type to a pointer of the target type would 
     * lead to a meaningful conversion.
     * In all other cases a VariantTypeException arises.
     * 
     * @return The variant data.
     */
    template<typename T>
    operator T&();
    
    /**
     * Shortcut to static_cast<T>(*this)
     * 
     * @return The variant data.
     */
    template<typename T>
    T& as();
    
    /**
     * Copy constructor. The data is copied through the copy constructor.
     * 
     * @param orig The variant to copy.
     */
    Variant(const Variant& orig);
    
    /**
     * Move constructor. The data of the variants is swapped.
     * 
     * @param orig The variant to move.
     */
    Variant(Variant&& orig);
    
    /**
     * Operator for assignment.
     * The data is copied through the type copy constructor.
     * If the data of the lvalue variant has not yet been allocated is then
     * allocated through the standard constructor.
     * It types are different, then the lvalue variant data is first
     * deallocated, and then types are set the same.
     * 
     * @param other The other variant object.
     * @return The variant
     */
    const Variant& operator=(const Variant& other);
    
    /**
     * Operator for assignment.
     * The data of the rvalue is stored into the variant after it has been
     * copied through the assignment operator of the specified type.
     * If current type of the variant is different form that of the rvalue then
     * the previous data is deallocated with the destructor and a new object of
     * the new type is allocated with its default constructor.
     * The assignment is then performed.
     * 
     * @param rvalue The rvalue object
     * @return A reference to the rvalue
     */
    template<typename T>
    const T& operator=(const T& rvalue);
    
    //TODO: add support for all others operators
    
    /**
     * Call a method, if the variant is a class instance
     * 
     * @param methodName Method name.
     * @param arg<N> The Nth Argument.
     * @return A Variant containing the return value.
     */
    Variant call
    (
        const std::string& methodName,
        _XM_METHOD_CALL_PARAMS
    );
    
    /**
     * Call a method, if the variant is a class instance
     * 
     * @param methodName Method name.
     * @param args A vector containing the arguments of the method.
     * @return A Variant containing the return value.
     */
    Variant callV(const std::string& methodName, std::vector<Variant>& args);
    
    /**
     * Destructor. The data is deallocated calling the destructor.
     */
    virtual ~Variant();
    
    static Variant Null;
    
protected:
    // Pointer the data / data
    void* data_;
    
    // Pointer to the Type of data.
    const Type* type_;
    
    // Some flags
    char flags_;
    
    /**
     * Initialize a variant.
     */
    template<typename T>
    struct Initialize
    {
        Initialize(Variant& variant);

        void operator()(T& data);

    private:
        // The variant that is being initialized
        Variant& variant_;
    };
    
};


} // namespace xm

#endif	/* XM_VARIANT_HPP */

