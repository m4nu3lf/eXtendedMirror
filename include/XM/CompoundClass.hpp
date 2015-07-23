/******************************************************************************      
 *      Extended Mirror: CompoundClass.hpp                                    *
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


#ifndef XM_COMPOUNDCLASS_HPP
#define	XM_COMPOUNDCLASS_HPP

namespace xm {


typedef std::vector<TemplArg> TemplArg_Vector;


class CompoundClass : public Class
{
public:
    /**
     * Constructor for full initialization.
     *
     * @param name The class name.
     * @param name_space The class namespace.
     */
    CompoundClass(const std::string& name, const Namespace& name_space);

    /**
     * Get the type Category.
     * 
     * @return The type category of this type.
     */
    Category getCategory() const;
    
    /**
     * Get the template descriptor of the template this class is an instance of.
     * 
     * @return The template descriptor.
     */
    const Template& getTemplate() const;
    
    /**
     * Get a vector containing the arguments of the
     * template.
     * 
     * @return The type descriptors vector.
     */
    const TemplArg_Vector& getTemplateArgs() const;
        
private:
    /**
     * Constructor for full initialization.
     * 
     * @param name_space The class namespace.
     * @param name The class name.
     * @param size The class size.
     * @param cppType The type_info struct of the class.
     * @param constructor The class constructor wrapper function.
     * @param copyConstructor The type copy constructor wrapper function.
     * @param destructor The class destructor wrapper function.
     * @param isAbstract If the class is abstract.
     * @param tempjate The template this class is an instance of.
     * @param templateArgs The Type of the template arguments.
     */
    CompoundClass
    (
            const Namespace& name_space,
            const std::string& name,
            uint size,
            const std::type_info& cppType,
            const Constructor& constructor,
            const CopyConstructor& copyConstructor,
            const Destructor& destructor,
            bool isAbstract,
            const Template& tempjate,
            const TemplArg_Vector& templateArgs
     );
    
    // The template descriptor of the template this class is an instance of.
    const Template* tempjate_;
    
    // The the template arguments.
    TemplArg_Vector templateArgs_;
    
    // Factory function
    template<class T>
    static CompoundClass& create();
    
    // Factory class ( calls create() )
    template<typename T>
    friend struct CreateType;
};


} // namespace xm

#endif	/* XM_COMPOUNDCLASS_HPP */

