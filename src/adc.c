/**
 * @file adc.c
 *
 * @brief Provides the ADC interrupt handler and a function to initialize ADC.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-07T19:39:03-0500
 * @date Last modified: 2014-01-12T18:04:47-0500
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
#include "adc.h"
//
// ADC Control Register, LPC_ADC->CR
//
static const uint32_t ADC_CHANNELS     = (1 << VREF_25_CHANNEL)|(1 << CURRENT_CHANNEL)|(1 << VOLTAGE_CHANNEL);
static const uint32_t ADC_CR_CHAN_Msk  = 0xFFuL;
static const uint32_t ADC_CR_BURST_ON  = 1uL << 16;
static const uint32_t ADC_CR_PDN       = 1uL << 21;
static const uint32_t ADC_CR_START_Msk = 7uL << 24;
static const uint32_t ADC_CR_START_NOW = 1uL << 24;
//
// ADC Global Data Register, LPC_ADC->GDR
// ADC Data Registers,  LPC_ADC->DR[0] through DR[7]
//
static const uint32_t ADC_DR_DATA_Pos  = 6;
//static const uint32_t ADC_DR_DATA_Msk  = 0x3FFuL << ADC_DR_DATA_Pos;
static const uint32_t ADC_DR_DATA_Msk  = 0x3FFuL << 6;
static const uint32_t ADC_DR_DONE      = 1uL << 31;
static const uint32_t ADC_DR_OVERRUN   = 1uL << 30;
//
// In ADC Interrupt Enable Register,  LPC_ADC->INTEN
//
#if VREF_25_CHANNEL > CURRENT_CHANNEL
#  if VREF_25_CHANNEL > VOLTAGE_CHANNEL
static const uint32_t HIGHEST_CHANNEL = VREF_25_CHANNEL;
#  else
static const uint32_t HIGHEST_CHANNEL = VOLTAGE_CHANNEL;
#  endif
#else
#  if CURRENT_CHANNEL > VOLTAGE_CHANNEL
static const uint32_t HIGHEST_CHANNEL = CURRENT_CHANNEL;
#  else
static const uint32_t HIGHEST_CHANNEL = VOLTAGE_CHANNEL;
#  endif
#endif
static const uint32_t ADC_INTEN_GLBL_INT = 1uL << 8;
//
// In ADC Status Register,  LPC_ADC->STAT
//
static const uint32_t ADC_STAT_DONE_Msk    = 0xFFuL << 0;
static const uint32_t ADC_STAT_OVERRUN_Pos = 8;
//static const uint32_t ADC_STAT_OVERRUN_Msk = 0xFFuL << ADC_STAT_OVERRUN_Pos;
static const uint32_t ADC_STAT_OVERRUN_Msk = 0xFFuL << 8;
static const uint32_t ADC_STAT_ADINT       = 0x1uL << 16;
//
// SysCon registers for clocking and power
//
static const uint32_t SYSCON_SYSAHBCLKCTRL_ADC = 1uL << 13;
static const uint32_t SYSCON_PDRUNCFG_ADC      = 1uL << 4;
//
// Appropriate bit settings for IO pin configuration
//
static const uint32_t IOCON_FUNC_Msk  = 0x7 << 0;
static const uint32_t IOCON_MODE_Msk  = 3uL << 3;
static const uint32_t IOCON_ANALOG    = 1uL << 7;
static const uint32_t IOCON_ADC0      = 2uL << 0;
static const uint32_t IOCON_ADC1      = 2uL << 0;
static const uint32_t IOCON_ADC2      = 2uL << 0;
static const uint32_t IOCON_ADC3      = 2uL << 0;
static const uint32_t IOCON_ADC4      = 2uL << 0;
static const uint32_t IOCON_ADC5      = 1uL << 0;
static const uint32_t IOCON_ADC6      = 1uL << 0;
static const uint32_t IOCON_ADC7      = 1uL << 0;

/**
 * @brief Initialize the analog-to-digital converter
 *
 * @details Turn on power to the ADC by disabling its power-down bit in
 * `PDRUNCFG` then enable its clock in `SYSAHBCLKCTRL`.
 * Each of the pins used as an ADC input must then be reconfigured for the
 * analog input function.
 */
void ADC_Init()
{
  // Disable Power down bit to the ADC block.
  LPC_SYSCON->PDRUNCFG &= ~SYSCON_PDRUNCFG_ADC;
  // Enable AHB clock to the ADC.
  LPC_SYSCON->SYSAHBCLKCTRL |= SYSCON_SYSAHBCLKCTRL_ADC;
  //
  // Configure A/D pins
  //
#if (ADC_CHANNELS & (1 << 0)) != 0
  LPC_IOCON->IOCON_ADC0PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC0PIN |= IOCON_ADC0;
#endif
#if (ADC_CHANNELS & (1 << 1)) != 0
  LPC_IOCON->IOCON_ADC1PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC1PIN |= IOCON_ADC1;
#endif
#if (ADC_CHANNELS & (1 << 2)) != 0
  LPC_IOCON->IOCON_ADC2PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC2PIN |= IOCON_ADC2;
#endif
#if (ADC_CHANNELS & (1 << 3)) != 0
  LPC_IOCON->IOCON_ADC3PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC3PIN |= IOCON_ADC3;
#endif
#if (ADC_CHANNELS & (1 << 4)) != 0
  LPC_IOCON->IOCON_ADC4PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC4PIN |= IOCON_ADC4;
#endif
#if (ADC_CHANNELS & (1 << 5)) != 0
  LPC_IOCON->IOCON_ADC5PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC5PIN |= IOCON_ADC5;
#endif
#if (ADC_CHANNELS & (1 << 6)) != 0
  LPC_IOCON->IOCON_ADC6PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC6PIN |= IOCON_ADC6;
#endif
#if (ADC_CHANNELS & (1 << 7)) != 0
  LPC_IOCON->IOCON_ADC7PIN &= ~(IOCON_ANALOG | IOCON_FUNC_Msk | IOCON_MODE_Msk);
  LPC_IOCON->IOCON_ADC7PIN |= IOCON_ADC7;
#endif

  /**
   * Select the desired ADC channels, turn on burst mode, and set the clock
   * divider value in the ADC control register. Clear all other bits.
   */
  LPC_ADC->CR = ADC_CHANNELS | ADC_CR_BURST_ON |
      ((SystemCoreClock / LPC_SYSCON->SYSAHBCLKDIV) / ADC_CLK_FREQ - 1) << 8;

  /**
   * Enable ADC interrupts. Interrupt will occur when the highest-numbered
   * channel finishes a conversion. Also enable the NVIC IRQ for the ADC.
   */
  LPC_ADC->INTEN = (1 << HIGHEST_CHANNEL);
  NVIC_EnableIRQ(ADC_IRQn);
  return;
}

/**
 * @brief The ADC interrupt service routine.
 * 
 * @details The conversion from each of the three channels is read from the
 * appropriate ADC data register. The variables ::RawCurrent, ::RawVoltage,
 * and ::FastVoltage are the accumulator for three moving-average filters that
 * perform low-pass filtering on the current and voltage samples. The voltage
 * and current samples are not synchronized to the PWM signal so some samples
 * will be taken when the switching transistor is conducting and some will be
 * taken when it is not conducting. We need to average many samples to get
 * reasonable measurements.
 *
 * The ADC channel for the 2.5V voltage reference is also sampled but this
 * data is discarded. In the future we should use this channel to calibrate
 * the ADC, since the ADC's reference voltage is just the microcontroller's
 * supply voltage.
 */
void ADC_IRQHandler()
{
  uint32_t temp;
  temp = LPC_ADC->STAT;         // clear the interrupt

  temp = (LPC_ADC->DR[CURRENT_CHANNEL] & ADC_DR_DATA_Msk) >> ADC_DR_DATA_Pos;
  RawCurrent = RawCurrent - (RawCurrent / SAMPLES_TO_AVERAGE) + temp;

  temp = (LPC_ADC->DR[VOLTAGE_CHANNEL] & ADC_DR_DATA_Msk) >> ADC_DR_DATA_Pos;
  RawVoltage = RawVoltage - (RawVoltage / SAMPLES_TO_AVERAGE) + temp;
  FastVoltage = FastVoltage - (FastVoltage / SAMPLES_FAST_AVERAGE) + temp;

  temp = (LPC_ADC->DR[VREF_25_CHANNEL] & ADC_DR_DATA_Msk) >> ADC_DR_DATA_Pos;
  temp = LPC_ADC->STAT;         // clear the interrupt
  return;
}
