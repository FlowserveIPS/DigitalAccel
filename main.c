/*
 * Functions to interface with Analog Devices ADXL375
 *
 * Author: E. Pesek
 * Date: November 9, 2017
 * Version 1.0
 *
 */
// Updated this comment by Akshat on 10 Aug 2018

// When the USCI module is enabled by clearing the UCSWRST bit it is ready to receive and transmit.
// In master mode, writing to UCxTXBUF activates the bit clock generator and the data will begin to transmit.

#include <ADXL357.h>
#include <__cross_studio_io.h>
//#include <msp430.h>
#include <in430.h>
#include <msp430f2417.h>

void InitSPI(void);
char queryADXL357(char address);
void writeADXL357(char address, char command);
void SPIwrite(char commmand);
char SPIread(void);
void CS_enable(void);
void CS_disable(void);
char spi_transfer_byte(char data);
void delay(int cycles);
int read_temperature(void);
int read_X_Axis(void);
int read_Y_Axis(void);
int read_Z_Axis(void);
//int binTwosComplementToSignedDecimal(char binary[],int significantBits);  //comment out 06/11/2018
int check_status(void);


// Using these globals for debugging
char poll_command = 0;
int temperature = 0;
long int X_Axis = 0;
long int Y_Axis = 0;
long int Z_Axis = 0;

/**************************************************************************************************************************/

void main(void)
{
	char response = 0;
        int i = 0;
        int accel_status = 0;

        WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer // 06/25/2018

        // Clock Configuration
        DCOCTL = DCO0 ; 
        BCSCTL3 = XT2S1 | XCAP1;
        BCSCTL1 &= ~XT2OFF;
       

	InitSPI();  // Init SPI
        
        _NOP();

        writeADXL357(POWER_CTL, 0x00); // Enable Data Sampling on ADXL357

        _NOP();

        response = queryADXL357(STATUS);    // report status

        _NOP();

        while(1)
        {

         delay(5000);
        
         accel_status = check_status();

          if(accel_status == 1)  // 06/22/2018
          {

           _NOP();
                 
           temperature = read_temperature();
          
           read_X_Axis(); // 06/22/2018
           read_Y_Axis(); // 06/22/2018
           read_Z_Axis();

           _NOP();

          }

        }
      
}

/**************************************************************************************************************************/

char queryADXL357(char address)
{
	char reply = 0;				// Refer to ADXL357.h for list of Register Addresses
						// Bits[7:1] are the command to the accel, Bit[0] refers to the read/write operation of the command
	address = address << 1;			// Bit shift left by one
	address = address | READ;		// OR with the read operation

        poll_command = address;

        CS_enable();                            // Enable Chip Select (active low)

	spi_transfer_byte(address);
 
        reply = spi_transfer_byte(0x00);        // Read response from command

        CS_disable();                           // Disable Chip Select
      
	return(reply);
}

/**************************************************************************************************************************/

void writeADXL357(char address, char command)
{
	char reply = 0;
						// Refer to ADXL357.h for list of Register Addresses
						// Bits[7:1] are the command to the accel, Bit[0] refers to the read/write operation of the command
	address = address << 1;			// Bit shift left by one
	address = address | WRITE;		// OR with the write operation

	CS_enable();                            // Enable Chip Select (active low)

	spi_transfer_byte(address);
        spi_transfer_byte(command);             // Command to write to ADXL357 Register

         CS_disable();                          // Disable Chip Select
      
        _NOP();

}

/**************************************************************************************************************************/

int check_status(void)
{
    int result = 0;
    int ready = 0;

    result = queryADXL357(STATUS); 

    // function checks the status register and determines status of DATA_RDY (bit 0)
    // when set - "A complete x-axis, y-axis, and z-axis measurement was made and results can be read"
    // check if bit 0 is set
    if ( (result >> 0) & 1)   // change val---> result   06/11/2018
    {
      ready = 1;
    }
    
    else
    {
      ready = 0;
    }


    return ready;
}


/**************************************************************************************************************************/

int read_temperature(void)
{
    int temperature_msb = 0;
    int temperature_lsb = 0;
    int result = 0;

    temperature_msb = queryADXL357(TEMP2);    
    temperature_lsb = queryADXL357(TEMP1);    
      
    result = (temperature_msb << 8) | temperature_lsb;
        
    _NOP();

    return(result);
}

/**************************************************************************************************************************/

int read_X_Axis(void)
{

    long int X_accel_19_12 = 0;
    long int X_accel_11_4 = 0;
    long int X_accel_3_0 = 0;
    long int result = 0;
    int compliment = 0;
    long int test;
   

    X_accel_19_12 = queryADXL357(XDATA3);
    X_accel_11_4 = queryADXL357(XDATA2);
    X_accel_3_0 = queryADXL357(XDATA1);
          
    result = (X_accel_19_12 << 12) | (X_accel_11_4 << 4) | (X_accel_3_0 >> 4);
  X_Axis = result;

    // If a positive value, return it
            if ((result & 0x80000) == 0)
            {
                test = result;
            }
 
            // Otherwise perform the 2's complement math on the value
            else
            {
            test = (~result + 1) * -1;
            test >= 12;
            }
  //  compliment =  binTwosComplementToSignedDecimal(binary_string,20);     

    _NOP();

    return(compliment);

}

/**************************************************************************************************************************/

int read_Y_Axis(void)
{

    long int Y_accel_19_12 = 0;
    long int Y_accel_11_4 = 0;
    long int Y_accel_3_0 = 0;
    long int result = 0;
    int compliment = 0;
   

    Y_accel_19_12 = queryADXL357(YDATA3);
    Y_accel_11_4 = queryADXL357(YDATA2);
    Y_accel_3_0 = queryADXL357(YDATA1);
          
    result = (Y_accel_19_12 << 12) | (Y_accel_11_4 << 4) | (Y_accel_3_0 >> 4);
  Y_Axis = result;
    
  //  compliment =  binTwosComplementToSignedDecimal(binary_string,20);     

    _NOP();

    return(compliment);

}

/**************************************************************************************************************************/

int read_Z_Axis(void)
{

    long int Z_accel_19_12 = 0;
    long int Z_accel_11_4 = 0;
    long int Z_accel_3_0 = 0;
    long int result = 0;
    int compliment = 0;
   

    Z_accel_19_12 = queryADXL357(ZDATA3);
    Z_accel_11_4 = queryADXL357(ZDATA2);
    Z_accel_3_0 = queryADXL357(ZDATA1);
          
    result = (Z_accel_19_12 << 12) | (Z_accel_11_4 << 4) | (Z_accel_3_0 >> 4);
  Z_Axis = result;
    
  //  compliment =  binTwosComplementToSignedDecimal(binary_string,20);     

    _NOP();

    return(compliment);

}

/**************************************************************************************************************************/


char spi_transfer_byte(char data)
{
    _NOP();
    UCB1TXBUF = data;    // write
      
    while ((UC1IFG & UCB1RXIFG) == 0); // wait for transfer to complete
    UC1IFG &= ~UCB1RXIFG; // clear the rx flag
      
    return(UCB1RXBUF);
}

/**************************************************************************************************************************/

void InitSPI(void)
// Description:
//   Initialization of the SPI Module
{
      int UCB_reg = 0;

      P5DIR |= BIT6;  // Set direction of P5.6, Bit = 1: The port pin is switched to output direction
      P5DIR |= BIT1;  // Set direction of P5.1, Bit = 1: The port pin is switched to output direction (Master Out)
      P5DIR &= ~BIT2;  // Set direction of P5.2, Bit = 0: The port pin is switched to input direction (Master In)
      P5DIR |= BIT3;  // Set direction of P5.3, Bit = 1: The port pin is switched to output direction (Serial Clock)

      P5SEL |= BIT1;  // Set mode of P5.1
      P5SEL |= BIT2;  // Set mode of P5.2
      P5SEL |= BIT3;  // Set mode of P5.3


      CS_disable();

      

      UCB1CTL1 |= UCSWRST;   // Enable software reset    // 06/11/2018

      UCB1CTL0 = 	(1 << 7) |	/* Bit 7, UCCKPH Clock Phase*/
			(0 << 6) |	/* Bit 6, UCCKPL Clock Polarity 0 = Inactive Low, 1 = Inactive High*/
			(1 << 5) |	/* Bit 5, UCMSB MSB First Select 0 = LSB First, 1 = MSB First*/
			(0 << 4) |	/* Bit 4, UC7BIT Character Length 0 = 8-Bit, 1 = 7-Bit*/
			(1 << 3) |	/* Bit 3, UCMST Master Mode Select 0 = Slave, 1 = Master*/
			(0 << 2) |	/* Bit 2:1, USCI Mode 00 - 3 Pin SPI, 01 - 4 Pin SPI active high, 10 - 4 Pin SPI active low, 11 - I2C Mode*/
			(0 << 1) |
			(1 << 0);	/* Bit 0, UCSYNC Sync Mode Enable 0 = ASYNC MODE, 1 = SYNC MODE*/

      UCB1CTL1 = 	(0 << 7) |	/* Bit 7 -6 UCSSELx, UCI Clock Source Select */
			(1 << 6) |	/* 00 = NA; 01 = ACLK; 10 = SMCLK; 11 = SMCLK */
			(0 << 5) |	/* Bit 5, Unused */
			(0 << 4) |	/* Bit 4, Unused */
			(0 << 3) |	/* Bit 3, Unused */
			(0 << 2) |	/* Bit 2 Unused */
			(0 << 1) |      /* Bit 1 Unused */
			(1 << 0);	/* Bit 0, UCSWRST Software Reset Enable 0 = Disabled (released), 1 = Enabled (reset state) */

      UCB_reg = UCB1CTL0;               // For debugging purposes

      UCB1BR0 = 0;//8
      UCB1BR1 = 0;
   //   UCA0MCTL=0;    

     
     UCB1CTL1 &= ~UCSWRST;            // Clear SW reset, resume operation
}

/**************************************************************************************************************************/

void CS_disable(void)
{
    int i = 0;

    delay(1);
    P5OUT |= BIT6;  // Bit = 1: The output is high
   
}


/**************************************************************************************************************************/

void CS_enable(void)
{
    P5OUT &= ~BIT6;  // Bit = 0: The output is low
    delay(1);
    
}

/**************************************************************************************************************************/

void delay(int cycles)
{
    int i;

    for(i=0; i<=cycles;i++) // add some delay before changing state of carrier select
    {
       _NOP();
    }

}

/**************************************************************************************************************************/

/* comment out 06/11/2018
int binTwosComplementToSignedDecimal(char binary[],int significantBits) 
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i=0; i<significantBits; ++i)
    {
        if ( i==0 && binary[i]!='0')
        {
            sum = power * -1;
        }
        else 
        {
            sum += (binary[i]-'0')*power;//The -0 is needed
        }
        power /= 2;
    }

    return sum;
}
*/


/*
void SPIwrite(char command)
{
        CS_enable();                            // Enable Chip Select (active low)
	_NOP();
            
        UCB1TXBUF = command;    
        while ((UC1IFG & UCB1RXIFG) == 0); // wait for transfer to complete
        UC1IFG &= ~UCB1RXIFG; // clear the rx flag

        
        _NOP();
        CS_disable();                           // Disable Chip Select

        _NOP();
      
}


/**************************************************************************************************************************/
/*
char SPIread(void)
{
	char reply = 0;

        CS_enable();                            // Enable Chip Select (active low)
		
        UCB1TXBUF = 0x00; 			// Transmit empty packet to receive response from slave device	        
        reply = UCB1RXBUF;

        CS_disable();                           // Disable Chip Select

        _NOP();
	
        return(reply);

}


 public static int ConvertTwosComplementByteToInteger(byte rawValue)
        {
            // If a positive value, return it
            if ((rawValue & 0x80) == 0)
            {
                return rawValue;
            }
 
            // Otherwise perform the 2's complement math on the value
            return (byte)(~(rawValue - 0x01)) * -1;
        }

        */ 
