/****************************************************************************
 * @file     core_cmFunc.h
 * @brief    CMSIS Cortex-M Core Function Access Header File
 * @version  V3.01
 * @date     06. March 2012
 *
 * Copyright (C) 2009-2012 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#ifndef __CORE_CMFUNC_H
#  define __CORE_CMFUNC_H

/* ######################  Core Function Access  ########################### */
/* Enable IRQ Interrupts

  This function enables IRQ interrupts by clearing the I-bit in the CPSR.
  Can only be executed in Privileged modes.
 */
__attribute__ ((always_inline))
static inline void __enable_irq(void)
{
  __ASM volatile ("cpsie i");
}

/* Disable IRQ Interrupts

  This function disables IRQ interrupts by setting the I-bit in the CPSR.
  Can only be executed in Privileged modes.
 */
__attribute__ ((always_inline)) static inline void __disable_irq(void)
{
  __ASM volatile ("cpsid i");
}

/* Get Control Register

    This function returns the content of the Control Register.

    \return               Control Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, control":"=r" (result));
  return (result);
}

/* Set Control Register

    This function writes the given value to the Control Register.

    \param [in]    control  Control Register value to set
 */
__attribute__ ((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __ASM volatile ("MSR control, %0"::"r" (control));
}

/* Get IPSR Register

    This function returns the content of the IPSR Register.

    \return               IPSR Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, ipsr":"=r" (result));
  return (result);
}

/* Get APSR Register

    This function returns the content of the APSR Register.

    \return               APSR Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, apsr":"=r" (result));
  return (result);
}

/* Get xPSR Register

    This function returns the content of the xPSR Register.

    \return               xPSR Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, xpsr":"=r" (result));
  return (result);
}

/* Get Process Stack Pointer

    This function returns the current value of the Process Stack Pointer (PSP).

    \return               PSP Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_PSP(void)
{
  register uint32_t result;

  __ASM volatile ("MRS %0, psp\n":"=r" (result));
  return (result);
}

/* Set Process Stack Pointer

    This function assigns the given value to the Process Stack Pointer (PSP).

    \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__attribute__ ((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __ASM volatile ("MSR psp, %0\n"::"r" (topOfProcStack));
}

/* Get Main Stack Pointer

    This function returns the current value of the Main Stack Pointer (MSP).

    \return               MSP Register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_MSP(void)
{
  register uint32_t result;

  __ASM volatile ("MRS %0, msp\n":"=r" (result));
  return (result);
}

/* Set Main Stack Pointer

    This function assigns the given value to the Main Stack Pointer (MSP).

    \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__attribute__ ((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0\n"::"r" (topOfMainStack));
}

/* Get Priority Mask

    This function returns the current state of the priority mask bit from the
    Priority Mask Register.

    \return               Priority Mask value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, primask":"=r" (result));
  return (result);
}

/* Set Priority Mask

    This function assigns the given value to the Priority Mask Register.

    \param [in]    priMask  Priority Mask
 */
__attribute__ ((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __ASM volatile ("MSR primask, %0"::"r" (priMask));
}

#  if       (__CORTEX_M >= 0x03)

/* Enable FIQ

    This function enables FIQ interrupts by clearing the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
__attribute__ ((always_inline)) static inline void __enable_fault_irq(void)
{
  __ASM volatile ("cpsie f");
}

/* Disable FIQ

    This function disables FIQ interrupts by setting the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
__attribute__ ((always_inline)) static inline void __disable_fault_irq(void)
{
  __ASM volatile ("cpsid f");
}

/* Get Base Priority

    This function returns the current value of the Base Priority register.

    \return               Base Priority register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_BASEPRI(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, basepri_max":"=r" (result));
  return (result);
}

/* Set Base Priority

    This function assigns the given value to the Base Priority register.

    \param [in]    basePri  Base Priority value to set
 */
__attribute__ ((always_inline)) static inline void __set_BASEPRI(uint32_t value)
{
  __ASM volatile ("MSR basepri, %0"::"r" (value));
}

/* Get Fault Mask

    This function returns the current value of the Fault Mask register.

    \return               Fault Mask register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_FAULTMASK(void)
{
  uint32_t result;

  __ASM volatile ("MRS %0, faultmask":"=r" (result));
  return (result);
}

/* Set Fault Mask

    This function assigns the given value to the Fault Mask register.

    \param [in]    faultMask  Fault Mask value to set
 */
__attribute__ ((always_inline)) static inline void __set_FAULTMASK(uint32_t faultMask)
{
  __ASM volatile ("MSR faultmask, %0"::"r" (faultMask));
}

#  endif                        /* (__CORTEX_M >= 0x03) */

#  if       (__CORTEX_M == 0x04)

/* Get FPSCR

    This function returns the current value of the Floating Point
    Status/Control register.

    \return               Floating Point Status/Control register value
 */
__attribute__ ((always_inline)) static inline uint32_t __get_FPSCR(void)
{
#    if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  uint32_t result;

  __ASM volatile ("VMRS %0, fpscr":"=r" (result));
  return (result);
#    else
  return (0);
#    endif
}

/* Set FPSCR

    This function assigns the given value to the Floating Point Status/Control
    register.

    \param [in]    fpscr  Floating Point Status/Control value to set
 */
__attribute__ ((always_inline)) static inline void __set_FPSCR(uint32_t fpscr)
{
#    if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  __ASM volatile ("VMSR fpscr, %0"::"r" (fpscr));
#    endif
}

#  endif                        /* (__CORTEX_M == 0x04) */
#endif                          /* __CORE_CMFUNC_H */
