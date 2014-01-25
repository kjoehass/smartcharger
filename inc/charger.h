/**
 * @file charger.h
 *
 * @brief Configuration parameters for the overall battery charger design.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-07T20:02:08-0500
 * @date Last modified: 2014-01-12T17:50:55-0500
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
#ifndef _CHARGER_H_
#  define _CHARGER_H_

/**
 * @name ADC measurement averaging parameters.
 * @details The voltage and current measurements are averaged over many samples
 * because the measurements are not synchronized to the PWM signal, and they
 * are fairly noisy. For convenience, the averaging is actually done with a
 * moving-average filter. There is a separate filter for battery voltage that
 * has a shorter time constant; this is used for fault detection purposes and
 * we want to react quickly to gross changes in the battery voltage.
 */
/**@{*/
#  define SAMPLES_FAST_AVERAGE 64
#  define SAMPLES_TO_AVERAGE 512
/**@}*/

/**
 * @name Voltage sensing scale factors.
 * @details The scale factor from battery voltage to ADC input voltage is
 * specified using two values, a numerator term (::V_SCALE_NUMERATOR) and a
 * denominator term (::V_SCALE_DENOMINATOR). This
 * is just for convenience, because these values are only used at compile-time
 * to determine the battery voltage, in mV, that corresponds to a full scale
 * ADC reading. It is this value, ::V_MAX_MV, that is used to convert ADC
 * values to actual voltages at run time.
 */
/**@{*/
#  define V_SCALE_NUMERATOR   5000
#  define V_SCALE_DENOMINATOR 1000
#  define V_MAX_MV ((ADC_VREF_MV*V_SCALE_NUMERATOR)/V_SCALE_DENOMINATOR)
/**@}*/

/**
 * @name Current sensing scale factors.
 * @details The scale factor from battery current (in amperes) to ADC input
 * voltage (in volts) is specified using two values, a numerator term
 * (::I_SCALE_NUMERATOR) and a denominator term (::I_SCALE_DENOMINATOR). This
 * is just for convenience, because these values are only used at compile-time
 * to determine the charging current, in mA, that corresponds to a full scale
 * ADC reading. It is this value, ::I_MAX_MA, that is used to convert ADC
 * values to actual voltages at run time.
 */
/**@{*/
#  define I_SCALE_NUMERATOR   1000
#  define I_SCALE_DENOMINATOR 1000
#  define I_MAX_MA ((ADC_VREF_MV*I_SCALE_NUMERATOR)/I_SCALE_DENOMINATOR)
/**@}*/

/**
 * @name Fault detection voltage levels
 * @details The battery voltage is compared to two voltage levels in an attempt
 * to detect whether the battery has been disconnected or the battery terminals
 * have been shorted. These checks are only made while the charger is in a
 * constant-current mode. If the battery voltage is below ::SHORT_VOLTAGE_MV or
 * above ::OPEN_VOLTAGE_MV we assume that there is some kind of fault and shut
 * down the charger.
 */
/**@{*/
#  define SHORT_VOLTAGE_MV 11000
#  define OPEN_VOLTAGE_MV  15000
/**@}*/

/**
 * @name Stage 1 voltage limit and current value
 * These parameters set the current level used for constant-current charging
 * and the voltage level that must be reached (the battery voltage must rise
 * to) in order to advance to the next charging stage.
 */
/**@{*/
#  define MODE1_VOLTAGE_MV 14400
#  define MODE1_CURRENT_MA 1800
/**@}*/

/**
 * @name Stage 2 voltage value and current limit
 * These parameters set the voltage level used for constant-voltage charging
 * and the current level that must be reached (the charging current must fall
 * to) in order to advance to the next charging stage. 
 */
/**@{*/
#  define MODE2_VOLTAGE_MV   14400
#  define MODE2_CURRENT_MA   100
/**@}*/

/**
 * @name Stage 3 voltage value
 * This parameter sets the voltage for trickle charging in stage 3.
 */
/**@{*/
#  define MODE3_VOLTAGE_MV   12900
/**@}*/

/**
 * @name START button connection
 * @details These parameters specify the name of the GPIO port, and the bit
 * position within that port, where the <b>START</b> button is connected. We
 * also define a function macro that returns a boolean true value if the button
 * is being pressed.
 */
/**@{*/
#  define BTN1_PORT          LPC_GPIO1
#  define BTN1_Pos           8
#  define BUTTON1_PRESSED    (~(BTN1_PORT->DATA) & (1uL << BTN1_Pos))
/**@}*/

/**
 * @name Diagnostic output
 * @details These parameters specify the name of a GPIO port, and the bit
 * position within that port, for a diagnostic output pin. A mask value is
 * defined that can be used to set or clear this output pin.
 */
/**@{*/
#  define FLAG1_PORT         LPC_GPIO1
#  define FLAG1_Pos          5
#  define FLAG1_Msk          (1 << FLAG1_Pos)
/**@}*/


enum ChargerState {
  /// The ERROR state will be entered when a fault condition is detected.
  /// The PWM output is disabled. This is a terminal state, and the STOP button
  /// must be pressed to reset the charger after an error.
  ERROR = 0,
  /// If the START button is held down at power-up or when the STOP button
  /// is pressed, the charger will enter the CALIBRATE state. This is a
  /// terminal state.
  CALIBRATE,
  /// If the START button NOT is held down at power-up or when the STOP button
  /// is pressed, the charger will enter the WAIT4BUTTON state. We start
  /// measuring the battery voltage but the PWM is not yet enabled. When the
  /// START button is then pressed the charger goes to the CHECK4BATT state.
  WAIT4BUTTON,
  /// The charger is in the CHECK4BATT state for just one SysTick. The PWM
  /// output is still disabled and the charger just checks the voltage at the
  /// battery terminals. If the voltage is too low or too high then the charger
  /// goes to the ERROR state. If the voltage is within limits the charger goes
  /// to the CC_CHARGE state.
  CHECK4BATT,
  /// The charger state is CC_CHARGE in the first stage of charging. We stay
  /// in this state until the voltage rises to the level specified by
  /// ::MODE1_VOLTAGE_MV and then goes to the CV_CHARGE state. The charger also
  /// checks for a disconnected or shorted battery during this stage.
  CC_CHARGE,
  /// The second stage of charging is the CV_CHARGE state. The charger stays
  /// in this state until the charging current falls below ::MODE2_CURRENT_MA,
  /// then it enters the TRICKLE state.
  CV_CHARGE,
  /// The TRICKLE state is a constant-voltage charging mode with a lower
  /// voltage than that used in the CV_CHARGE state. This is a terminal state,
  /// and the charger and battery can safely remain in this state indefinitely.
  TRICKLE
};

uint32_t State;
uint32_t FastVoltage, RawCurrent, RawVoltage;
uint32_t Temperature;

#endif
