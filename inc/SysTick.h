/**
 * @file SysTick.h
 *
 * @brief User interface to the SysTick functions.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-07T19:29:34-0500
 * @date Last modified: 2014-01-12T16:18:05-0500
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
#ifndef SYSTICK_H_
#  define SYSTICK_H_

/**
 * @def TICKS_PER_SEC
 * @brief Number of SysTick interrupts per second, which is how often the PWM
 *  duty cycle and LCD display will be updated.
 */
#  define TICKS_PER_SEC  100

extern uint32_t Ticks;

void SysTick_Handler();

#endif                          /* SYSTICK_H_ */
