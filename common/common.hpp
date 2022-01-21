#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#ifndef SIGN_BITS
#define SIGN_BITS 1
#endif
#ifndef INT_BITS
#define INT_BITS  3
#endif
#ifndef FRAC_BITS
#define FRAC_BITS 12
#endif
#if (SIGN_BITS + INT_BITS + FRAC_BITS > 32)
#error "SIGN_BITS + INT_BITS + FRAC_BITS > 32"
#endif

using FP = FixedPointNumber<INT_BITS, FRAC_BITS>;

#endif