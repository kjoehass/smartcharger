/**
 * @file LCD.h
 *
 * @brief User interface to the LCD functions and parameters
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-07T08:04:51-0500
 * @date Last modified: 2014-01-12T16:20:18-0500
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
#ifndef _LCD_H
#define _LCD_H

//
// Number of rows and columns in the display, starting from 0
//
#define MAX_ROW 1
#define MAX_COL 15

#define LCD_DATA_Pos   6
#define LCD_DATA_PORT  LPC_GPIO0
#define LCD_CTRL_Pos   1
#define LCD_CTRL_PORT  LPC_GPIO0

// Approximate clock period, nanoseconds
#define CLKPER          20   // LPC1114 runs at 48 MHz

/**
 @def LCD_TAS
 @brief The LCD's required RS/RW-to-EN-asserted setup time (nanoseconds).
 @def LCD_TDS
 @brief The LCD's required Data-to-EN-deasserted setup time (nanoseconds).
 @def LCD_TDA
 @brief The LCD's maximum EN-asserted-to-Data-valid delay (nanoseconds).
 @def LCD_TEH
 @brief The LCD's required minimum EN high time (nanoseconds).
 @def LCD_TEL
 @brief The LCD's required minimum EN low time (nanoseconds).
 */
// For Sparkfun 3.3V display, ADM1602K
#define LCD_TAS        100   // RS, R/W setup before EN rises
#define LCD_TDS         60   // DATA setup before EN falls
#define LCD_TDA         60   // DATA valid after EN rises (reading)
#define LCD_TEH        300   // EN minimum high time
#define LCD_TEL        200   // EN minimum low time

extern char TopLine[MAX_COL+1];
extern char BottomLine[MAX_COL+1];
//
// Initializes the display, should be called just once
//
void LCD_Init(void);
//
// Display the next character, using Row and Col to point to the current
// character position. TopLine and BottomLine contain the text to be displayed.
//
void LCD_WriteNextChar();

#endif
