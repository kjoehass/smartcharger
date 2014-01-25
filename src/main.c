/**
 * @file main.c
 *
 * @brief An intelligent battery charger.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-08T19:12:48-0500
 * @date Last modified: 2014-01-12T17:45:06-0500
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
#include "pwm.h"
#include "LCD.h"
#include "SysTick.h"
#include "i2c.h"

/**
 * @var State
 * @brief The current operating state of the charger.
 */
uint32_t State;

/**
 * @var FastVoltage
 * @brief The accumulator for the short moving-average filter of voltages.
 * @var RawVoltage
 * @brief The accumulator for the long moving-average filter of voltages.
 * @var RawCurrent
 * @brief The accumulator for the long moving-average filter of currents.
 */
uint32_t FastVoltage, RawCurrent, RawVoltage;

/**
 * @var Temperature
 * @brief The most recent temperature reading from the sensor.
 */
uint32_t Temperature;

/**
 * @brief The main function for the charger.
 * @details This function is entered automatically at reset. There is no exit
 * from this function, it is declared as _int_ to avoid compiler warning.
 */
int main()
{
  uint32_t i;

  FastVoltage = RawVoltage = RawCurrent = 0;

  PWM_Stop();                   // Disable PWM output (set it low)
  ADC_Init();                   // Initialize the A/D converters

  if (BUTTON1_PRESSED)          // If button pressed at reset, calibrate only
    State = CALIBRATE;
  else                          // else wait for the START button
    State = WAIT4BUTTON;
  //
  // Wait at least 100 ms for the LCD to wake up
  // Assume that the loop takes 4 clocks, wait 125 ms
  //
  for (i = 0; i < (SystemCoreClock / 32); i++) {
  }
  LCD_Init();
  //
  // Set up the System Tick
  //
  FLAG1_PORT->DIR |= FLAG1_Msk;
  FLAG1_PORT->DATA &= ~FLAG1_Msk;
  Ticks = 0;
  SysTick_Config((SystemCoreClock / TICKS_PER_SEC) - 1);
  //
  // Set up the I2C interface for the temperature sensor
  //
  I2CInit((uint32_t) I2CMASTER);

  for (;;) {
    if (0 == Ticks) {
      for (i = 0; i < BUFSIZE; i++) {
        I2CSlaveBuffer[i] = 0x00;
      }
      I2CWriteLength = 0;
      I2CReadLength = 2;
      I2CMasterBuffer[0] = LM75_ADDR | RD_BIT;
      I2CEngine();

      Temperature = I2CSlaveBuffer[0];
      // Wait until Ticks becomes non-zero to read the sensor again
      while (0 == Ticks) {
      }
    }
  }
}
