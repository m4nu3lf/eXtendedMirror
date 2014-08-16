/******************************************************************************      
 *      Extended Mirror: Item.hpp                                             *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
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


#ifndef XM_ITEM_HPP
#define	XM_ITEM_HPP

namespace xm {

class Namespace;

class Item
{
public:
    Item(const Namespace& name_space, const std::string& unqualifiedName = "");
    
    Item(const std::string& name = "");
    
    /**
     * Get the unqualified name of the item.
     * 
     * @return The unqualified name of the item.
     */
    const std::string& getUnqualifiedName() const;
    
    /**
     * Get the unqualified name of the item.
     * 
     * @return The qualified name.
     */
    std::string getName() const;
    
    /**
     * Get the namespace of the item.
     * 
     * @return The namespace.
     */
    const Namespace& getNamespace() const;
    
    virtual ~Item();
    
protected:
    static std::string removeQualifier_(const std::string& name);
    
    std::string unqualifiedName_;
    
    const Namespace* namespace_;
    
    friend bool operator<(const Item& n1, const Item& n2);
    
    friend bool operator==(const Item& n1, const Item& n2);
    
    friend bool operator!=(const Item& n1, const Item& n2);
    
    friend class Namespace;
};


bool inline operator<(const Item& i1, const Item& i2)
{
    return i1.getName() < i2.getName();
}


bool inline operator==(const Item& i1, const Item& i2)
{
    return i1.getName() == i2.getName();
}


bool inline operator!=(const Item& i1, const Item& i2)
{
    return i1.getName() != i2.getName();
}


} // namespace xm

#endif	/* XM_ITEM_HPP */

