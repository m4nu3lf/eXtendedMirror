/******************************************************************************      
 *      Extended Mirror: Namespace.hpp                                        *
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


#ifndef XM_NAMESPACE_HPP
#define	XM_NAMESPACE_HPP

namespace xm {

typedef std::set<Item*, ::PtrCmpByVal<Item> > Item_Set;
typedef std::set<const Item*, ::PtrCmpByVal<Item> > Const_Item_Set;
typedef void (*ItemInspector)(const Item& item);


class Namespace : public virtual Item
{
public:
    const Namespace& getNamespace(const std::string& name = "") const;
    
    template<typename T = Item>
    const T& getItem(const std::string& name) const;

    template<typename T = Item>
    const T& getItem(const T& keyItem) const;

    template<typename T = Item>
    const T& getItem(const std::string& path, const T& keyItem) const;
    
    void walkItems(ItemInspector fnc, bool recursive = false) const;
    
    Namespace& defineNamespace(const std::string& path);

    void addItem(Item& item);
    
    virtual ~Namespace();
    
protected:
    Namespace(const std::string& name, const Namespace& name_space);

    Namespace(const std::string& name = "");
    
    template<typename T = Item>
    T& getItem_(const std::string& name);

    template<typename T = Item>
    T& getItem_(const T& keyItem);

    template<typename T = Item>
    T& getItem_(const std::string& path, const T& keyItem);

    virtual Namespace& walkTo(const std::string& path, bool create = false);
    
    static bool addNamespace_(Namespace& where, const std::string& what);
    
    Const_Item_Set items_;
    Const_Item_Set ownItems_;
};


} // namespace xm

#endif	/* XM_NAMESPACE_HPP */

