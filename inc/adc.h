/**
 * @file adc.h
 *
 * @brief User interface to the ADC functions.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-07T19:31:54-0500
 * @date Last modified: 2014-01-12T18:02:38-0500
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
#ifndef _ADC_H_
#  define _ADC_H_

/**
 * @def   ADC_CLK_FREQ
 * @brief The desired ADC clock frequency, in hertz.
 * @details For the LPC13xx and LPC11xx processors this value must be less than
 * 4.5 MHz. Running the ADC at slower clocks can improve accuracy.
 */
#  define ADC_CLK_FREQ         1000000

/**
 * @def   VREF_25_CHANNEL
 * @brief Specifies which ADC channel is connected to the 2.5V reference.
 * @def   CURRENT_CHANNEL
 * @brief Specifies which ADC channel measures the battery current.
 * @def   VOLTAGE_CHANNEL
 * @brief Specifies which ADC channel measures the battery voltage.
 */
#  define VREF_25_CHANNEL 1
#  define CURRENT_CHANNEL 2
#  define VOLTAGE_CHANNEL 3

/**
 * @def   ADC_VREF_MV
 * @brief The ADC reference voltage, in mV. Here, same as the supply voltage.
 * @def   ADC_BITS
 * @brief The ADC resolution, in bits.
 */
#  define ADC_VREF_MV   3300
#  define ADC_BITS      10


//
// ADC pin names for LPC11xx
//
#ifdef __LPC11xx_H__
#  define IOCON_ADC0PIN   R_PIO0_11
#  define IOCON_ADC1PIN   R_PIO1_0
#  define IOCON_ADC2PIN   R_PIO1_1
#  define IOCON_ADC3PIN   R_PIO1_2
#  define IOCON_ADC4PIN   SWDIO_PIO1_3
#  define IOCON_ADC5PIN   PIO1_4
#  define IOCON_ADC6PIN   PIO1_10
#  define IOCON_ADC7PIN   PIO1_11
#endif
//
// ADC pin names for LPC13xx
//
#ifdef __LPC13xx_H__
#  define IOCON_ADC0PIN   JTAG_TDI_PIO0_11
#  define IOCON_ADC1PIN   JTAG_TMS_PIO1_0
#  define IOCON_ADC2PIN   JTAG_TDO_PIO1_1
#  define IOCON_ADC3PIN   JTAG_nTRST_PIO1_2
#  define IOCON_ADC4PIN   ARM_SWDIO_PIO1_3
#  define IOCON_ADC5PIN   PIO1_4
#  define IOCON_ADC6PIN   PIO1_10
#  define IOCON_ADC7PIN   PIO1_11
#endif

//
// Initializes the ADC and starts conversions.
//
void ADC_Init();

//
// Interrupt service routine for the ADC
//
void ADC_IRQHandler();

#endif                          // #ifndef _ADC_H_
