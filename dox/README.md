# Introduction

This microcontroller-based battery charger is a prototype for a high-voltage charger that will be used with an experimental electric truck. The prototype was designed to charge a standard 12-volt lead-acid battery, but the voltage and current values are easily changed to support other batteries.

Important features of the charger include:
  - Three-stage operation to quickly and safely recharge the battery
  - Pulse-width modulation control of power electronics
  - LCD character display of charging mode, voltage, current, and temperature
  - Checks for presence of battery before charging begins
  - ARM Cortex-M0 microcontroller (NXP LPC1114)

# Three-stage charging

A 3-stage charging cycle is used to charge the battery as quickly as possible without sacrificing safety or battery life. In the first stage, the charger provides a constant current to the battery. For the prototype software this current is set to 1.8 A. The current sensing circuitry in the prototype can measure currents up to about 3.3 A, so it can support higher charging currents.  The constant-current charging in the first stage continues until the battery voltage reaches 2.4 V per cell, or 14.4 V for a standard 12 V battery.

Once the battery voltage reaches 14.4 V the charger enters the second charging stage, which is constant-voltage charging at 2.4 V per cell. As the battery reaches a fully charged condition the charging current will begin to decrease.  When the charging current falls below 0.1 A the battery is assumed to be fully charged.

The third charging stage, trickle charging, is entered when the charging current falls below 0.1 A during the second, constant-voltage, stage. The charger continues to operate in a constant-voltage mode but the charging voltage is reduced to a lower voltage. This stage is intended to safely maintain the battery in its fully-charged condition, and the battery can be charged indefinitely at this voltage.

# Charger operation

Pressing the __STOP__ button at any time will disable the PWM signal (i.e. set it to a constant logic 0) and return the charger to its initial state.

The user should always press the __STOP__ button before connecting or disconnecting the battery.

## Normal charging
 
The prototype charger is powered from a laptop battery charger that provides 19 V with a maximum current of over 4 A. The charger itself should be powered before it is connected to a battery. When power is first applied to the charger (or when the __STOP__ button is pressed) the LCD will present this message:

    Press button to
      start charging

The charger waits until the __START__ is pressed, and then checks the voltage at the battery terminals to determine if a suitable battery has been connected. If the measured voltage is less than the value specified by SHORT_VOLTAGE_MV (currently 11.0 V) then the charger halts and displays this message:

    Charging stopped
    Short/no battery

If the measured voltage is greater than the value specified by OPEN_VOLTAGE_MV (currently 15.0 V) the charger will halt with this message:

    Charging stopped
    Open, no battery

Once the charger has halted the user must press the __STOP__ button to reset the microcontroller.

If the initial voltage at the battery terminal is between the limits specified by SHORT_VOLTAGE_MV and OPEN_VOLTAGE_MV then the charger enters the first stage of charging and displays:

    Constant Current
    00.0V 0.0A  00 C

where the zeros are replaced with the measured values of voltage, current, and temperature. The duty cycle of the PWM signal is increased slowly until the desired current level is reached, as specified by MODE1_CURRENT_MA (currently 1.8 A). The charger then maintains the charging current at that level until the battery voltage rises to MODE1_VOLTAGE_MV (currently 14.4 V), and at that point the charger transitions to the second, constant-voltage, stage of charging.

In the second stage the PWM duty cycle will be increased or decreased as necessary to maintain the battery voltage at MODE2_VOLTAGE_MV (currently 14.4 V) and the charger displays:

    Constant Voltage
    00.0V 0.0A  00 C

Under normal circumstances the charging current (and thus the PWM duty cycle) will gradually decrease as the battery reaches a fully charged state. When the current falls to the level specified by MODE2_CURRENT_MA (currently 0.1 A) then the charger transitions to the third and final charging stage.

The third stage is also constant-voltage charging but the voltage is reduced to a level that can be safely applied to the battery indefinitely. This voltage is specified by MODE3_VOLTAGE_MV (currently 12.9 V). The charger displays:

    Trickle Charge
    00.0V 0.0A  00 C
 
The charger will remain in the trickle charge stage until the __STOP__ button is pressed.

## Calibration mode

If the __STOP__ button is held down while the __START__ button is pressed and released then the charger enters a calibration mode of operation.  The PWM output is disabled but the charger continues to measure the voltage at the battery terminals. In this mode, the accuracy of the charger's voltage readings can be determined by replacing the battery with an accurate voltage source. The charger displays:

    Calibration Mode
    00.0V

