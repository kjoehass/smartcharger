/**
 * @file LCD4.c
 *
 * @brief Functions for configuring the LCD and displaying text.
 *
 * @author K. Joseph Hass
 * @date Created: 2014-01-08T19:21:54-0500
 * @date Last modified: 2014-01-12T17:44:30-0500
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
#include "LCD.h"

/**
 * @var   TopLine
 * @brief Character string that is written to row 0 of the LCD display.
 * @var   BottomLine
 * @brief Character string that is written to row 1 of the LCD display.
 */
char TopLine[MAX_COL+1];
char BottomLine[MAX_COL+1];

/**
 * @var   Row
 * @brief The row number where the next character is written on the LCD.
 * @var   Col
 * @brief The column number where the next character is written on the LCD.
 */
static uint32_t Row;
static uint32_t Col;

/**
 * @def LCD_DATA_Msk
 * @brief A mask for the 4 data bits in the GPIO port.
 * @def LCD_BUSY_FLAG
 * @brief A mask for the MSB of the LCD data bits.
 */
static const uint32_t LCD_DATA_Msk  = 0xF << LCD_DATA_Pos;
static const uint32_t LCD_BUSY_FLAG = 0x8 << LCD_DATA_Pos;

/**
 * @def LCD_CTRL_Msk
 * @brief A mask for the 3 control bits in the GPIO port.
 * @def LCD_RS
 * @brief A mask for the Register Select control bit
 * @details The Register Select bit must be the LSB of the three control bits in
 *   the GPIO port. It is assumed to be at the bit position specified by
 *   ::LCD_CTRL_Pos
 * @def LCD_RW
 * @brief A mask for the Read/Write control bit.
 * @details The Read/Write bit must be to the left of the Register Select bit in
 *   the GPIO port. It is assumed to be at the bit position specified by
 *   ::LCD_CTRL_Pos +1.
 * @def LCD_EN
 * @brief A mask for the Enable control bit.
 * @details The Enable bit must be to the left of the Read/Write bit in
 *   the GPIO port. It is assumed to be at the bit position specified by
 *   ::LCD_CTRL_Pos <tt>+2</tt>, the most significant bit position of the three
 *   control bits.
 */
static const uint32_t LCD_RS       = 1 << LCD_CTRL_Pos;
static const uint32_t LCD_RW       = 1 << (LCD_CTRL_Pos + 1);
static const uint32_t LCD_EN       = 1 << (LCD_CTRL_Pos + 2);
static const uint32_t LCD_CTRL_Msk = 0x7 << LCD_CTRL_Pos ;

/**
 * @def DELAY_RS_EN
 * @brief The LCD's required RS/RW-to-EN-asserted setup time (clock cycles).
 * @def DELAY_DA_EN
 * @brief The LCD's required Data-to-EN-deasserted setup time (clock cycles).
 * @def DELAY_EN_DA
 * @brief The LCD's maximum EN-asserted-to-Data-valid delay (clock cycles).
 * @def DELAY_EN_HIGH
 * @brief The LCD's required minimum EN high time (clock cycles).
 * @def DELAY_EN_HIGH
 * @brief The LCD's required minimum EN low time (clock cycles).
 */
static const uint32_t DELAY_RS_EN    = LCD_TAS/CLKPER;
static const uint32_t DELAY_DA_EN    = LCD_TDS/CLKPER;
static const uint32_t DELAY_EN_DA    = LCD_TDA/CLKPER;
static const uint32_t DELAY_EN_HIGH  = LCD_TEH/CLKPER;
static const uint32_t DELAY_EN_LOW   = LCD_TEL/CLKPER;

/**
  @private
  @brief A crude delay time for short delays.
  @details Execute the processor's NOP instruction in a tight loop.

  @param[in] count number of loop executions
 */
void delay(int count)
{
  for (int i = 0; i < count; i++)
    __NOP();
}
/**
 * @private
 * @brief Busy-wait until the LCD display is not busy.
 * @details The busy flag from the LCD is on the same pin as the MSB of the
 * data, so first we change the direction of that GPIO bit to an input.
 * We set the Read/Write control to the read mode, wait a bit, then enable
 * the LCD.
 *
 * A tight loop reads the data from the LCD until the busy flag goes low.
 *
 * Finally, the LCD is disabled and then the Read/Write control is set to
 * the write mode. The direction of the busy flag is changed back to an
 * input. Since we have just deasserted the LCD enable signal we wait a bit
 * to make sure we satisfy the low time requirement for this signal.
 *
 */
void Wait_LCD(void)
{
  //
  // Make the BUSY flag an input, set control bits for READ, ENABLE
  //
  LCD_DATA_PORT->DIR &= ~LCD_BUSY_FLAG;
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RW;
  delay(DELAY_RS_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RW | LCD_EN;
  delay(DELAY_EN_DA);
  //
  // Wait for BUSY to be deasserted
  //
  while (LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] & LCD_BUSY_FLAG);
  //
  // Disable control bits, change BUSY back to an output
  //
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RW;
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  LCD_DATA_PORT->DIR |= LCD_DATA_Msk;

  delay(DELAY_EN_LOW);
}
/**
 * @private
 * @brief Writes a command byte to the LCD using the 4-bit interface.
 *
 * @note Access to the GPIO data registers uses the "masked access" capability
 * of the LPC GPIO ports, so there is no need to explicitly mask bits when
 * writing to the ports.
 *
 * @param[in] command the command byte
 */
void LCD_WriteCommandNoWait(uint8_t command)
{
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_RS_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_DA);
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = (command >> 4) << LCD_DATA_Pos;
  delay(DELAY_DA_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);

  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_DA);
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = command << LCD_DATA_Pos;
  delay(DELAY_DA_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
}
/**
 * @private
 * @brief Writes a data (character) byte to the LCD using the 4-bit interface.
 *
 * @note Access to the GPIO data registers uses the "masked access" capability
 * of the LPC GPIO ports, so there is no need to explicitly mask bits when
 * writing to the ports.
 *
 * @param[in] data the ASCII character to display
 */
void LCD_WriteDataNoWait(uint8_t data)
{
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RS;
  delay(DELAY_RS_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RS | LCD_EN;
  delay(DELAY_EN_DA);
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = (data >> 4) << LCD_DATA_Pos;
  delay(DELAY_DA_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RS;
  delay(DELAY_EN_LOW);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RS | LCD_EN;
  delay(DELAY_EN_DA);
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = data << LCD_DATA_Pos;
  delay(DELAY_DA_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_RS;
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
}
/**
 * @brief Writes the next character to the LCD.
 * 
 * @details The characters in the two display strings, ::TopLine and ::BottomLine, are
 * written to the LCD. One character is written each time this function is
 * called, except when changing from one row to the other when a command byte
 * is written instead. The local variables Row and Col are used to keep
 * track of the next location that should be written to.
 * 
 * @warning
 * This function does not check the BUSY flag from the LCD. There must be a
 * time greater than the longest LCD command execution time between calls of
 * this function.
 */
void LCD_WriteNextChar()
{
  if (Col > MAX_COL) {
    Col = 0;
    if ((0 == Row) && (1 == MAX_ROW)) {
      Row = 1;
      LCD_WriteCommandNoWait(0xC0);
    } else {
      Row = 0;
      LCD_WriteCommandNoWait(0x80);
    }
  } else {
    if (0 == Row)
      LCD_WriteDataNoWait(TopLine[Col]);
    else
      LCD_WriteDataNoWait(BottomLine[Col]);
    Col++;
  }
}
/**
 * @brief Initialize the LCD display.
 * @details Begin by changing the direction of the GPIO lines that connect to
 * the LCD control/data pins to outputs.
 *
 * The LCD wakes up in 8-bit data mode but we will eventually configure it for
 * a 4-bit data mode. The least-significant 4 bits of the LCD's data byte are
 * hardwired to ground, so while in the 8-bit mode we can only use commands
 * that have zeros in the bottom 4 bits.
 *
 * The reset command (<tt>0x30</tt>) is sent to the LCD three times. After the
 * top 4 command bits are written to the 4 GPIO data pins, the LCD enable pin
 * is asserted for a short time and then deasserted. After each pulse on the
 * enable pin we wait for the LCD's busy flag to be deasserted.
 *
 * After reset the LCD is configured for a 4-bit interface, but the command
 * that does this (<tt>0x20</tt>) is still an 8-bit command.
 *
 * Once the LCD is in 4-bit mode we can start using commands that have non-zero
 * values for the lower 4 bits. This is accomplished by first writing the upper
 * nibble of the command and then writing the lower nibble of the command. A
 * sequence of commands is issued to:
 *   - Configure the LCD for two rows of characters, each with 5x7 pixels
 *   - Clear the display and move the cursor to the first character position
 *   - Set the entry mode to automatically increment the character position
 *     after each character is written to the display
 *   - Turn on the display and make the cursor visible
 *
 * @note Access to the GPIO data registers uses the "masked access" capability
 * of the LPC GPIO ports, so there is no need to explicitly mask bits when
 * writing to the ports.
 */
void LCD_Init(void)
{
  // Set pins to outputs
  LCD_CTRL_PORT->DIR |= (LCD_EN | LCD_RS | LCD_RW);
  LCD_DATA_PORT->DIR |= LCD_DATA_Msk;
  // Send reset command to LCD in 8-bit mode
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = 0x3 << LCD_DATA_Pos;
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_RS_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_HIGH);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
  Wait_LCD();
  // Send reset command to LCD in 8-bit mode (second time)
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_HIGH);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
  Wait_LCD();
  // Send reset command to LCD in 8-bit mode (third time)
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_HIGH);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
  Wait_LCD();

  // Send command to change LCD to 4-bit interface
  LCD_DATA_PORT->MASKED_ACCESS[LCD_DATA_Msk] = 0x2 << LCD_DATA_Pos;
  delay(DELAY_RS_EN);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = LCD_EN;
  delay(DELAY_EN_HIGH);
  LCD_CTRL_PORT->MASKED_ACCESS[LCD_CTRL_Msk] = 0;
  delay(DELAY_EN_LOW);
  Wait_LCD();

  LCD_WriteCommandNoWait(0x28); // 4-bit interface, 2 row, 5x7 char
  Wait_LCD();
  LCD_WriteCommandNoWait(0x01); // clear display, cursor home
  Wait_LCD();
  LCD_WriteCommandNoWait(0x06); // Entry mode: Increment, Shift off
  Wait_LCD();
  LCD_WriteCommandNoWait(0x0F); // display on, cursor on
  Wait_LCD();
}
