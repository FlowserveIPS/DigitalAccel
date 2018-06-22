// Rowley CrossWorks, runtime support.
//
//  Copyright (c) 2001-2016 Rowley Associates Limited.
//
// This file may be distributed under the terms of the License Agreement
// provided with this software.
//
// THIS FILE IS PROVIDED AS IS WITH NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#ifndef __in430_H
#define __in430_H

#include <inmsp.h>


/*!! The header file \<in430.h\> defines a number of intrinsic functions
  of general use for the MSP430 processor. This file is written to be
  compatible, and in some cases an enhancement of, the corresponding file
  in version 2 of IAR's Embedded Workbench for MSP430 (EW430) product.
*/



/*! \brief Swap order of bytes in a word \ingroup Byte order manipulation \synopsis

  \description A synonym for \ref __swap_bytes.
*/
#define _SWPB(X) __swap_bytes(X)


/*! \brief Swap order of words in a long \ingroup Byte order manipulation \synopsis

  \description A synonym for \ref __swap_words.
*/
#define _LSWPW(X) __swap_words(X)


/*! \brief Swap order of bytes in a long \ingroup Byte order manipulation \synopsis

  \description A synonym for \ref __swap_long_bytes.
*/
#define _LSWPB(X) __swap_long_bytes(X)


/*! \brief Set bits in status register \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __bis_SR_register.
*/
#define _BIS_SR(X) __bis_SR_register(X)


/*! \brief Clear bits in status register \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __bic_SR_register.
*/
#define _BIC_SR(X) __bic_SR_register(X)


/*! \brief Set bits in stacked status register \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __bis_SR_register_on_exit.
*/
#define _BIS_SR_IRQ(X) __bis_SR_register_on_exit(X)


/*! \brief Clear bits in stacked status register \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __bic_SR_register_on_exit.
*/
#define _BIC_SR_IRQ(X) __bic_SR_register_on_exit(X)


/*! \brief Disable global interrupts \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __disable_interrupt.
*/
#define _DINT()  __disable_interrupt()


/*! \brief Enable global interrupts \ingroup Status register manipulation \synopsis

  \description A synonym for \ref __enable_interrupt.
*/
#define _EINT()  __enable_interrupt()


/*! \brief Insert a NOP instruction \ingroup Miscellaneous functions \synopsis

  \description A synonym for \ref __no_operation.
*/
#define _NOP() __no_operation()


/*! \brief Insert an opcode \ingroup Miscellaneous functions \synopsis

  \description A synonym for \ref __insert_opcode.
*/
#define _OPC(X) __insert_opcode(X)


/*! \brief Add two 16-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_add_short.
*/
#define _DADD16(X, Y) __bcd_add_short(X, Y)


/*! \brief Add two 32-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_add_long.
*/
#define _DADD32(X, Y) __bcd_add_long(X, Y)


/*! \brief Add two 64-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_add_long_long.
*/
#define _DADD64(X, Y) __bcd_add_long_long(X, Y)


/*! \brief Subtract two 16-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_subtract_short.
*/
#define _DSUB16(X, Y) __bcd_subtract_short(X, Y)


/*! \brief Subtract two 32-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_subtract_long.
*/
#define _DSUB32(X, Y) __bcd_subtract_long(X, Y)


/*! \brief Subtract two 64-bit values using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_subtract_long_long.
*/
#define _DSUB64(X, Y) __bcd_subtract_long_long(X, Y)


/*! \brief Negate a 16-bit value using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_negate_short.
*/
#define _DNEG16(X) __bcd_negate_short(X)


/*! \brief Negate a 32-bit value using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_negate_long.
*/
#define _DNEG32(X) __bcd_negate_long(X)


/*! \brief Negate a 64-bit value using decimal arithmetic \ingroup Binary coded decimal arithmetic \synopsis

  \description A synonym for \ref __bcd_negate_long_long.
*/
#define _DNEG64(X) __bcd_negate_long_long(X)


/* Private, internal functions. */
#pragma intrinsic(_H16)
unsigned _H16(unsigned long);

#pragma intrinsic(_L16)
unsigned _L16(unsigned long);

#pragma intrinsic(_H32)
unsigned long _H32(unsigned long long);

#pragma intrinsic(_L32)
unsigned long _L32(unsigned long long);

#pragma intrinsic(_HH16)
unsigned _HH16(unsigned long long);

#pragma intrinsic(_LL16)
unsigned _LL16(unsigned long long);

#define __even_in_range(X, R) (X)

#endif
