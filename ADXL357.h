/*
 * Register Name declarations to interface with Analog Devices ADXL375
 *
 * Author: E. Pesek
 * Date: November 9, 2017
 * Version 1.0
 *
 *	SPI Timing Diagram and Addressing:
 *---------------------------------------------------------------------
 * SCLK		1		2		3		4		5		6		7		8
 * MOSI		A6		A5		A4		A3		A2		A1		A0		RW
 *---------------------------------------------------------------------
 *
 *	Send eight click pulses following a read command to get the response from the slave device
 *	For write commands send the 8 bit payload after the 8 bit address packet
 */




// R/W Bit, write is active low
#define READ			0x01
#define WRITE			0x00


// Use 7 bit Register Address
#define DEVID_AD		0x00
#define DEVID_MST		0x01
#define PARTID			0x02
#define REVID			  0x03
#define STATUS			0x04
#define FIFO_ENTRIES	        0x05   // new comments
#define TEMP2			  0x06
#define TEMP1			  0x07
#define XDATA3			0x08
#define XDATA2			0x09
#define XDATA1			0x0A
#define YDATA3			0x0B
#define YDATA2			0x0C
#define YDATA1			0x0D
#define ZDATA3			0x0E
#define ZDATA2			0x0F
#define ZDATA1			0x10
#define FIFO_DATA		0x11
#define OFFSET_X_H		0x1E
#define OFFSET_X_L		0x1F
#define OFFSET_Y_H		0x20
#define OFFSET_Y_L		0x21
#define OFFSET_Z_H		0x22
#define OFFSET_Z_L		0x23
#define ACT_EN			  0x24
#define ACT_THRESH_H	        0x25
#define ACT_THRESH_L	        0x26
#define ACT_COUNT		0x27
#define FILTER			0x28
#define FIFO_SAMPLES	        0x29
#define INT_MAP			0x2A
#define SYNC			  0x2B
#define RANGE			  0x2C
#define POWER_CTL		0x2D
#define SELF_TEST		0x2E
#define RESET			  0x2F

