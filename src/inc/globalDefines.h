/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Global hash define literal replacements
 *
 * This holds general purpose hash defined constants and literals.
 *
 * @todo TODO Some investigation as to whether it is best to use consts or defines is required
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_GLOBALDEFINES_H_SEEN
#define FILE_GLOBALDEFINES_H_SEEN


/* TODO perhaps configure various ports and pins etc to have names such that the
 * code can stay untouched when being ported and just the header changed to suit?
 * definitely a good idea, but we'll see what karsten says before putting time
 * into it. something like : #define RPM_IN_MAIN IC0 etc etc
 */


/* Definitions for functions used across the project TODO these are unused! */
/* http://www.seattlerobotics.org/encoder/200109/encoder.htm section Assembly */
#define INLINE_ASSEMBLY(code) __asm__ __volatile__ (code)
#define ALWAYS_INLINE __attribute__((always_inline))

/* Common macro definitions across the project */
/* Booleans from http://c2.com/cgi/wiki?CeePreprocessorStatements */
#define FALSE (0!=0) // Note, this evaluates to 0 on this platform
#define TRUE  !FALSE // Note, this evaluates to 1 on this platform

/* 8 bit values */
#define ZEROS 0x00
#define ONES  0xFF

/* 16 bit values */
#define ZEROS16 0x0000
#define ONES16  0xFFFF

/* Halves and Maxes */
#define LONGHALF  0x80000000UL /* 2147483648 */ // Ned IS awesome! ;-)
#define LONGMAX   0xFFFFFFFFUL /* 4294967295 */
#define SHORT4TH  0x4000       /* 16384 */
#define SHORTHALF 0x8000       /* 32768 */
#define SHORTMAX  0xFFFF       /* 65535 */

/* Individual bits WARNING, do not not these for notted versions, use the notted ones below instead : http://supp.iar.com/Support/?note=12582&from=search+result */
#define BIT0        0x01      /*  1st bit =     1 */
#define BIT1        0x02      /*  2nd bit =     2 */
#define BIT2        0x04      /*  3rd bit =     4 */
#define BIT3        0x08      /*  4th bit =     8 */
#define BIT4        0x10      /*  5th bit =    16 */
#define BIT5        0x20      /*  6th bit =    32 */
#define BIT6        0x40      /*  7th bit =    64 */
#define BIT7        0x80      /*  8th bit =   128 */

#define BIT0_16     0x0001    /*  1st bit =     1 */
#define BIT1_16     0x0002    /*  2nd bit =     2 */
#define BIT2_16     0x0004    /*  3rd bit =     4 */
#define BIT3_16     0x0008    /*  4th bit =     8 */
#define BIT4_16     0x0010    /*  5th bit =    16 */
#define BIT5_16     0x0020    /*  6th bit =    32 */
#define BIT6_16     0x0040    /*  7th bit =    64 */
#define BIT7_16     0x0080    /*  8th bit =   128 */

#define BIT8_16     0x0100    /*  9th bit =   256 */
#define BIT9_16     0x0200    /* 10th bit =   512 */
#define BIT10_16    0x0400    /* 11th bit =  1024 */
#define BIT11_16    0x0800    /* 12th bit =  2048 */
#define BIT12_16    0x1000    /* 13th bit =  4096 */
#define BIT13_16    0x2000    /* 14th bit =  8192 */
#define BIT14_16    0x4000    /* 15th bit = 16384 */
#define BIT15_16    0x8000    /* 16th bit = 32768 */

/* Individual bits NOTTED : http://supp.iar.com/Support/?note=12582&from=search+result */
#define NBIT0       0xFE      /*  1st bit =     1 */
#define NBIT1       0xFD      /*  2nd bit =     2 */
#define NBIT2       0xFB      /*  3rd bit =     4 */
#define NBIT3       0xF7      /*  4th bit =     8 */
#define NBIT4       0xEF      /*  5th bit =    16 */
#define NBIT5       0xDF      /*  6th bit =    32 */
#define NBIT6       0xBF      /*  7th bit =    64 */
#define NBIT7       0x7F      /*  8th bit =   128 */

#define NBIT0_16    0xFFFE    /*  1st bit =     1 */
#define NBIT1_16    0xFFFD    /*  2nd bit =     2 */
#define NBIT2_16    0xFFFB    /*  3rd bit =     4 */
#define NBIT3_16    0xFFF7    /*  4th bit =     8 */
#define NBIT4_16    0xFFEF    /*  5th bit =    16 */
#define NBIT5_16    0xFFDF    /*  6th bit =    32 */
#define NBIT6_16    0xFFBF    /*  7th bit =    64 */
#define NBIT7_16    0xFF7F    /*  8th bit =   128 */

#define NBIT8_16    0xFEFF    /*  9th bit =   256 */
#define NBIT9_16    0xFDFF    /* 10th bit =   512 */
#define NBIT10_16   0xFBFF    /* 11th bit =  1024 */
#define NBIT11_16   0xF7FF    /* 12th bit =  2048 */
#define NBIT12_16   0xEFFF    /* 13th bit =  4096 */
#define NBIT13_16   0xDFFF    /* 14th bit =  8192 */
#define NBIT14_16   0xBFFF    /* 15th bit = 16384 */
#define NBIT15_16   0x7FFF    /* 16th bit = 32768 */


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file GLOBALDEFINES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
