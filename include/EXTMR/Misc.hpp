/* 
 * File:   Misc.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 23, 2013, 13.19
 */

#ifndef EXTMR_MISC_HPP
#define	EXTMR_MISC_HPP

namespace extmr{

class Type;

/**
 * Actually an empty class useful for unused template parameters.
 */
struct Empty
{
    Empty(){};
    
    /// Every type can be converted to an Empty.
    template<typename T>
    Empty(T param){};
};

/**
 * Remove namespace qualifiers from a string representing a member name.
 * e.g. "Class::member" becomes "member".
 * 
 * @param name the unformatted name.
 * @return the formatted name.
 */
std::string getNonQualifiedName(const std::string& name);

/**
 * Set the passed parameters to the numerical limits of the type T.
 * If T is a floating point value min is set to be - max.
 * If T is not a numerical type both value are set to zero.
 * 
 * @param min The variable to set at the minimum value.
 * @param max The variable to set at the maximum value.
 */
template<typename T>
void getTypeBounds(typename ToNumerical<T>::Type& min,
        typename ToNumerical<T>::Type& max)
{
    typedef typename ToNumerical<T>::Type NumT;
    
    if (std::numeric_limits<T>::is_specialized)
    {
        max = std::numeric_limits<NumT>::max();
        if(std::numeric_limits<T>::is_integer)
            min = std::numeric_limits<NumT>::min();
        else
            min = -max;
    }
    else min = max = 0;
}

/**
 * This function returns a function pointer to the callback function
 * to call on type registration. This function is used to retrieve the call
 * back function on the TypeRegister singleton instantiation.
 * 
 * @return The callback function
 */
void (*getRegCallBack())(const Type&);

} // namespace extmr

#endif	/* EXTMR_MISC_HPP */

