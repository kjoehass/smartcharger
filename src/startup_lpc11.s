@ Startup file for LPC1343 assembly programming
@ Compatible with GNU as assembler
@
@ 17 Jul 2012 Changed global symbol names in crt code to agree with
@             those used in gcc_arm.ld
@
@ APB peripherals
@
  .equ APB_BASE, 0x40000000
@
@ APB->I2C bus
@
  .equ I2C_BASE,        APB_BASE+0x00000
  .equ I2C0CONSET,      I2C_BASE+0x000 @R/W Control Set Register
  .equ I2C0STAT,        I2C_BASE+0x004 @R   Status Register
  .equ I2C0DAT,         I2C_BASE+0x008 @R/W Data Register
  .equ I2C0ADR0,        I2C_BASE+0x00C @R/W Slave Address Register 0
  .equ I2C0SCLH,        I2C_BASE+0x010 @R/W SCH Duty Cycle Register High Half Word
  .equ I2C0SCLL,        I2C_BASE+0x014 @R/W SCH Duty Cycle Register Low Half Word
  .equ I2C0CONCLR,      I2C_BASE+0x018 @W   Control Clear Register
  .equ I2C0MMCTRL,      I2C_BASE+0x01C @R/W Monitor Mode Control Register
  .equ I2C0ADR1,        I2C_BASE+0x020 @R/W Slave Address Register 1
  .equ I2C0ADR2,        I2C_BASE+0x024 @R/W Slave Address Register 2
  .equ I2C0ADR3,        I2C_BASE+0x028 @R/W Slave Address Register 3
  .equ I2C0DATA_BUFFER, I2C_BASE+0x02C @R   Data Buffer Register
  .equ I2C0MASK0,       I2C_BASE+0x030 @R/W Slave Address Mask Register 0
  .equ I2C0MASK1,       I2C_BASE+0x034 @R/W Slave Address Mask Register 1
  .equ I2C0MASK2,       I2C_BASE+0x038 @R/W Slave Address Mask Register 2
  .equ I2C0MASK3,       I2C_BASE+0x03C @R/W Slave Address Mask Register 3
  .global I2C_BASE,I2C0CONSET,I2C0STAT,I2C0DAT,I2C0ADR0,I2C0SCLH
  .global I2C0SCLL,I2C0CONCLR,I2C0MMCTRL,I2C0ADR1,I2C0ADR2,I2C0ADR3
  .global I2C0DATA_BUFFER,I2C0MASK0,I2C0MASK1,I2C0MASK2,I2C0MASK3
@
@ APB->Watchdog Timer
@
  .equ WDT_BASE, APB_BASE+0x04000
  .equ WDMOD,    WDT_BASE+0x000 @R/W Watchdog mode register
  .equ WDTC,     WDT_BASE+0x004 @R/W Watchdog timer constant register
  .equ WDFEED,   WDT_BASE+0x008 @W   Watchdog feed sequence register
  .equ WDTV,     WDT_BASE+0x00C @R   Watchdog timer value register
  .equ WDWARNINT,WDT_BASE+0x014 @R/W Watchdog warning int. register
  .equ WDWINDOW, WDT_BASE+0x018 @R/W Watchdog window value register
  .global WDT_BASE,WDMOD,WDTC,WDFEED,WDTV,WDWARNINT,WDWINDOW
@
@ APB->UART
@ Note that several registers have different functions depending on the
@   state of the DLAB bit, which is bit 7 in U0LCR
@
  .equ UART_BASE,   APB_BASE+0x08000
  .equ U0RBR,       UART_BASE+0x000 @ R   Receive Buffer Register when DLAB=0
  .equ U0THR,       UART_BASE+0x000 @ W   Transmit Holding Register when DLAB=0
  .equ U0DLL,       UART_BASE+0x000 @ R/W Divisor Latch LSB when DLAB=1
  .equ U0DLM,       UART_BASE+0x004 @ R/W Divisor Latch MSB when DLAB=1
  .equ U0IER,       UART_BASE+0x004 @ R/W Interrupt Enable Register when DLAB=0
  .equ U0IIR,       UART_BASE+0x008 @ R   Interrupt ID Register
  .equ U0FCR,       UART_BASE+0x008 @ W   FIFO Control Register
  .equ U0LCR,       UART_BASE+0x00C @ R/W Line Control Register
  .equ U0MCR,       UART_BASE+0x010 @ R/W Modem Control Register
  .equ U0LSR,       UART_BASE+0x014 @ R   Line Status Register
  .equ U0MSR,       UART_BASE+0x018 @ R   Modem Status Register
  .equ U0SCR,       UART_BASE+0x01C @ R/W Scratchpad Register
  .equ U0ACR,       UART_BASE+0x020 @ R/W Autobaud Control Register
  .equ U0FDR,       UART_BASE+0x028 @ R/W Fractional Divider Register
  .equ U0TER,       UART_BASE+0x030 @ R/W Transmit Enable Register
  .equ U0RS485CTRL, UART_BASE+0x04C @ R/W RS-485 Control
  .equ U0ADRMATCH,  UART_BASE+0x050 @ R/W RS-485 Address Match
  .equ U0RS485DLY,  UART_BASE+0x054 @ R/W RS-485 Direction control delay
  .equ U0FIFOLVL,   UART_BASE+0x058 @ R   FIFO Level Register
  .global UART_BASE,U0RBR,U0THR,U0DLL,U0DLM,U0IER,U0IER,U0FCR,U0LCR,U0MCR,U0LSR,U0MSR,U0SCR
  .global U0ACR,U0FDR,U0TER,U0RS485CTRL,U0ADRMATCH,U0RS485DLY,U0FIFOLVL
@
@ APB->16-bit Timer/Counter 0
@
  .equ TMR16B0_BASE, APB_BASE+0x0C000
  .equ TMR16B0IR,   TMR16B0_BASE+0x000 @R/W Interrupt Register 
  .equ TMR16B0TCR,  TMR16B0_BASE+0x004 @R/W Timer Control Register 
  .equ TMR16B0TC,   TMR16B0_BASE+0x008 @R/W Timer Counter 
  .equ TMR16B0PR,   TMR16B0_BASE+0x00C @R/W Prescale Register 
  .equ TMR16B0PC,   TMR16B0_BASE+0x010 @R/W Prescale Counter 
  .equ TMR16B0MCR,  TMR16B0_BASE+0x014 @R/W Match Control Register 
  .equ TMR16B0MR0,  TMR16B0_BASE+0x018 @R/W Match Register 0 
  .equ TMR16B0MR1,  TMR16B0_BASE+0x01C @R/W Match Register 1 
  .equ TMR16B0MR2,  TMR16B0_BASE+0x020 @R/W Match Register 2 
  .equ TMR16B0MR3,  TMR16B0_BASE+0x024 @R/W Match Register 3 
  .equ TMR16B0CCR,  TMR16B0_BASE+0x028 @R/W Capture Control Register 
  .equ TMR16B0CR0,  TMR16B0_BASE+0x02C @R   Capture Register 0 
  .equ TMR16B0EMR,  TMR16B0_BASE+0x03C @R/W External Match Register 
  .equ TMR16B0CTCR, TMR16B0_BASE+0x070 @R/W Count Control Register 
  .equ TMR16B0PWMC, TMR16B0_BASE+0x074 @R/W PWM Control Register 
  .global TMR16B0_BASE,TMR16B0IR,TMR16B0TCR,TMR16B0TC,TMR16B0PR,TMR16B0PC
  .global TMR16B0MCR,TMR16B0MR0,TMR16B0MR1,TMR16B0MR2,TMR16B0MR3
  .global TMR16B0CCR,TMR16B0CR0,TMR16B0EMR,TMR16B0CTCR,TMR16B0PWMC
@
@ APB->16-bit Timer/Counter 1
@
  .equ TMR16B1_BASE, APB_BASE+0x10000
  .equ TMR16B1IR,   TMR16B1_BASE+0x000 @R/W Interrupt Register 
  .equ TMR16B1TCR,  TMR16B1_BASE+0x004 @R/W Timer Control Register 
  .equ TMR16B1TC,   TMR16B1_BASE+0x008 @R/W Timer Counter 
  .equ TMR16B1PR,   TMR16B1_BASE+0x00C @R/W Prescale Register 
  .equ TMR16B1PC,   TMR16B1_BASE+0x010 @R/W Prescale Counter 
  .equ TMR16B1MCR,  TMR16B1_BASE+0x014 @R/W Match Control Register 
  .equ TMR16B1MR0,  TMR16B1_BASE+0x018 @R/W Match Register 0 
  .equ TMR16B1MR1,  TMR16B1_BASE+0x01C @R/W Match Register 1 
  .equ TMR16B1MR2,  TMR16B1_BASE+0x020 @R/W Match Register 2 
  .equ TMR16B1MR3,  TMR16B1_BASE+0x024 @R/W Match Register 3 
  .equ TMR16B1CCR,  TMR16B1_BASE+0x028 @R/W Capture Control Register 
  .equ TMR16B1CR0,  TMR16B1_BASE+0x02C @R   Capture Register 0 
  .equ TMR16B1EMR,  TMR16B1_BASE+0x03C @R/W External Match Register 
  .equ TMR16B1CTCR, TMR16B1_BASE+0x070 @R/W Count Control Register 
  .equ TMR16B1PWMC, TMR16B1_BASE+0x074 @R/W PWM Control Register 
  .global TMR16B1_BASE,TMR16B1IR,TMR16B1TCR,TMR16B1TC,TMR16B1PR,TMR16B1PC
  .global TMR16B1MCR,TMR16B1MR0,TMR16B1MR1,TMR16B1MR2,TMR16B1MR3
  .global TMR16B1CCR,TMR16B1CR0,TMR16B1EMR,TMR16B1CTCR,TMR16B1PWMC
@
@ APB->32-bit Timer/Counter 0
@
  .equ TMR32B0_BASE, APB_BASE+0x14000
  .equ TMR32B0IR,   TMR32B0_BASE+0x000 @R/W Interrupt Register 
  .equ TMR32B0TCR,  TMR32B0_BASE+0x004 @R/W Timer Control Register 
  .equ TMR32B0TC,   TMR32B0_BASE+0x008 @R/W Timer Counter 
  .equ TMR32B0PR,   TMR32B0_BASE+0x00C @R/W Prescale Register 
  .equ TMR32B0PC,   TMR32B0_BASE+0x010 @R/W Prescale Counter 
  .equ TMR32B0MCR,  TMR32B0_BASE+0x014 @R/W Match Control Register 
  .equ TMR32B0MR0,  TMR32B0_BASE+0x018 @R/W Match Register 0 
  .equ TMR32B0MR1,  TMR32B0_BASE+0x01C @R/W Match Register 1 
  .equ TMR32B0MR2,  TMR32B0_BASE+0x020 @R/W Match Register 2 
  .equ TMR32B0MR3,  TMR32B0_BASE+0x024 @R/W Match Register 3 
  .equ TMR32B0CCR,  TMR32B0_BASE+0x028 @R/W Capture Control Register 
  .equ TMR32B0CR0,  TMR32B0_BASE+0x02C @R   Capture Register 0 
  .equ TMR32B0EMR,  TMR32B0_BASE+0x03C @R/W External Match Register 
  .equ TMR32B0CTCR, TMR32B0_BASE+0x070 @R/W Count Control Register 
  .equ TMR32B0PWMC, TMR32B0_BASE+0x074 @R/W PWM Control Register 
  .global TMR32B0_BASE,TMR32B0IR,TMR32B0TCR,TMR32B0TC,TMR32B0PR,TMR32B0PC
  .global TMR32B0MCR,TMR32B0MR0,TMR32B0MR1,TMR32B0MR2,TMR32B0MR3
  .global TMR32B0CCR,TMR32B0CR0,TMR32B0EMR,TMR32B0CTCR,TMR32B0PWMC
@
@ APB->32-bit Timer/Counter 1
@
  .equ TMR32B1_BASE, APB_BASE+0x18000
  .equ TMR32B1IR,   TMR32B1_BASE+0x000 @R/W Interrupt Register
  .equ TMR32B1TCR,  TMR32B1_BASE+0x004 @R/W Timer Control Register
  .equ TMR32B1TC,   TMR32B1_BASE+0x008 @R/W Timer Counter
  .equ TMR32B1PR,   TMR32B1_BASE+0x00C @R/W Prescale Register
  .equ TMR32B1PC,   TMR32B1_BASE+0x010 @R/W Prescale Counter
  .equ TMR32B1MCR,  TMR32B1_BASE+0x014 @R/W Match Control Register
  .equ TMR32B1MR0,  TMR32B1_BASE+0x018 @R/W Match Register 0
  .equ TMR32B1MR1,  TMR32B1_BASE+0x01C @R/W Match Register 1
  .equ TMR32B1MR2,  TMR32B1_BASE+0x020 @R/W Match Register 2
  .equ TMR32B1MR3,  TMR32B1_BASE+0x024 @R/W Match Register 3
  .equ TMR32B1CCR,  TMR32B1_BASE+0x028 @R/W Capture Control Register
  .equ TMR32B1CR0,  TMR32B1_BASE+0x02C @R   Capture Register 0
  .equ TMR32B1EMR,  TMR32B1_BASE+0x03C @R/W External Match Register
  .equ TMR32B1CTCR, TMR32B1_BASE+0x070 @R/W Count Control Register
  .equ TMR32B1PWMC, TMR32B1_BASE+0x074 @R/W PWM Control Register
  .global TMR32B1_BASE,TMR32B1IR,TMR32B1TCR,TMR32B1TC,TMR32B1PR,TMR32B1PC
  .global TMR32B1MCR,TMR32B1MR0,TMR32B1MR1,TMR32B1MR2,TMR32B1MR3
  .global TMR32B1CCR,TMR32B1CR0,TMR32B1EMR,TMR32B1CTCR,TMR32B1PWMC
@
@ APB->Analog-to-digital converter
@
  .equ ADC_BASE, APB_BASE+0x1C000
  .equ AD0CR,    ADC_BASE+0x000 @R/W A/D Control Register
  .equ AD0GDR,   ADC_BASE+0x004 @R/W A/D Global Data Register
  .equ AD0INTEN, ADC_BASE+0x00C @R/W A/D Interrupt Enable Register
  .equ AD0DR0,   ADC_BASE+0x010 @R/W A/D Channel 0 Data Register
  .equ AD0DR1,   ADC_BASE+0x014 @R/W A/D Channel 1 Data Register
  .equ AD0DR2,   ADC_BASE+0x018 @R/W A/D Channel 2 Data Register
  .equ AD0DR3,   ADC_BASE+0x01C @R/W A/D Channel 3 Data Register
  .equ AD0DR4,   ADC_BASE+0x020 @R/W A/D Channel 4 Data Register
  .equ AD0DR5,   ADC_BASE+0x024 @R/W A/D Channel 5 Data Register
  .equ AD0DR6,   ADC_BASE+0x028 @R/W A/D Channel 6 Data Register
  .equ AD0DR7,   ADC_BASE+0x02C @R/W A/D Channel 7 Data Register
  .equ AD0STAT,  ADC_BASE+0x030 @R   A/D Status Register
  .global ADC_BASE,AD0CR,AD0GDR,AD0INTEN,AD0DR0,AD0DR1,AD0DR2,AD0DR3
  .global AD0DR4,AD0DR5,AD0DR6,AD0DR7,AD0STAT
@
@ APB->PMU
@
  .equ PMU_BASE, APB_BASE+0x38000
  .equ PCON,     PMU_BASE+0x000 @R/W Power control register
  .equ GPREG0,   PMU_BASE+0x004 @R/W General purpose register 0
  .equ GPREG1,   PMU_BASE+0x008 @R/W General purpose register 1
  .equ GPREG2,   PMU_BASE+0x00C @R/W General purpose register 2
  .equ GPREG3,   PMU_BASE+0x010 @R/W General purpose register 3
  .equ GPREG4,   PMU_BASE+0x014 @R/W General purpose register 4
  .global PMU_BASE,PCON,GPREG0,GPREG1,GPREG2,GPREG3,GPREG4
@
@ APB->Flash Controller
@
  .equ FLSH_BASE,  APB_BASE+0x3C000
  .equ FLASHCFG,   FLSH_BASE+0xC010 @ Flash memory access time configuration register
  .equ FMSSTART,   FLSH_BASE+0xC020 @ Signature start address register
  .equ FMSSTOP,    FLSH_BASE+0xC024 @ Signature stop-address register
  .equ FMSW0,      FLSH_BASE+0xC02C @ Word 0 [31:0]
  .equ FMSW1,      FLSH_BASE+0xC030 @ Word 1 [63:32]
  .equ FMSW2,      FLSH_BASE+0xC034 @ Word 2 [95:64]
  .equ FMSW3,      FLSH_BASE+0xC038 @ Word 3 [127:96]
  .equ FMSTAT,     FLSH_BASE+0xCFE0 @ Signature generation status register
  .equ FMSTATCLR,  FLSH_BASE+0xCFE8 @ Signature generation status clear r
  .global FLASHCFG,MSSTART,MSSTOP,MSW0,MSW1,MSW2,MSW3,MSTAT,MSTATCLR,
@
@ APB->SSP0
@
  .equ SSP0_BASE, APB_BASE+0x40000
  .equ SSP0CR0,   SSP0_BASE+0x000 @R/W Control Register 0
  .equ SSP0CR1,   SSP0_BASE+0x004 @R/W Control Register 1
  .equ SSP0DR,    SSP0_BASE+0x008 @R/W Data Register
  .equ SSP0SR,    SSP0_BASE+0x00C @R   Status Register
  .equ SSP0CPSR,  SSP0_BASE+0x010 @R/W Clock Prescale Register
  .equ SSP0IMSC,  SSP0_BASE+0x014 @R/W Interrupt Mask Set and Clear Register
  .equ SSP0RIS,   SSP0_BASE+0x018 @R   Raw Interrupt Status Register
  .equ SSP0MIS,   SSP0_BASE+0x01C @R   Masked Interrupt Status Register
  .equ SSP0ICR,   SSP0_BASE+0x020 @W   SSPICR Interrupt Clear Register
  .global SSP0_BASE,SSP0CR0,SSP0CR1,SSP0DR,SSP0SR,SSP0CPSR,SSP0IMSC,SSP0RIS,SSP0MIS,SSP0ICR
@
@ APB->IOCONFIG
@
  .equ IO_BASE,             APB_BASE+0x44000
  .equ IOCON_PIO2_6,        IO_BASE+0x000 @I/O config, pin PIO2_6 
  .equ IOCON_PIO2_0,        IO_BASE+0x008 @I/O config, pin PIO2_0/DTR/SSEL1 
  .equ IOCON_RESET_PIO0_0,  IO_BASE+0x00C @I/O config, pin RESET/PIO0_0  
  .equ IOCON_PIO0_1,        IO_BASE+0x010 @I/O config, pin PIO0_1/CLKOUT/CT32B0_MAT2 
  .equ IOCON_PIO1_8,        IO_BASE+0x014 @I/O config, pin PIO1_8/CT16B1_CAP0 
  .equ IOCON_PIO0_2,        IO_BASE+0x01C @I/O config, pin PIO0_2/SSEL0/CT16B0_CAP0 
  .equ IOCON_PIO2_7,        IO_BASE+0x020 @I/O config, pin PIO2_7 
  .equ IOCON_PIO2_8,        IO_BASE+0x024 @I/O config, pin PIO2_8 
  .equ IOCON_PIO2_1,        IO_BASE+0x028 @I/O config, pin PIO2_1/nDSR/SCK1 
  .equ IOCON_PIO0_3,        IO_BASE+0x02C @I/O config, pin PIO0_3 
  .equ IOCON_PIO0_4,        IO_BASE+0x030 @I/O config, pin PIO0_4/SCL 
  .equ IOCON_PIO0_5,        IO_BASE+0x034 @I/O config, pin PIO0_5/SDA 
  .equ IOCON_PIO1_9,        IO_BASE+0x038 @I/O config, pin PIO1_9/CT16B1_MAT0 
  .equ IOCON_PIO3_4,        IO_BASE+0x03C @I/O config, pin PIO3_4 
  .equ IOCON_PIO2_4,        IO_BASE+0x040 @I/O config, pin PIO2_4 
  .equ IOCON_PIO2_5,        IO_BASE+0x044 @I/O config, pin PIO2_5 
  .equ IOCON_PIO3_5,        IO_BASE+0x048 @I/O config, pin PIO3_5 
  .equ IOCON_PIO0_6,        IO_BASE+0x04C @I/O config, pin PIO0_6/SCK0 
  .equ IOCON_PIO0_7,        IO_BASE+0x050 @I/O config, pin PIO0_7/nCTS 
  .equ IOCON_PIO2_9,        IO_BASE+0x054 @I/O config, pin PIO2_9 
  .equ IOCON_PIO2_10,       IO_BASE+0x058 @I/O config, pin PIO2_10 
  .equ IOCON_PIO2_2,        IO_BASE+0x05C @I/O config, pin PIO2_2/DCD/MISO1 
  .equ IOCON_PIO0_8,        IO_BASE+0x060 @I/O config, pin PIO0_8/MISO0/CT16B0_MAT0 
  .equ IOCON_PIO0_9,        IO_BASE+0x064 @I/O config, pin PIO0_9/MOSI0/CT16B0_MAT1 
  .equ IOCON_SWCLK_PIO0_10, IO_BASE+0x068 @I/O config, pin SWCLK/PIO0_10/SCK0/CT16B0_MAT2 
  .equ IOCON_PIO1_10,       IO_BASE+0x06C @I/O config, pin PIO1_10/AD6/CT16B1_MAT1 
  .equ IOCON_PIO2_11,       IO_BASE+0x070 @I/O config, pin PIO2_11/SCK0 
  .equ IOCON_R_PIO0_11,     IO_BASE+0x074 @I/O config, pin TDI/PIO0_11/AD0/CT32B0_MAT3 
  .equ IOCON_R_PIO1_0,      IO_BASE+0x078 @I/O config, pin TMS/PIO1_0/AD1/CT32B1_CAP0 
  .equ IOCON_R_PIO1_1,      IO_BASE+0x07C @I/O config, pin TDO/PIO1_1/AD2/CT32B1_MAT0 
  .equ IOCON_R_PIO1_2,      IO_BASE+0x080 @I/O config, pin nTRST/PIO1_2/AD3/CT32B1_MAT1 
  .equ IOCON_PIO3_0,        IO_BASE+0x084 @I/O config, pin PIO3_0/nDTR 
  .equ IOCON_PIO3_1,        IO_BASE+0x088 @I/O config, pin PIO3_1/nDSR 
  .equ IOCON_PIO2_3,        IO_BASE+0x08C @I/O config, pin PIO2_3/RI/MOSI1 
  .equ IOCON_SWDIO_PIO1_3,  IO_BASE+0x090 @I/O config, pin SWDIO/PIO1_3/AD4/CT32B1_MAT2 
  .equ IOCON_PIO1_4,        IO_BASE+0x094 @I/O config, pin PIO1_4/AD5/CT32B1_MAT3 
  .equ IOCON_PIO1_11,       IO_BASE+0x098 @I/O config, pin PIO1_11/AD7 
  .equ IOCON_PIO3_2,        IO_BASE+0x09C @I/O config, pin PIO3_2/nDCD 
  .equ IOCON_PIO1_5,        IO_BASE+0x0A0 @I/O config, pin PIO1_5/nRTS/CT32B0_CAP0 
  .equ IOCON_PIO1_6,        IO_BASE+0x0A4 @I/O config, pin PIO1_6/RXD/CT32B0_MAT0 
  .equ IOCON_PIO1_7,        IO_BASE+0x0A8 @I/O config, pin PIO1_7/TXD/CT32B0_MAT1 
  .equ IOCON_PIO3_3,        IO_BASE+0x0AC @I/O config, pin PIO3_3/nRI 
  .equ IOCON_SCK_LOC,       IO_BASE+0x0B0 @SCK pin location select Register 
  .equ IOCON_DSR_LOC,       IO_BASE+0x0B4 @DSR pin location select Register 
  .equ IOCON_DCD_LOC,       IO_BASE+0x0B8 @DCD pin location select Register 
  .equ IOCON_RI_LOC,        IO_BASE+0x0BC @RI pin location Register 
  .global IOCON_PIO2_6,IOCON_PIO2_0,IOCON_RESET_PIO0_0,PIO0_1,IOCON_PIO1_8
  .global IOCON_PIO0_2,IOCON_PIO2_7,IOCON_PIO2_8,PIO2_1,IOCON_PIO0_3
  .global IOCON_PIO0_4,IOCON_PIO0_5,IOCON_PIO1_9,PIO3_4,IOCON_PIO2_4
  .global IOCON_PIO2_5,IOCON_PIO3_5,IOCON_PIO0_6,PIO0_7,IOCON_PIO2_9
  .global IOCON_PIO2_10,IOCON_PIO2_2,IOCON_PIO0_8,PIO0_9
  .global IOCON_SWCLK_PIO0_10,IOCON_PIO1_10,IOCON_PIO2_11,R_PIO0_11
  .global IOCON_R_PIO1_0,IOCON_R_PIO1_1,IOCON_R_PIO1_2,PIO3_0
  .global IOCON_PIO3_1,IOCON_PIO2_3,IOCON_SWDIO_PIO1_3,PIO1_4
  .global IOCON_PIO1_11,IOCON_PIO3_2,IOCON_PIO1_5,IOCON_PIO1_6,PIO1_7
  .global IOCON_PIO3_3,IOCON_SCK_LOC,IOCON_DSR_LOC,DCD_LOC,IOCON_RI_LOC
@
@ APB->System Control
@
  .equ SYS_BASE,      APB_BASE+0x48000
  .equ SYSMEMREMAP,   SYS_BASE+0x000 @R/W System memory remap
  .equ PRESETCTRL,    SYS_BASE+0x004 @R/W Peripheral reset control
  .equ SYSPLLCTRL,    SYS_BASE+0x008 @R/W System PLL control
  .equ SYSPLLSTAT,    SYS_BASE+0x00C @R   System PLL status
  .equ SYSOSCCTRL,    SYS_BASE+0x020 @R/W System oscillator control
  .equ WDTOSCCTRL,    SYS_BASE+0x024 @R/W Watchdog oscillator control
  .equ IRCCTRL,       SYS_BASE+0x028 @R/W IRC control
  .equ SYSRESSTAT,    SYS_BASE+0x030 @R   System reset status register
  .equ SYSRSTSTAT,    SYS_BASE+0x030
  .equ SYSPLLCLKSEL,  SYS_BASE+0x040 @R/W System PLL clock source select
  .equ SYSPLLCLKUEN,  SYS_BASE+0x044 @R/W System PLL clock source update enable
  .equ MAINCLKSEL,    SYS_BASE+0x070 @R/W Main clock source select
  .equ MAINCLKUEN,    SYS_BASE+0x074 @R/W Main clock source update enable
  .equ SYSAHBCLKDIV,  SYS_BASE+0x078 @R/W System AHB clock divider
  .equ SYSAHBCLKCTRL, SYS_BASE+0x080 @R/W System AHB clock control
  .equ SSP0CLKDIV,    SYS_BASE+0x094 @R/W SSP0 clock divder
  .equ UARTCLKDIV,    SYS_BASE+0x098 @R/W UART clock divder
  .equ SSP1CLKDIV,    SYS_BASE+0x09C @R/W SSP1 clock divder
  .equ WDTCLKSEL,     SYS_BASE+0x0D0 @R/W WDT clock source select
  .equ WDTCLKUEN,     SYS_BASE+0x0D4 @R/W WDT clock source update enable
  .equ WDTCLKDIV,     SYS_BASE+0x0D8 @R/W WDT clock divider
  .equ CLKOUTCLKSEL,  SYS_BASE+0x0E0 @R/W CLKOUT clock source select
  .equ CLKOUTUEN,     SYS_BASE+0x0E4 @R/W CLKOUT clock source update enable
  .equ CLKOUTDIV,     SYS_BASE+0x0E8 @R/W CLKOUT clock divider
  .equ PIOPORCAP0,    SYS_BASE+0x100 @R   POR captured PIO status 0
  .equ PIOPORCAP1,    SYS_BASE+0x104 @R   POR captured PIO status 1
  .equ BODCTRL,       SYS_BASE+0x150 @R/W BOD control
  .equ SYSTCKCAL,     SYS_BASE+0x154 @R/W System tick counter calibration
  .equ NMISRC,        SYS_BASE+0x174 @R/W NMI source selection
  .equ STARTAPRP0,    SYS_BASE+0x200 @R/W Start logic edge control register 0; bottom 32 interrupts
  .equ STARTERP0,     SYS_BASE+0x204 @R/W Start logic signal enable register 0; bottom 32 interrupts
  .equ STARTRSRP0CLR, SYS_BASE+0x208 @W   Start logic reset register 0; bottom 32 interrupts
  .equ STARTSRP0,     SYS_BASE+0x20C @R   Start logic status register 0; bottom 32 interrupts
  .equ STARTAPRP1,    SYS_BASE+0x210 @R/W Start logic edge control register 1; top 8 interrupts
  .equ STARTERP1,     SYS_BASE+0x214 @R/W Start logic signal enable register 1; top 8 interrupts
  .equ STARTRSRP1CLR, SYS_BASE+0x218 @W   Start logic reset register 1; top 8 interrupts
  .equ STARTSRP1,     SYS_BASE+0x21C @R   Start logic status register 1; top 8 interrupts
  .equ PDSLEEPCFG,    SYS_BASE+0x230 @R/W Power-down states in Deep-sleep mode
  .equ PDAWAKECFG,    SYS_BASE+0x234 @R/W Power-down states after wake-up from Deep-sleep mode
  .equ PDRUNCFG,      SYS_BASE+0x238 @R/W Power-down configuration register
  .equ DEVICE_ID,     SYS_BASE+0x3F4 @R   Device ID, 0x3D00002B for LPC1343
  .global SYS_BASE,SYSMEMREMAP,PRESETCTRL,SYSPLLCTRL,SYSPLLSTAT,SYSOSCCTRL,
  .global WDTOSCCTRL,IRCCTRL,SYSRESSTAT,SYSRSTSTAT,SYSPLLCLKSEL,SYSPLLCLKUEN,
  .global MAINCLKSEL,MAINCLKUEN,SYSAHBCLKDIV,SYSAHBCLKCTRL,SSP0CLKDIV,UARTCLKDIV,
  .global SSP1CLKDIV,WDTCLKSEL,WDTCLKUEN,WDTCLKDIV,CLKOUTCLKSEL,CLKOUTUEN,
  .global CLKOUTDIV,PIOPORCAP0,PIOPORCAP1,BODCTRL,SYSTCKCAL,NMISRC,STARTAPRP0,
  .global STARTERP0,STARTRSRP0CLR,STARTSRP0,STARTAPRP1,STARTERP1,STARTRSRP1CLR,
  .global STARTSRP1,PDSLEEPCFG,PDAWAKECFG,PDRUNCFG,DEVICE_ID
@
@ APB->CAN
@
  .equ CAN_BASE,       APB_BASE+0x50000
  .equ CAN_CNTL,       CAN_BASE+0x000	/* 0x000 */
  .equ CAN_STAT,       CAN_BASE+0x004
  .equ CAN_EC,         CAN_BASE+0x008
  .equ CAN_BT,         CAN_BASE+0x00C
  .equ CAN_INT,        CAN_BASE+0x010
  .equ CAN_TEST,       CAN_BASE+0x014
  .equ CAN_BRPE,       CAN_BASE+0x018
  .equ CAN_IF1_CMDREQ, CAN_BASE+0x020	/* 0x020 */
  .equ CAN_IF1_CMDMSK, CAN_BASE+0x024
  .equ CAN_IF1_MSK1,   CAN_BASE+0x028
  .equ CAN_IF1_MSK2,   CAN_BASE+0x02C
  .equ CAN_IF1_ARB1,   CAN_BASE+0x030
  .equ CAN_IF1_ARB2,   CAN_BASE+0x034
  .equ CAN_IF1_MCTRL,  CAN_BASE+0x038
  .equ CAN_IF1_DA1,    CAN_BASE+0x03C
  .equ CAN_IF1_DA2,    CAN_BASE+0x040
  .equ CAN_IF1_DB1,    CAN_BASE+0x044
  .equ CAN_IF1_DB2,    CAN_BASE+0x048
  .equ CAN_IF2_CMDREQ, CAN_BASE+0x080	/* 0x080 */
  .equ CAN_IF2_CMDMSK, CAN_BASE+0x084
  .equ CAN_IF2_MSK1,   CAN_BASE+0x088
  .equ CAN_IF2_MSK2,   CAN_BASE+0x08C
  .equ CAN_IF2_ARB1,   CAN_BASE+0x090
  .equ CAN_IF2_ARB2,   CAN_BASE+0x094
  .equ CAN_IF2_MCTRL,  CAN_BASE+0x098
  .equ CAN_IF2_DA1,    CAN_BASE+0x09C
  .equ CAN_IF2_DA2,    CAN_BASE+0x0A0
  .equ CAN_IF2_DB1,    CAN_BASE+0x0A4
  .equ CAN_IF2_DB2,    CAN_BASE+0x0A8
  .equ CAN_TXREQ1,     CAN_BASE+0x100	/* 0x100 */
  .equ CAN_TXREQ2,     CAN_BASE+0x104
  .equ CAN_ND1,        CAN_BASE+0x120	/* 0x120 */
  .equ CAN_ND2,        CAN_BASE+0x124
  .equ CAN_IR1,        CAN_BASE+0x140	/* 0x140 */
  .equ CAN_IR2,        CAN_BASE+0x144
  .equ CAN_MSGV1,      CAN_BASE+0x160	/* 0x160 */
  .equ CAN_MSGV2,      CAN_BASE+0x164
  .equ CAN_CLKDIV,     CAN_BASE+0x180	/* 0x180 */
  .global CAN_BASE,CNTL,STAT,EC,BT,INT,TEST,BRPE,IF1_CMDREQ,IF1_CMDMSK
  .global CAN_IF1_MSK1,IF1_MSK2,IF1_ARB1,IF1_ARB2,IF1_MCTRL,IF1_DA1,IF1_DA2
  .global CAN_IF1_DB1,IF1_DB2,IF2_CMDREQ,IF2_CMDMSK,IF2_MSK1,IF2_MSK2
  .global CAN_IF2_ARB1,IF2_ARB2,IF2_MCTRL,IF2_DA1,IF2_DA2,IF2_DB1,IF2_DB2
  .global CAN_TXREQ1,TXREQ2,ND1,ND2,IR1,IR2,MSGV1,MSGV2,CLKDIV
@
@ APB->SSP1
@
  .equ SSP1_BASE, APB_BASE+0x40000
  .equ SSP1CR0,   SSP1_BASE+0x000 @R/W Control Register 0
  .equ SSP1CR1,   SSP1_BASE+0x004 @R/W Control Register 1
  .equ SSP1DR,    SSP1_BASE+0x008 @R/W Data Register
  .equ SSP1SR,    SSP1_BASE+0x00C @R   Status Register
  .equ SSP1CPSR,  SSP1_BASE+0x010 @R/W Clock Prescale Register
  .equ SSP1IMSC,  SSP1_BASE+0x014 @R/W Interrupt Mask Set and Clear Register
  .equ SSP1RIS,   SSP1_BASE+0x018 @R   Raw Interrupt Status Register
  .equ SSP1MIS,   SSP1_BASE+0x01C @R   Masked Interrupt Status Register
  .equ SSP1ICR,   SSP1_BASE+0x020 @W   SSPICR Interrupt Clear Register
  .global SSP1_BASE,SSP1CR0,SSP1CR1,SSP1DR,SSP1SR,SSP1CPSR,SSP1IMSC,SSP1RIS,SSP1MIS,SSP1ICR
@
@ AHB peripherals
@
  .equ AHB_BASE, 0x50000000
@
@ GPIO0 addresses
@
  .equ GPIO0_BASE, AHB_BASE+0x00000
  .equ GPIO0DATA, GPIO0_BASE+0x3FFC  @ R/W Data
  .equ GPIO0DIR,  GPIO0_BASE+0x8000  @ R/W Direction: 0=input, 1=output
  .equ GPIO0IS,   GPIO0_BASE+0x8004  @ R/W Interrupt Sense: 0=edge, 1=level
  .equ GPIO0IBE,  GPIO0_BASE+0x8008  @ R/W Int. Both Edges: 0=one, 1=both
  .equ GPIO0IEV,  GPIO0_BASE+0x800C  @ R/W Int. Event: 0=low/falling, 1=high/rising
  .equ GPIO0IE,   GPIO0_BASE+0x8010  @ R/W Int. Enable: 0=disabled, 1=enabled
  .equ GPIO0RIS,  GPIO0_BASE+0x8014  @ R   Raw Int. Status
  .equ GPIO0MIS,  GPIO0_BASE+0x8018  @ R   Masked Int. Status
  .equ GPIO0IC,   GPIO0_BASE+0x801C  @ W   Int. Clear: 1=clear edge detect
  .global GPIO0_BASE,GPIO0DATA,GPIO0DIR,GPIO0IS,GPIO0IBE,GPIO0IEV,GPIO0IE,GPIO0RIS,GPIO0MIS,GPIO0IC
@
@ GPIO1 addresses
@
  .equ GPIO1_BASE, AHB_BASE+0x10000
  .equ GPIO1DATA, GPIO1_BASE+0x3FFC
  .equ GPIO1DIR,  GPIO1_BASE+0x8000
  .equ GPIO1IS,   GPIO1_BASE+0x8004
  .equ GPIO1IBE,  GPIO1_BASE+0x8008
  .equ GPIO1IEV,  GPIO1_BASE+0x800C
  .equ GPIO1IE,   GPIO1_BASE+0x8010
  .equ GPIO1RIS,  GPIO1_BASE+0x8014
  .equ GPIO1MIS,  GPIO1_BASE+0x8018
  .equ GPIO1IC,   GPIO1_BASE+0x801C
  .global GPIO1_BASE,GPIO1DATA,GPIO1DIR,GPIO1IS,GPIO1IBE,GPIO1IEV,GPIO1IE,GPIO1RIS,GPIO1MIS,GPIO1IC
@
@ GPIO2 addresses
@
  .equ GPIO2_BASE, AHB_BASE+0x20000
  .equ GPIO2DATA, GPIO2_BASE+0x3FFC
  .equ GPIO2DIR,  GPIO2_BASE+0x8000
  .equ GPIO2IS,   GPIO2_BASE+0x8004
  .equ GPIO2IBE,  GPIO2_BASE+0x8008
  .equ GPIO2IEV,  GPIO2_BASE+0x800C
  .equ GPIO2IE,   GPIO2_BASE+0x8010
  .equ GPIO2RIS,  GPIO2_BASE+0x8014
  .equ GPIO2MIS,  GPIO2_BASE+0x8018
  .equ GPIO2IC,   GPIO2_BASE+0x801C
  .global GPIO2_BASE,GPIO2DATA,GPIO2DIR,GPIO2IS,GPIO2IBE,GPIO2IEV,GPIO2IE,GPIO2RIS,GPIO2MIS,GPIO2IC
@
@ GPIO3 addresses
@
  .equ GPIO3_BASE, AHB_BASE+0x30000
  .equ GPIO3DATA, GPIO3_BASE+0x3FFC
  .equ GPIO3DIR,  GPIO3_BASE+0x8000
  .equ GPIO3IS,   GPIO3_BASE+0x8004
  .equ GPIO3IBE,  GPIO3_BASE+0x8008
  .equ GPIO3IEV,  GPIO3_BASE+0x800C
  .equ GPIO3IE,   GPIO3_BASE+0x8010
  .equ GPIO3RIS,  GPIO3_BASE+0x8014
  .equ GPIO3MIS,  GPIO3_BASE+0x8018
  .equ GPIO3IC,   GPIO3_BASE+0x801C
  .global GPIO3_BASE,GPIO3DATA,GPIO3DIR,GPIO3IS,GPIO3IBE,GPIO3IEV,GPIO3IE,GPIO3RIS,GPIO3MIS,GPIO3IC
@
@ System Control Space
@
  .equ SCS_BASE, 0xE000E000
@
@ System Control Block
@
  .equ SCB_BASE, SCS_BASE+0x0D00
  .equ CPUID,    SCB_BASE+0x00 @R  CPUID Base Register
  .equ ICSR,     SCB_BASE+0x04 @RW or RO Interrupt Control and State Register
  .equ AIRCR,    SCB_BASE+0x0C @RW Application Interrupt and Reset Control Register
  .equ SCR,      SCB_BASE+0x10 @RW System Control Register
  .equ CCR,      SCB_BASE+0x14 @RW Configuration and Control Register
  .equ SHPR2,    SCB_BASE+0x1C @RW System Handler Priority Register 2
  .equ SHPR3,    SCB_BASE+0x20 @RW System Handler Priority Register 3
  .global SCB_BASE, CPUID, ICSR, AIRCR, SCR, CCR, SHPR2, SHPR3
@
@ SysTick Space
@
  .equ SYSTICK_BASE, SCS_BASE+0x0010
  .equ STCTRL,   SYSTICK_BASE+0x0 @RW SysTick Control and Status Register
  .equ STLOAD,   SYSTICK_BASE+0x4 @RW SysTick Reload Value Register
  .equ STVAL,    SYSTICK_BASE+0x8 @RW SysTick Current Value Register
  .equ STCALIB,  SYSTICK_BASE+0xC @R  SysTick Calibration Value Register
  .global SYSTICK_BASE, STCTRL, STLOAD, STVAL, STCALIB
@
@ Nested Vector Interrupt Controller
@
  .equ NVIC_BASE, SCS_BASE+0x100
@  .equ ICTR,   SCS_BASE+0x004  @R  Interrupt Control Type Register
  .equ ISER,   NVIC_BASE+0x000 @RW Interrupt Set-Enable Register 0
  .equ ICER,   NVIC_BASE+0x080 @RW Interrupt Clear-Enable Register 0
  .equ ISPR,   NVIC_BASE+0x100 @RW Interrupt Set-Pending Register 0
  .equ ICPR,   NVIC_BASE+0x180 @RW Interrupt Clear-Pending Register 0
  .equ IPR0,   NVIC_BASE+0x300 @RW Interrupt Priority Register
  .equ IPR1,   NVIC_BASE+0x304 @RW Interrupt Priority Register
  .equ IPR2,   NVIC_BASE+0x308 @RW Interrupt Priority Register
  .equ IPR3,   NVIC_BASE+0x30C @RW Interrupt Priority Register
  .equ IPR4,   NVIC_BASE+0x310 @RW Interrupt Priority Register
  .equ IPR5,   NVIC_BASE+0x314 @RW Interrupt Priority Register
  .equ IPR6,   NVIC_BASE+0x318 @RW Interrupt Priority Register
  .equ IPR7,   NVIC_BASE+0x31C @RW Interrupt Priority Register
  .global NVIC_BASE,ISER,ICER,ISPR,ICPR
  .global IPR0,IPR1,IPR2,IPR3,IPR4,IPR5,IPR6,IPR7
@
@ NVIC register names used by Yiu
@
  .equ SETENA0, ISER0
  .equ SETENA1, ISER1
  .equ CLRENA0, ICER0
  .equ CLRENA1, ICER1
  .equ SETPEND0, ISPR0
  .equ SETPEND1, ISPR1
  .equ CLRPEND0, ICPR0
  .equ CLRPEND1, ICPR1
  .equ ACTIVE0, IABR0
  .equ ACTIVE1, IABR1
  .equ PRI_0,  NVIC_BASE+0x300
  .equ PRI_1,  NVIC_BASE+0x301
  .equ PRI_2,  NVIC_BASE+0x302
  .equ PRI_3,  NVIC_BASE+0x303
  .equ PRI_4,  NVIC_BASE+0x304
  .equ PRI_5,  NVIC_BASE+0x305
  .equ PRI_6,  NVIC_BASE+0x306
  .equ PRI_7,  NVIC_BASE+0x307
  .equ PRI_8,  NVIC_BASE+0x308
  .equ PRI_9,  NVIC_BASE+0x309
  .equ PRI_10, NVIC_BASE+0x30A
  .equ PRI_11, NVIC_BASE+0x30B
  .equ PRI_12, NVIC_BASE+0x30C
  .equ PRI_13, NVIC_BASE+0x30D
  .equ PRI_14, NVIC_BASE+0x30E
  .equ PRI_15, NVIC_BASE+0x30F
  .equ PRI_16, NVIC_BASE+0x310
  .equ PRI_17, NVIC_BASE+0x311
  .equ PRI_18, NVIC_BASE+0x312
  .equ PRI_19, NVIC_BASE+0x313
  .equ PRI_20, NVIC_BASE+0x314
  .equ PRI_21, NVIC_BASE+0x315
  .equ PRI_22, NVIC_BASE+0x316
  .equ PRI_23, NVIC_BASE+0x317
  .equ PRI_24, NVIC_BASE+0x318
  .equ PRI_25, NVIC_BASE+0x319
  .equ PRI_26, NVIC_BASE+0x31A
  .equ PRI_27, NVIC_BASE+0x31B
  .equ PRI_28, NVIC_BASE+0x31C
  .equ PRI_29, NVIC_BASE+0x31D
  .equ PRI_30, NVIC_BASE+0x31E
  .equ PRI_31, NVIC_BASE+0x31F
  .global SETENA0,SETENA1,CLRENA0,CLRENA1,SETPEND0,SETPEND1,CLRPEND0
  .global CLRPEND1,ACTIVE0,ACTIVE1,PRI_0,PRI_1,PRI_2,PRI_3,PRI_4,PRI_5
  .global PRI_6,PRI_7,PRI_8,PRI_9,PRI_10,PRI_11,PRI_12,PRI_13,PRI_14
  .global PRI_15,PRI_16,PRI_17,PRI_18,PRI_19,PRI_20,PRI_21,PRI_22
  .global PRI_23,PRI_24,PRI_25,PRI_26,PRI_27,PRI_28,PRI_29,PRI_30,PRI_31
@
@ Tell the linker that the vector table begins here (and must be loaded
@   at absolute address 0x0!)
@
  .section .isr_vector
@
@ Create all of the exception/interrupt vectors.
@ Note that service routine addresses in this table
@ should be declared as .thumb_func so the LSB will be
@ set to 1 and they will execute in thumb mode.
@
  .global __StackTop
  .global _vectors
_vectors:
  .word __StackTop                  @ Initial Stack Pointer
  .word Reset_Handler               @ Start of executable code
  .word NMI_Handler                 @ Non-maskable Interrupt Handler
  .word HardFault_Handler           @ Hard Fault Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVCall_Handler              @ SVCall Handler
  .word 0
  .word 0
  .word PendSV_Handler              @ PendSV Handler
  .word SysTick_Handler             @ SysTick Handler
  .word WAKEUP_IRQHandler           @ PIO0_0 Handler
  .word WAKEUP_IRQHandler           @ PIO0_1 Handler
  .word WAKEUP_IRQHandler           @ PIO0_2 Handler
  .word WAKEUP_IRQHandler           @ PIO0_3 Handler
  .word WAKEUP_IRQHandler           @ PIO0_4 Handler
  .word WAKEUP_IRQHandler           @ PIO0_5 Handler
  .word WAKEUP_IRQHandler           @ PIO0_6 Handler
  .word WAKEUP_IRQHandler           @ PIO0_7 Handler
  .word WAKEUP_IRQHandler           @ PIO0_8 Handler
  .word WAKEUP_IRQHandler           @ PIO0_9 Handler
  .word WAKEUP_IRQHandler           @ PIO0_10 Handler
  .word WAKEUP_IRQHandler           @ PIO0_11 Handler
  .word WAKEUP_IRQHandler           @ PIO1_0 Handler
  .word CAN_IRQHandler              @ CAN Handler
  .word SSP1_IRQHandler             @ SSP1 Handler
  .word I2C_IRQHandler              @ I2C Handler        
  .word TIMER16_0_IRQHandler        @ CT16B0 Handler
  .word TIMER16_1_IRQHandler        @ CT16B1 Handler
  .word TIMER32_0_IRQHandler        @ CT32B0 Handler
  .word TIMER32_1_IRQHandler        @ CT32B1 Handler
  .word SSP0_IRQHandler             @ SSP0 Handler
  .word UART_IRQHandler             @ UART0 Handler
  .word 0
  .word 0
  .word ADC_IRQHandler              @ ADC Handler
  .word WDT_IRQHandler              @ WDT Handler
  .word BOD_IRQHandler              @ BOD Handler
  .word FMC_IRQHandler              @ Flash Memory Controller Handler ??????
  .word PIOINT3_IRQHandler          @ PIO3 Interupt Handler
  .word PIOINT2_IRQHandler          @ PIO2 Interupt Handler
  .word PIOINT1_IRQHandler          @ PIO1 Interupt Handler
  .word PIOINT0_IRQHandler          @ PIO0 Interupt Handler
@
@ Dummy interrupt handlers are added here. The NMI and HardFault handlers
@   are defined uniquely as infinite loops. The other exceptions are all
@   aliased to the same infinite loop. These are defined as weak functions
@   so the user can redefine them as desired.
@
  .syntax unified
  .thumb_func
  .weak NMI_Handler
NMI_Handler:
   B .
  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
   B .
  .thumb_func
  .weak Default_Handler
Default_Handler:
   B .
   .global NMI_Handler,HardFault_Handler,Default_Handler
@
@ Map the rest of the interrupts to the Default Handler, weakly
@
  .macro MapIRQ vector
  .weak \vector
  .thumb_set \vector, Default_Handler
  .global \vector
  .endm

  MapIRQ SVCall_Handler
  MapIRQ PendSV_Handler
  MapIRQ SysTick_Handler
  MapIRQ IntDefault_Handler
  MapIRQ WAKEUP_IRQHandler
  MapIRQ CAN_IRQHandler
  MapIRQ SSP1_IRQHandler
  MapIRQ I2C_IRQHandler
  MapIRQ TIMER16_0_IRQHandler
  MapIRQ TIMER16_1_IRQHandler
  MapIRQ TIMER32_0_IRQHandler
  MapIRQ TIMER32_1_IRQHandler
  MapIRQ SSP0_IRQHandler
  MapIRQ UART_IRQHandler
  MapIRQ ADC_IRQHandler
  MapIRQ WDT_IRQHandler
  MapIRQ BOD_IRQHandler
  MapIRQ FMC_IRQHandler
  MapIRQ PIOINT3_IRQHandler
  MapIRQ PIOINT2_IRQHandler
  MapIRQ PIOINT1_IRQHandler
  MapIRQ PIOINT0_IRQHandler
@
@ Need some symbols from the linker
@
@  .global _bss, _ebss, data_start, data_size, data_load_start
  .global __bss_start__, __bss_end__, __data_start__, __data_end__, __etext
@
@ At reset we have to do the C run-time stuff:
@   Clear the bss segment in RAM
@   Copy the data segment from Flash to RAM
@   Setup the clocks
@   Go to the user's main
@
  .syntax unified
  .section .text
  .thumb_func
  .weak Reset_Handler
  .global Reset_Handler
Reset_Handler:
@
@ Clear the bss segment
@
  MOVS    R2, #0
  LDR     R0, =__bss_start__
  LDR     R1, =__bss_end__
ClearMore:
  CMP     R0, R1
  BEQ     LoadData
  STR     R2, [R0]
  ADDS    R0, #4
  B       ClearMore
@
@ Move the data segment from Flash to RAM
@
LoadData:
  LDR     R0, =__etext
  LDR     R1, =__data_end__
  LDR     R2, =__data_start__
MoveMore:
  CMP     R2, R1
  BEQ     Setup
  LDR     R3, [R0]
  STR     R3, [R2]
  ADDS    R0, #4
  ADDS    R2, #4
  B       MoveMore
@
@ Setup clocks and then go to main
@
Setup:
  LDR     R0, =SystemInit
  BLX     R0
  LDR     R0, =main
  BX      R0
  B       .
  .pool
  .end
