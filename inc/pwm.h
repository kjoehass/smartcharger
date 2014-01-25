/**
 * @file pwm.h
 *
 * @brief Initialize and control the PWM output.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-12T15:34:58-0500
 * @date Last modified: 2014-01-12T16:08:26-0500
 *
 * @copyright Copyright (C) 2014 Kenneth Joseph Hass
 *
 * @copyright This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * @copyright This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 */
#ifndef _PWM_H_
#  define _PWM_H_

/** 
 * @brief Desired PWM clock frequency, in hertz.
 *
 * @details The integer number of clock cycles that is the actual PWM period is
 * calculated at run time by dividing the system clock frequency by the desired
 * PWM frequency, ::PWM_FREQ. The PWM frequency must be much less than the
 * system clock frequency, say at least 100x lower. A higher PWM frequency may
 * result in relatively coarser adjustments of the duty cycle.
 */
#  define PWM_FREQ 25000
/** 
 * @brief Factor by which duty cycle may be decreased at each system tick.
 *
 * @details This factor is used to compute, at run time, an integer number of
 * clock cycles by which the PWM low time will increase. The integer is equal
 * to (SystemCoreClock / ::PWM_FREQ) >> ::PWM_DOWN_STEP. If the result of this
 * calculation is 0 then a default value of 1 is used instead.
 *
 * Increasing the value of ::PWM_DOWN_STEP causes the duty cycle to decrease
 * more gradually.
 */
#  define PWM_DOWN_STEP 9
/** 
 * @brief Factor by which duty cycle may be increased at each system tick.
 *
 * @details This factor is used to compute, at run time, an integer number of
 * clock cycles by which the PWM low time will decrease. The integer is
 * equal to (SystemCoreClock / ::PWM_FREQ) >> ::PWM_UP_STEP. If the result of
 * this calculation is 0 then a default value of 1 is used instead.
 */
#  define PWM_UP_STEP   9

/**
 * @def MATCH_PIN
 * @brief Specifies the particular I/O pin that is the PWM output.
 * @def MATCH_PIN_CONFIG
 * @brief A mask to configure the I/O pin for the PWM output in LPC_IOCON.
 * @def COUNTER_TIMER_CLK
 * @brief A mask to enable the PWM timer clock in SYSAHBCLKCTRL.
 * @def PWM_TIMER
 * @brief Specifies the name of the PWM timer.
 * @def PWM_GPIO
 * @brief Specifies the name of the GPIO port that includes the PWM output.
 * @def PWM_PIN_MSK
 * @brief A mask to configure a GPIO pin as an output for the PWM signal
 */
#  ifdef __LPC11xx_H__
#    define MATCH_PIN         PIO1_9
#    define MATCH_PIN_CONFIG  (1 << 0)  // PIO1_9 function, LPC11 CT16B1_MAT0
#    define COUNTER_TIMER_CLK (1 << 8)  // AHB clock enable, CT16B1
#    define PWM_TIMER         LPC_TMR16B1
#    define PWM_GPIO          LPC_GPIO1
#    define PWM_PIN_MSK       (1 << 9)
#  endif
#  ifdef __LPC13xx_H__
#    define MATCH_PIN         PIO0_8
#    define MATCH_PIN_CONFIG  (1 << 1)  // PIO0_8 function, LPC13 CT16B0_MAT0
#    define COUNTER_TIMER_CLK (1 << 7)  // AHB clock enable, CT16B0
#    define PWM_TIMER         LPC_TMR16B0
#    define PWM_GPIO          LPC_GPIO0
#    define PWM_PIN_MSK       (1 << 8)
#  endif
/**
 * @def ENABLE_TC
 * @brief A mask to enable the PWM timer in the timer control register.
 * @def PWM_MATCH0
 * @brief A mask to select Match 0 to be the PWM_TIMER's PWM output.
 * @def MATCH3_RESET
 * @brief A mask to select Match 3 to reset the PWM_TIMER.
 */
#  define ENABLE_TC         (1 << 0)    // Enable bit in Timer Control Reg
#  define PWM_MATCH0        (1 << 0)    // Make Match 0 a PWM output
#  define MATCH3_RESET      (1 << 10)   // Make Match 3 reset the timer

//
// Initialize and start the PWM output
//
void PWM_Start();
//
// Shut down the PWM output
//
void PWM_Stop();
//
// Increase the PWM duty cycle
//
void PWM_IncreaseDutyCycle();
//
// Decrease the PWM duty cycle
//
void PWM_DecreaseDutyCycle();

#endif
