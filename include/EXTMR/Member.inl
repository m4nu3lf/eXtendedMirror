/* 
 * File:   Member..inl
 * Author: manuele
 *
 * Created on April 15, 2014, 8:12 PM
 */

#ifndef EXTMR_MEMBER__INL
#define	EXTMR_MEMBER__INL

namespace extmr {

    
bool inline operator<(const Member& m1, const Member& m2)
{
    if (*m1.owner_ != getClass<void>() and *m2.owner_ != getClass<void>())
    {
        if (*m1.owner_ < *m2.owner_)
            return true;
        else return m1.name_ < m2.name_;
    }
    else return m1.name_ < m2.name_;
}


} // namespace extmr

#endif	/* EXTMR_MEMBER__INL */

