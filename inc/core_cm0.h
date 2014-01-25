/******************************************************************************
 * @file     core_cm0.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File
 * @version  V2.03
 * @date     23. May 2011
 *
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
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

#ifndef __CORE_CM0_H_GENERIC
#  define __CORE_CM0_H_GENERIC

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
//  CMSIS CM0 definitions
#  define __CM0_CMSIS_VERSION_MAIN  (0x02) // [31:16] CMSIS HAL main version
#  define __CM0_CMSIS_VERSION_SUB   (0x00) // [15:0]  CMSIS HAL sub version
#  define __CM0_CMSIS_VERSION       ((__CM0_CMSIS_VERSION_MAIN << 16) | __CM0_CMSIS_VERSION_SUB)

#  define __CORTEX_M                (0x00)

#  define __ASM            __asm
#  define __INLINE         inline

#  include <stdint.h>
#  include "core_cmInstr.h"
#  include "core_cmFunc.h"

#endif


#ifndef __CMSIS_GENERIC

#  ifndef __CORE_CM0_H_DEPENDANT
#    define __CORE_CM0_H_DEPENDANT

// IO definitions (access restrictions to peripheral registers)
#    define     __I     volatile const  // 'read only' permissions
#    define     __O     volatile        // 'write only' permissions
#    define     __IO    volatile        // 'read / write' permissions

/*******************************************************************************
 *                 Register Abstraction
 ******************************************************************************/
// Application Program Status Register (APSR)
typedef union {
  struct {
    uint32_t _reserved0:27;     // bit:  0..26  Reserved
    uint32_t Q:1;               // bit:     27  Saturation condition flag
    uint32_t V:1;               // bit:     28  Overflow condition code flag
    uint32_t C:1;               // bit:     29  Carry condition code flag
    uint32_t Z:1;               // bit:     30  Zero condition code flag
    uint32_t N:1;               // bit:     31  Negative condition code flag
  } b;                          // Structure used for bit  access
  uint32_t w;                   // Type      used for word access
} APSR_Type;

// Interrupt Program Status Register (IPSR).
typedef union {
  struct {
    uint32_t ISR:9;             // bit:  0.. 8  Exception number
    uint32_t _reserved0:23;     // bit:  9..31  Reserved
  } b;                          // Structure used for bit  access
  uint32_t w;                   // Type      used for word access
} IPSR_Type;


// Special-Purpose Program Status Registers (xPSR).
typedef union {
  struct {
    uint32_t ISR:9;             // bit:  0.. 8  Exception number
    uint32_t _reserved0:15;     // bit:  9..23  Reserved
    uint32_t T:1;               // bit:     24  Thumb bit        (read 0)
    uint32_t IT:2;              // bit: 25..26  saved IT state   (read 0)
    uint32_t Q:1;               // bit:     27  Saturation condition flag
    uint32_t V:1;               // bit:     28  Overflow condition code flag
    uint32_t C:1;               // bit:     29  Carry condition code flag
    uint32_t Z:1;               // bit:     30  Zero condition code flag
    uint32_t N:1;               // bit:     31  Negative condition code flag
  } b;                          // Structure used for bit  access
  uint32_t w;                   // Type      used for word access
} xPSR_Type;

// Control Registers (CONTROL).
typedef union {
  struct {
    uint32_t nPRIV:1;           // bit:      0  Execution privilege, thread mode
    uint32_t SPSEL:1;           // bit:      1  Stack to be used
    uint32_t FPCA:1;            // bit:      2  FP extension active flag
    uint32_t _reserved0:29;     // bit:  3..31  Reserved
  } b;                          // Structure used for bit  access
  uint32_t w;                   // Type      used for word access
} CONTROL_Type;

// Nested Vectored Interrupt Controller (NVIC).

typedef struct {
  __IO uint32_t ISER[1];  // Offset: 0x000 (R/W) Interrupt Set Enable Reg
  uint32_t RESERVED0[31];
  __IO uint32_t ICER[1];  // Offset: 0x080 (R/W) Interrupt Clear Enable Reg
  uint32_t RSERVED1[31];
  __IO uint32_t ISPR[1];  // Offset: 0x100 (R/W) Interrupt Set Pending Reg
  uint32_t RESERVED2[31];
  __IO uint32_t ICPR[1];  // Offset: 0x180 (R/W) Interrupt Clear Pending Reg
  uint32_t RESERVED3[31];
  uint32_t RESERVED4[64];
  __IO uint32_t IPR[8];   // Offset: 0x3EC (R/W) Interrupt Priority Reg
} NVIC_Type;

// System Control Block (SCB).
typedef struct {
  __I uint32_t CPUID;     // Offset: 0x000 (R/ ) CPU ID Base Reg
  __IO uint32_t ICSR;     // Offset: 0x004 (R/W) Interrupt Control State Reg
  uint32_t RESERVED0;
  __IO uint32_t AIRCR;    // Offset: 0x00C (R/W) Application Interrupt/Reset Control Reg
  __IO uint32_t SCR;      // Offset: 0x010 (R/W) System Control Reg
  __IO uint32_t CCR;      // Offset: 0x014 (R/W) Configuration Control Reg
  uint32_t RESERVED1;
  __IO uint32_t SHP[2];   // Offset: 0x01C (R/W) System Handlers Priority Regs [0] is RESERVED
} SCB_Type;

// SCB CPUID Register Definitions
#    define SCB_CPUID_IMPLEMENTER_Pos   24
#    define SCB_CPUID_IMPLEMENTER_Msk   (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)
#    define SCB_CPUID_VARIANT_Pos       20
#    define SCB_CPUID_VARIANT_Msk       (0xFUL << SCB_CPUID_VARIANT_Pos)
#    define SCB_CPUID_ARCHITECTURE_Pos  16
#    define SCB_CPUID_ARCHITECTURE_Msk  (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)
#    define SCB_CPUID_PARTNO_Pos         4
#    define SCB_CPUID_PARTNO_Msk        (0xFFFUL << SCB_CPUID_PARTNO_Pos)
#    define SCB_CPUID_REVISION_Pos       0
#    define SCB_CPUID_REVISION_Msk      (0xFUL << SCB_CPUID_REVISION_Pos)

// SCB Interrupt Control State Register Definitions
#    define SCB_ICSR_NMIPENDSET_Pos     31
#    define SCB_ICSR_NMIPENDSET_Msk     (1UL << SCB_ICSR_NMIPENDSET_Pos)
#    define SCB_ICSR_PENDSVSET_Pos      28
#    define SCB_ICSR_PENDSVSET_Msk      (1UL << SCB_ICSR_PENDSVSET_Pos)
#    define SCB_ICSR_PENDSVCLR_Pos      27
#    define SCB_ICSR_PENDSVCLR_Msk      (1UL << SCB_ICSR_PENDSVCLR_Pos)
#    define SCB_ICSR_PENDSTSET_Pos      26
#    define SCB_ICSR_PENDSTSET_Msk      (1UL << SCB_ICSR_PENDSTSET_Pos)
#    define SCB_ICSR_PENDSTCLR_Pos      25
#    define SCB_ICSR_PENDSTCLR_Msk      (1UL << SCB_ICSR_PENDSTCLR_Pos)
#    define SCB_ICSR_ISRPREEMPT_Pos     23
#    define SCB_ICSR_ISRPREEMPT_Msk     (1UL << SCB_ICSR_ISRPREEMPT_Pos)
#    define SCB_ICSR_ISRPENDING_Pos     22
#    define SCB_ICSR_ISRPENDING_Msk     (1UL << SCB_ICSR_ISRPENDING_Pos)
#    define SCB_ICSR_VECTPENDING_Pos    12
#    define SCB_ICSR_VECTPENDING_Msk    (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)
#    define SCB_ICSR_VECTACTIVE_Pos      0
#    define SCB_ICSR_VECTACTIVE_Msk     (0x1FFUL << SCB_ICSR_VECTACTIVE_Pos)

// SCB Application Interrupt and Reset Control Register Definitions
#    define SCB_AIRCR_VECTKEY_Pos       16
#    define SCB_AIRCR_VECTKEY_Msk       (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)
#    define SCB_AIRCR_VECTKEYSTAT_Pos   16
#    define SCB_AIRCR_VECTKEYSTAT_Msk   (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)
#    define SCB_AIRCR_ENDIANESS_Pos     15
#    define SCB_AIRCR_ENDIANESS_Msk     (1UL << SCB_AIRCR_ENDIANESS_Pos)
#    define SCB_AIRCR_SYSRESETREQ_Pos    2
#    define SCB_AIRCR_SYSRESETREQ_Msk   (1UL << SCB_AIRCR_SYSRESETREQ_Pos)
#    define SCB_AIRCR_VECTCLRACTIVE_Pos  1
#    define SCB_AIRCR_VECTCLRACTIVE_Msk (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)

// SCB System Control Register Definitions
#    define SCB_SCR_SEVONPEND_Pos        4
#    define SCB_SCR_SEVONPEND_Msk       (1UL << SCB_SCR_SEVONPEND_Pos)
#    define SCB_SCR_SLEEPDEEP_Pos        2
#    define SCB_SCR_SLEEPDEEP_Msk       (1UL << SCB_SCR_SLEEPDEEP_Pos)
#    define SCB_SCR_SLEEPONEXIT_Pos      1
#    define SCB_SCR_SLEEPONEXIT_Msk     (1UL << SCB_SCR_SLEEPONEXIT_Pos)

// SCB Configuration Control Register Definitions
#    define SCB_CCR_STKALIGN_Pos         9
#    define SCB_CCR_STKALIGN_Msk        (1UL << SCB_CCR_STKALIGN_Pos)
#    define SCB_CCR_UNALIGN_TRP_Pos      3
#    define SCB_CCR_UNALIGN_TRP_Msk     (1UL << SCB_CCR_UNALIGN_TRP_Pos)

// System Timer (SysTick).

typedef struct {
  __IO uint32_t CTRL; // Offset: 0x000 (R/W)  SysTick Control & Status Register
  __IO uint32_t LOAD; // Offset: 0x004 (R/W)  SysTick Reload Value Register
  __IO uint32_t VAL;  // Offset: 0x008 (R/W)  SysTick Current Value Register
  __I uint32_t CALIB; // Offset: 0x00C (R/ )  SysTick Calibration Register
} SysTick_Type;

// SysTick Control / Status Register Definitions
#    define SysTick_CTRL_COUNTFLAG_Pos  16
#    define SysTick_CTRL_COUNTFLAG_Msk  (1UL << SysTick_CTRL_COUNTFLAG_Pos)
#    define SysTick_CTRL_CLKSOURCE_Pos   2
#    define SysTick_CTRL_CLKSOURCE_Msk  (1UL << SysTick_CTRL_CLKSOURCE_Pos)
#    define SysTick_CTRL_TICKINT_Pos     1
#    define SysTick_CTRL_TICKINT_Msk    (1UL << SysTick_CTRL_TICKINT_Pos)
#    define SysTick_CTRL_ENABLE_Pos      0
#    define SysTick_CTRL_ENABLE_Msk     (1UL << SysTick_CTRL_ENABLE_Pos)
#    define SysTick_LOAD_RELOAD_Pos      0
#    define SysTick_LOAD_RELOAD_Msk     (0xFFFFFFUL << SysTick_LOAD_RELOAD_Pos)
#    define SysTick_VAL_CURRENT_Pos      0
#    define SysTick_VAL_CURRENT_Msk     (0xFFFFFFUL << SysTick_VAL_CURRENT_Pos)
#    define SysTick_CALIB_NOREF_Pos     31
#    define SysTick_CALIB_NOREF_Msk     (1UL << SysTick_CALIB_NOREF_Pos)
#    define SysTick_CALIB_SKEW_Pos      30
#    define SysTick_CALIB_SKEW_Msk      (1UL << SysTick_CALIB_SKEW_Pos)
#    define SysTick_CALIB_TENMS_Pos      0
#    define SysTick_CALIB_TENMS_Msk     (0xFFFFFFUL << SysTick_VAL_CURRENT_Pos)

// Memory mapping of Cortex-M0 Hardware
#    define SCS_BASE        (0xE000E000UL)  // System Control Space Base Address
#    define CoreDebug_BASE  (0xE000EDF0UL)  // Core Debug Base Address
#    define SysTick_BASE    (SCS_BASE +  0x0010UL)  // SysTick Base Address
#    define NVIC_BASE       (SCS_BASE +  0x0100UL)  // NVIC Base Address
#    define SCB_BASE        (SCS_BASE +  0x0D00UL)  // System Control Block Base
#    define SCB             ((SCB_Type *)           SCB_BASE)
#    define SysTick         ((SysTick_Type *)       SysTick_BASE)
#    define NVIC            ((NVIC_Type *)          NVIC_BASE)

// #######################   NVIC functions  #################################

// Interrupt Priorities are WORD accessible only under ARMv6M
// The following MACROS handle generation of the register offset and byte masks
#    define _BIT_SHIFT(IRQn)    (  (((uint32_t)(IRQn)       )    &  0x03) * 8 )
#    define _SHP_IDX(IRQn)      ( ((((uint32_t)(IRQn) & 0x0F)-8) >>    2)     )
#    define _IP_IDX(IRQn)       (   ((uint32_t)(IRQn)            >>    2)     )

/*
 * Enable External Interrupt

  This function enables a device specific interrupt in the NVIC interrupt
  controller. The interrupt number cannot be a negative value. 

  param:  IRQn  Number of the external interrupt to enable
*/
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->ISER[0] = (1 << ((uint32_t) (IRQn) & 0x1F));
}

/* Disable External Interrupt

   This function disables a device specific interupt in the NVIC interrupt
   controller. The interrupt number cannot be a negative value. 

   param:  IRQn  Number of the external interrupt to disable
*/
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->ICER[0] = (1 << ((uint32_t) (IRQn) & 0x1F));
}

/* Get Pending Interrupt

   This function reads the pending register in the NVIC and returns the
   pending bit for the specified interrupt. 

    param       IRQn  Number of the interrupt for get pending
    return      0  Interrupt status is not pending
    return      1  Interrupt status is pending
*/
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return ((uint32_t)
          ((NVIC->ISPR[0] & (1 << ((uint32_t) (IRQn) & 0x1F))) ? 1 : 0));
}

/* Set Pending Interrupt

    This function sets the pending bit for the specified interrupt. 
    The interrupt number cannot be a negative value.

    \param [in]      IRQn  Number of the interrupt for set pending
*/
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ISPR[0] = (1 << ((uint32_t) (IRQn) & 0x1F));
}

/* Clear Pending Interrupt

    This function clears the pending bit for the specified interrupt. 
    The interrupt number cannot be a negative value.

    \param [in]      IRQn  Number of the interrupt for clear pending
*/
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ICPR[0] = (1 << ((uint32_t) (IRQn) & 0x1F));
}

/* Set Interrupt Priority

    This function sets the priority for the specified interrupt. The interrupt 
    number can be positive to specify an external (device specific) 
    interrupt, or negative to specify an internal (core) interrupt.

    Note: The priority cannot be set for every core interrupt.

    \param [in]      IRQn  Number of the interrupt for set priority
    \param [in]  priority  Priority to set
*/
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if (IRQn < 0) {
    SCB->SHP[_SHP_IDX(IRQn)] =
        (SCB->
         SHP[_SHP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) <<
         _BIT_SHIFT(IRQn));
  } else {
    NVIC->IPR[_IP_IDX(IRQn)] =
        (NVIC->
         IPR[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) <<
         _BIT_SHIFT(IRQn));
  }
}

/* Get Interrupt Priority

    This function reads the priority for the specified interrupt. The interrupt 
    number can be positive to specify an external (device specific) 
    interrupt, or negative to specify an internal (core) interrupt.

    The returned priority value is automatically aligned to the implemented
    priority bits of the microcontroller.

    \param [in]   IRQn  Number of the interrupt for get priority
    \return             Interrupt Priority
*/

static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if (IRQn < 0) {
    return ((uint32_t)
            ((SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn)) >> (8 -
                                                                __NVIC_PRIO_BITS)));
  } else {
    return ((uint32_t)
            ((NVIC->IPR[_IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn)) >> (8 -
                                                                __NVIC_PRIO_BITS)));
  }
}

/* System Reset

    This function initiate a system reset request to reset the MCU.
*/
static __INLINE void NVIC_SystemReset(void)
{
  __DSB();                // Ensure all outstanding memory accesses included
                          // buffered write are completed before reset
  SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) |
                SCB_AIRCR_SYSRESETREQ_Msk);
  __DSB();                // Ensure completion of memory access
  while (1);              // wait until reset
}

// ########################    SysTick function  ###############################
#    if (__Vendor_SysTickConfig == 0)

/* System Tick Configuration

    This function initialises the system tick timer and its interrupt and start
    the system tick timer.  Counter is in free running mode to generate
    periodical interrupts.

    \param [in]  ticks  Number of ticks between two interrupts
    \return          0  Function succeeded
    \return          1  Function failed
*/
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if (ticks > SysTick_LOAD_RELOAD_Msk)
    return (1);                 // Reload value impossible

  // set reload register
  SysTick->LOAD = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
  // set Priority for Cortex-M0 System Interrupts
  NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
  // Load the SysTick Counter Value
  SysTick->VAL = 0;
  // Enable SysTick IRQ and SysTick Timer
  SysTick->CTRL =
      SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |
      SysTick_CTRL_ENABLE_Msk;
  return (0);
}

#    endif
#  endif                        // __CORE_CM0_H_DEPENDANT
#endif                          // __CMSIS_GENERIC
