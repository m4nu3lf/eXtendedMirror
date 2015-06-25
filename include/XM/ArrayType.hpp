/******************************************************************************      
 *      Extended Mirror: ArrayType.hpp                                        *
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


#ifndef XM_ARRAYTYPE_HPP
#define	XM_ARRAYTYPE_HPP

namespace xm {


class ArrayType : public Type
{
public:
    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the Type of the array elements.
     * If the type is not an array then a NULL reference is returned.
     * 
     * @return The element Type.
     */
    const Type& getArrayElementType() const;
    
    /**
     * Get the size of the array.
     * If the type is not an array then 0 is returned.
     * 
     * @return The type size.
     */
    std::size_t getArraySize() const;
    
    virtual ~ArrayType();
    
private:
    
    /**
     * Constructor for full initialization.
     * 
     * @param uName The type unqualified name.
     * @param size The type size.
     * @param cppType The type_info struct of the type.
     * @param arraySize The length of the array.
     * @param elementType The type of the array elements.
     */
    ArrayType(const std::string& uName,
            std::size_t size, const std::type_info& cppType,
            std::size_t arraySize, const Type& elementType);
    
    
    // The array elements type.
    const Type* elementType_;
    
    // The size of the array.
    size_t arraySize_;
    
    // Factory class
    template<typename T>
    friend struct CreateType;
};


} // namespace xm

#endif	/* XM_ARRAYTYPE_HPP */

