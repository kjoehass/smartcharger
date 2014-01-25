/**
 * @file pwm.c
 *
 * @brief  Global variables and functions for the pulse-width modulator
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-02T16:16:18-0500
 * @date Last modified: 2014-01-13T08:36:54-0500
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
#include "LPC11xx.h"
#include "charger.h"
#include "pwm.h"

/**
 * The period, in SystemCoreClock cycles, corresponding to the desired value
 * of PWM_FREQ.
 */
static uint32_t PWM_Period;
/**
 * The time, in SystemCoreClock cycles, that the PWM output is low.
 */
static uint32_t PWM_LowTime;
/**
 * The time, in SystemCoreClock cycles, that is added to the duty cycle at each
 * SysTick if we want to increase the duty cycle.
 */
static uint32_t PWM_UpValue;
/**
 * The time, in SystemCoreClock cycles, that is subtracted from the duty cycle
 * at each SysTick if we want to decrease the duty cycle.
 */
static uint32_t PWM_DownValue;

/**
 * @brief Configure and initialize the PWM output.
 *
 * @details Performs all of the initialization needed for the PWM output but
 * sets the current duty cycle to zero. The particular GPIO pin that will act
 * as the output of the timer/counter match register is configured for that
 * function. The internal clock signal to the timer/counter is enabled. The
 * timer/counter is configured for pulse-width modulation where match register
 * 3 sets the period and match register 0 sets the low time.
 *
 * The initial value of the low time is set equal to the period, which has the
 * effect of holding the PWM output continuously low.
 *
 * Finally, the values used to increase or decrease the PWM duty cycle are
 * initialized as a fraction of the total period. Since the PWM period is
 * determined at run time these are also calculated at run time, but if the
 * desired size for the increase or decrease is too small then a default value
 * of 1 clock cycle will be used. These two values are implemented as global
 * variables rather than compile-time constants so we can modify the behavior
 * for different modes of operation.
 *
 * @note The value stored in Match Register 0 (MR0) sets the __low time__ of
 *   the PWM output, which is not intuitive. Loading MR0 with the same value as
 *   the PWM period causes the PWM output to be continuously low so the resulting
 *   duty cycle is 0%. Loading MR0 with a value of 0 causes the PWM output to be
 *   continuously high, a duty cycle of 100%.
 */
void PWM_Start()
{
  // Set IO pin to be the Match 0 output of 16-bit Timer/Counter
  LPC_IOCON->MATCH_PIN |= MATCH_PIN_CONFIG;
  // Make sure the timer/counter clock is enabled.
  LPC_SYSCON->SYSAHBCLKCTRL |= COUNTER_TIMER_CLK;
  //
  // Enable the timer/counter and set Match 0 to be a PWM output.
  // Configure Match Register 3 to reset the timer (set the period)
  //
  PWM_TIMER->TCR |= ENABLE_TC;
  PWM_TIMER->PWMC |= PWM_MATCH0;
  PWM_TIMER->MCR = MATCH3_RESET;
  PWM_Period = SystemCoreClock / PWM_FREQ;
  PWM_TIMER->MR3 = PWM_Period;
  //
  // Start with the "low time" in MR0 equal to the PWM period, so the PWM
  // output is held low at reset
  //
  PWM_LowTime = PWM_Period;
  PWM_TIMER->MR0 = PWM_LowTime;
  //
  // Initialize the increment/decrement values
  //
  PWM_UpValue = PWM_Period >> PWM_UP_STEP;
  if (PWM_UpValue == 0) PWM_UpValue = 1;
  PWM_DownValue = PWM_Period >> PWM_DOWN_STEP;
  if (PWM_DownValue == 0) PWM_DownValue = 1;
}
/**
 * @brief Stop and disable the PWM signal.
 *
 * @details First set the low time of the PWM signal to be equal to the period,
 * so that the PWM output will always be low. Just for good measure we change
 * the PWM output pin back to its GPIO function and write a 0 to that bit.
 */
void PWM_Stop()
{
  PWM_LowTime = PWM_Period;
  PWM_TIMER->MR0 = PWM_LowTime;
  LPC_IOCON->MATCH_PIN &= ~MATCH_PIN_CONFIG;
  PWM_GPIO->DIR |= PWM_PIN_MSK;
  PWM_GPIO->DATA &= PWM_PIN_MSK;
}
/**
 * @brief Increase the PWM duty cycle.
 *
 * @details This is done by _decreasing_ the PWM low time in match register 0.
 * The amount by which the low time is changed is determined indirectly by
 * PWM_UpStep, and directly by PWM_UpValue. We check to make sure that the low
 * time will never go to zero or negative.
 */
void PWM_IncreaseDutyCycle()
{
  if (PWM_LowTime > PWM_UpValue)
    PWM_LowTime -= PWM_UpValue;
  PWM_TIMER->MR0 = PWM_LowTime;
}
/**
 * @brief Decrease the PWM duty cycle.
 * @details This is done by _increasing_ the PWM low time in match register 0.
 * The amount by which the low time is changed is specified indirectly by
 * PWM_DownStep, and directly by PWM_DownValue. We check to make sure that the
 * low time will never become equal to or greater than the PWM period.
 */
void PWM_DecreaseDutyCycle()
{
  if (PWM_LowTime < (PWM_Period - PWM_DownValue))
    PWM_LowTime += PWM_DownValue;
  PWM_TIMER->MR0 = PWM_LowTime;
}
