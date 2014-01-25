/**
 * @file SysTick.c
 *
 * @brief Provides the SysTick interrupt handler.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-08T19:47:51-0500
 * @date Last modified: 2014-01-12T17:45:35-0500
 *
 * @details The PWM duty cycle is changed as necessary and the LCD display is
 * updated when this interrupt is serviced.
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
#include "SysTick.h"
#include "charger.h"
#include "LCD.h"
#include "pwm.h"
#include "adc.h"

/**
 * @var   Ticks
 * @brief Counts SysTick interrupts to support long interval timing.
 */
uint32_t Ticks;

//
// This is the basic text used for the second row of the display when the
// charger is running. The actual digits are inserted by the
// DisplayMeasurements function.
//
static const char *StatusLine = "00.0V 0.0A  00 C";

//
// Maximum ADC value + 1
//
static const uint32_t ADC_MAX_COUNT = (1 << ADC_BITS);

/**
 * @var FastVoltage_mV
 * @brief The value of ::FastVoltage converted to mV, every SysTick.
 * @var BattVoltage_mV
 * @brief The value of ::RawVoltage converted to mV, every SysTick.
 * @var BattCurrent_mA
 * @brief The value of ::RawCurrent converted to mA, every SysTick.
 */
static uint32_t FastVoltage_mV, BattVoltage_mV, BattCurrent_mA;

/**
 * @brief Convert binary to BCD for display.
 * @details Binary values less than 100,000 decimal are converted to BCD. The
 * resulting BCD values are packed into a 32-bit integer. There may be up to
 * five valid BCD values.
 *
 * @param[in] binary_value binary integer to be converted to BCD
 * @return    packed BCD representation
 */
static uint32_t Binary2BCD(uint32_t binary_value)
{
  uint32_t bcd_value = 0;

  while (binary_value > 9999) {
    bcd_value += 0x10000;
    binary_value -= 10000;
  }
  while (binary_value > 999) {
    bcd_value += 0x1000;
    binary_value -= 1000;
  }
  while (binary_value > 99) {
    bcd_value += 0x100;
    binary_value -= 100;
  }
  while (binary_value > 9) {
    bcd_value += 0x10;
    binary_value -= 10;
  }
  bcd_value += binary_value;
  return bcd_value;
}

/**
 * @brief Inserts ASCII values for measurements into LCD output string.
 * @details There are two global variables, ::TopLine and ::BottomLine
 * that contain the text that is displayed on the LCD while charging is in
 * progress. This function converts the binary values of the voltage, current
 * and temperature measurements to BCD and then inserts those ASCII characters
 * at the correct positions in ::BottomLine
 *
 * The resolution of the output string is 0.1V, 0.1A, and 1.0C.
 *
 * @todo Increase voltage display accuracy in calibration mode, do not
 *       display current (or temperature?)
 * @todo Remove leading zero for temperatures less than 10C
 * @todo Handle negative temperatures
 */
static void DisplayMeasurements()
{
  uint32_t temp;

  // round to tenths of volts
  temp = Binary2BCD(BattVoltage_mV + 50);
  BottomLine[3] = (char) ((temp >> 8) & 0xF) + '0';
  BottomLine[1] = (char) ((temp >> 12) & 0xF) + '0';
  BottomLine[0] = (char) ((temp >> 16) & 0xF) + '0';

  // round to tenths of amperes
  temp = Binary2BCD(BattCurrent_mA + 50);
  BottomLine[8] = (char) ((temp >> 8) & 0xF) + '0';
  BottomLine[6] = (char) ((temp >> 12) & 0xF) + '0';

  BottomLine[14] = 0xdf;              // degree symbol
  temp = Binary2BCD(Temperature);
  BottomLine[13] = (char) (temp & 0xF) + '0';
  BottomLine[12] = (char) ((temp >> 4) & 0xF) + '0';
}

/**
 * @brief Copies ASCII text to a specified location.
 * @details This is a simple string copying function. The strings are assumed
 * to have ::MAX_COL +1 characters.
 *
 * @param[out] dest pointer to destination characters
 * @param[in] src pointer to source characters
 */
static void CopyLine(char *dest, const char *src)
{
  uint32_t i;
  for (i = 0; i <= MAX_COL; i++)
    dest[i] = src[i];
}

/**
 * @brief Error handler.
 * @details Disable the PWM output, change the charger state to the ERROR
 * state, and put an error message on the first line of the display.
 */
static void Error()
{
  PWM_Stop();
  State = ERROR;
  CopyLine(TopLine, "Charging stopped");
}

/**
  @brief The SysTick interrupt handler.
  @details This function maintains the state machine for the different charging
    modes, looks for shorts/opens at the battery terminals, and updates the
    LCD display.

  For diagnostic purposes, one GPIO pin is used to indicate when this handler
  is executing. This pin is defined as the FLAG1 pin, and it is set to a 1 as
  the first statement of the handler and is then cleared to 0 as the last
  statement in the handler.

  Raw current and voltage readings have been accumulated by the ADC interrupt
  handler, they get converted to actual voltage and current values here. The
  ADC interrupt uses moving-average filters to smooth the voltage/current data
  so the raw values must be divided by the length of those filters as part
  of the conversion. <tt>BattCurrent_mA</tt> and <tt>BattVoltage_mV</tt> use
  long filters for better smoothing, but <tt>FastVoltage_mV</tt> uses a shorter
  filter so that faults can be detected more quickly.

  Once the voltage and current are calculated, check to see if there appears
  to be a fault condition that causes the battery voltage to be too low or
  too high. If so, shut down the PWM and display an appropriate message.

  If there are no faults then the normal state machine processing is done.
  At reset we enter one of two states. If Button 1 (the Start button) is
  pressed when reset occurs then we enter the CALIBRATE state. In this state
  the calculated battery voltage is simply printed to the LCD, without
  activating the PWM output. This is intended for calibration purposes. The
  processor must be reset to leave the CALIBRATE state.

  If Button 1 is not pressed at reset then the process enters the WAIT4BUTTON
  state. The PWM output remains off and we wait for Button 1 to be pressed.

  Once Button 1 is pressed we enter the CHECK4BATT state. At the next SysTick
  interrupt the first check for a faulty voltage is performed, so the CHECK4BATT
  state should last for just one SysTick period. If the battery voltage is
  within expected limits then the PWM timer is intialized and the state will
  transition to CC_CHARGE.

  In the CC_CHARGE state the charger attempts to maintain the charging current
  at the value specified by MODE1_CURRENT_MA, and this is done by increasing
  the duty cycle if BattCurrent_mA is less than MODE1_CURRENT_MA or decreasing
  the duty cycle if BattCurrent_mA is greater than MODE1_CURRENT_MA. This
  constant-current charging continues until the batter voltage rises to the
  level specified by MODE1_VOLTAGE_MV, and then we transition to the CV_CHARGE
  state.

  In the CV_CHARGE state the battery is charged at a constant voltage specified
  by MODE2_VOLTAGE_MV. The PWM duty cycle is adjusted up or down to maintain
  this charging voltage. The charger stays in this state until the charging
  current falls below MODE2_CURRENT_MA, and then the charger transitions to
  the TRICKLE mode.

  The TRICKLE state is also a constant-voltage state, but the desired charging
  voltage is significantly lower than in the CV_CHARGE state. The charger
  remains in this state indefinitely, until the processor is reset or a faulty
  voltage is measured at the battery terminals.

  In addition to maintaining the charger state, the SysTick interrupt handler
  writes one character to the LCD every time it is activated.

  Finally, the Ticks variable is incremented. If the Ticks counter reaches the
  number of SysTick interrupts in one second then it will be cleared. The Ticks
  counter is used to control activities that happen at a very low rate, such
  as reading the temperature sensor.
 */
void SysTick_Handler(void)
{
  FLAG1_PORT->DATA |= FLAG1_Msk;
  //
  // Convert raw ADC data to voltages and current
  //
  BattCurrent_mA = ((RawCurrent * I_MAX_MA)/SAMPLES_TO_AVERAGE)/ADC_MAX_COUNT;
#if SAMPLES_TO_AVERAGE > 128
  BattVoltage_mV = ((RawVoltage/SAMPLES_TO_AVERAGE) * V_MAX_MV)/ADC_MAX_COUNT;
#else
  BattVoltage_mV = ((RawVoltage * V_MAX_MV)/SAMPLES_TO_AVERAGE)/ADC_MAX_COUNT;
#endif
  FastVoltage_mV = ((FastVoltage * V_MAX_MV)/SAMPLES_FAST_AVERAGE)/ADC_MAX_COUNT;
  //
  // Look for fault conditions
  //
  switch (State) {
    case CHECK4BATT:
    case CC_CHARGE:
    case CV_CHARGE:
    case TRICKLE:
      DisplayMeasurements();
      if (FastVoltage_mV < SHORT_VOLTAGE_MV) {
        Error();
        CopyLine(BottomLine, "Short/no battery");
      }
      if (FastVoltage_mV > OPEN_VOLTAGE_MV) {
        Error();
        CopyLine(BottomLine, "Open, no battery");
      }
      break;
  }
  //
  // Control the states of the charger and the various charging modes.
  //
  switch (State) {
    case CALIBRATE:
      CopyLine(TopLine, "Calibration mode");
      CopyLine(BottomLine, "00.0V           ");
      DisplayMeasurements();
      break;
    case WAIT4BUTTON:
      CopyLine(TopLine, "Press button to ");
      CopyLine(BottomLine, "  start charging");
      if (BUTTON1_PRESSED) {
        State = CHECK4BATT;
      }
      break;
    case CHECK4BATT:
      State = CC_CHARGE;
      CopyLine(TopLine, "Constant Current");
      CopyLine(BottomLine, StatusLine);
      PWM_Start();
      break;
    case CC_CHARGE:
      if (BattVoltage_mV < MODE1_VOLTAGE_MV) {
        if (BattCurrent_mA < MODE1_CURRENT_MA) {
          PWM_IncreaseDutyCycle();
        } else if (BattCurrent_mA > MODE1_CURRENT_MA) {
          PWM_DecreaseDutyCycle();
        }
      } else {
        State = CV_CHARGE;
        CopyLine(TopLine, "Constant Voltage");
        CopyLine(BottomLine, StatusLine);
      }
      break;
    case CV_CHARGE:
      if (BattCurrent_mA > MODE2_CURRENT_MA) {
        if (BattVoltage_mV < MODE2_VOLTAGE_MV) {
          PWM_IncreaseDutyCycle();
        } else if (BattVoltage_mV > MODE2_VOLTAGE_MV) {
          PWM_DecreaseDutyCycle();
        }
      } else {
        State = TRICKLE;
        CopyLine(TopLine, "Trickle Charge  ");
        CopyLine(BottomLine, StatusLine);
      }
      break;
    case TRICKLE:
      if (BattVoltage_mV < MODE3_VOLTAGE_MV) {
        PWM_IncreaseDutyCycle();
      } else if (BattVoltage_mV > MODE3_VOLTAGE_MV) {
        PWM_DecreaseDutyCycle();
      }
      break;
    case ERROR:
      PWM_Stop();
      CopyLine(TopLine, "Charging stopped");
      break;
  }

  LCD_WriteNextChar();

  Ticks++;
  if (Ticks == TICKS_PER_SEC) Ticks = 0;

  FLAG1_PORT->DATA &= ~FLAG1_Msk;
  return;
}
