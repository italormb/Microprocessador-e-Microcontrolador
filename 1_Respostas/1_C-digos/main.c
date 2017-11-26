#include <msp430g2553.h>
//#include
#define ADC_CHANNELS 6

unsigned int samples[ADC_CHANNELS];
unsigned int POLEGAR, MEDIO, MINDINHO, INDICADOR;


// Acelerômetro
unsigned char RX_Data[6];
unsigned char TX_Data[2];
unsigned char RX_ByteCtr;
unsigned char TX_ByteCtr;
int xAccel;
int sel_xAccel;
int yAccel;
int sel_yAccel;
int zAccel;
int sel_zAccel;
unsigned char slaveAddress = 0x68;    // Set slave address for MPU-6050
                    // 0x68 for ADD pin=0
                    // 0x69 for ADD pin=1

const unsigned char PWR_MGMT_1   = 0x6B;    // MPU-6050 register address
const unsigned char ACCEL_XOUT_H = 0x3B;    // MPU-6050 register address
const unsigned char ACCEL_XOUT_L = 0x3C;    // MPU-6050 register address
const unsigned char ACCEL_YOUT_H = 0x3D;    // MPU-6050 register address
const unsigned char ACCEL_YOUT_L = 0x3E;    // MPU-6050 register address
const unsigned char ACCEL_ZOUT_H = 0x3F;    // MPU-6050 register address
const unsigned char ACCEL_ZOUT_L = 0x40;    // MPU-6050 register address

//Funções do Acelerômetro

void i2cInit(void);
void i2cWrite(unsigned char);
void i2cRead(unsigned char);
void coleta_valores_mpu(void);
int coleta_valores_MPU(int sel_xAccel,int sel_yAccel,int sel_zAccel);


void ConfigureAdc(void)

    {

       ADC10CTL1 |= INCH_5 + CONSEQ_3 + ADC10SSEL_3;
       ADC10CTL0 |= SREF_0 + ADC10SHT_0 + MSC + ADC10ON + ADC10IE;
       ADC10AE0 |= BIT5 +BIT4+BIT3+BIT0;
       ADC10DTC1 = ADC_CHANNELS; //4 canais
       ADC10CTL0 |= ENC + ADC10SC;
    }


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   //Stop WDT


//if (CALBC1_1MHZ == 0xFF)
  //                {
    //               while (1);
      //            }
DCOCTL = 0;
BCSCTL1 = CALBC1_1MHZ;
DCOCTL = CALDCO_1MHZ;


P1SEL |= BIT1 + BIT2 + BIT6 + BIT7; //P1.1TX e P1.2RX
P1SEL2 |= BIT1 + BIT2+ BIT6 + BIT7;
P1DIR &=~BIT2;
P1DIR &=~BIT1;

UCA0CTL1 |= UCSSEL_2;
UCA0BR0 = 104;
UCA0BR1 = 0;
UCA0MCTL = UCBRS0;
UCA0CTL1 &= ~UCSWRST;
ConfigureAdc();

while (1)
{
    POLEGAR = samples[0];
    INDICADOR = samples[1];
    MEDIO = samples[2];
    MINDINHO = samples[5];
        ADC10CTL0 &= ~ENC;
        while (ADC10CTL1 & BUSY);
        ADC10SA = (unsigned int)samples;
        ADC10CTL0 |= ENC + ADC10SC;

     __bis_SR_register(CPUOFF + GIE);
//Coleta os Valores do MPU, Acelerometro
        sel_xAccel=1; 
        sel_yAccel=0;
        sel_zAccel=0;
        xAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);
        
        sel_xAccel=0;
        sel_yAccel=1;
        sel_zAccel=0;
        yAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);
        
        sel_xAccel=0;
        sel_yAccel=0;
        sel_zAccel=1;
        zAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);

    if  ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR < 498)&&(MEDIO<=264) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'A';
    }
    else if ( (POLEGAR > 815) && (INDICADOR > 670)&&(MEDIO > 380) && (MINDINHO > 544))
    {
      UCA0TXBUF = 'B';
    }
    else if ( (POLEGAR < 710) && ((INDICADOR <= 670) && (INDICADOR > 498)) && ((MEDIO > 264) && (MEDIO  <= 380)) &&((MINDINHO <= 544) && (MINDINHO > 521)) && (xAccel < 0) )
    {
      UCA0TXBUF = 'C';
    }
    else if ( ((POLEGAR >= 710) && (POLEGAR<=815)) && (INDICADOR > 670) && ((MEDIO > 264) && MEDIO  <= 380) &&((MINDINHO <= 544) && (MINDINHO > 521)))
    {
      UCA0TXBUF = 'D';
    }
    else if ( (POLEGAR > 815) && (INDICADOR<=498)&&(MEDIO<=264) &&(MINDINHO<=521) && (xAccel > 0))
    {
      UCA0TXBUF = 'E';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && ((INDICADOR <= 670) && (INDICADOR > 498)) && (MEDIO > 380) &&(MINDINHO > 544) && (xAccel > 0) )
    {
      UCA0TXBUF = 'F';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670)&& (MEDIO <= 264) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'G';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670) &&((MEDIO > 264) && (MEDIO  <= 380)) &&(MINDINHO<=521) && (xAccel < 0) && (yAccel< 0) && (zAccel< 0))
    {
      UCA0TXBUF = 'H'; //USAR O GIROSCOPIO PARA DIFERENCIAR
    }
    else if ( (POLEGAR > 815) && (INDICADOR<=498)&&(MEDIO<=264) &&(MINDINHO > 544))
    {
      UCA0TXBUF = 'I';
    }
    else if ( (POLEGAR > 815) && (INDICADOR<=498)&&(MEDIO<=264) &&((MINDINHO <= 544) && (MINDINHO > 521)))
    {
      UCA0TXBUF = 'J';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR<=498) && ((MEDIO > 264) && (MEDIO  <= 380)) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'K'; // USAR O GIROSCOPIO PARA DIFERENCIAR
    }
    else if ( (POLEGAR < 710) &&(INDICADOR > 670)&&(MEDIO<=264) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'L';
    }
    else  if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670) && (MEDIO > 380) &&(MINDINHO<=521) && (yAccel < 0) && (zAccel < 0))
    {
      UCA0TXBUF = 'M';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670) && (MEDIO > 380) &&(MINDINHO<=521) && (yAccel > 0) && (zAccel > 0))
    {
      UCA0TXBUF = 'N';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && ((INDICADOR <= 670) && (INDICADOR > 498)) &&((MEDIO > 264) && (MEDIO  <= 380)) &&((MINDINHO <= 544) && (MINDINHO > 521)))
    {
      UCA0TXBUF = 'O';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670)&& ((MEDIO > 264) && (MEDIO  <= 380)) &&(MINDINHO<=521) && (xAccel < 0) && (yAccel > 0) && (zAccel > 0))
    {
      UCA0TXBUF = 'P'; // USAR O GIROSCOPIO PARA DIFRENCIAR 
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR > 670) &&(MEDIO<=264) && (MINDINHO<=521))
    {
      UCA0TXBUF = 'Q';
    }
    else if ( (POLEGAR > 815) && (INDICADOR > 670) && ((MEDIO > 264) && (MEDIO  <= 380)) && (MINDINHO<=521))
    {
      UCA0TXBUF = 'R';
    }
    else if ( (POLEGAR > 815) && (INDICADOR<=498)&&(MEDIO<=264) &&(MINDINHO<=521) && (xAccel < 0))
    {
      UCA0TXBUF = 'S';
    }
    else if ( (POLEGAR >= 710 && POLEGAR<=815) && (INDICADOR<=498)&& (MEDIO > 380) &&(MINDINHO > 544)  && (xAccel < 0))
    {
      UCA0TXBUF = 'T';
    }
    else if ( (POLEGAR > 815) && (INDICADOR > 670) && (MEDIO > 380) && (MINDINHO<=521) && (xAccel < 0) && (yAccel< 0) && (zAccel< 0))
    {
      UCA0TXBUF = 'U';
    } 
    else if ( (POLEGAR > 815) && (INDICADOR > 670) && (MEDIO > 380) && (MINDINHO<=521) && (xAccel > 0) && (yAccel < 0 ) && (zAccel < 0))
    {
      UCA0TXBUF = 'V';
    }
    else if ( (POLEGAR > 815) && ((INDICADOR <= 670) && (INDICADOR > 498))&&(MEDIO<=264) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'X';
    }
    else if ( (POLEGAR > 815) && (INDICADOR > 670)&&(MEDIO > 380) &&(MINDINHO<=710)  && (xAccel < 0) && (yAccel > 0) && (zAccel > 0))
    {
      UCA0TXBUF = 'W';
    }
    else if ( (POLEGAR < 710) && (INDICADOR<=498)&&(MEDIO<=264) && (MINDINHO > 544))
    {
      UCA0TXBUF = 'Y';
    }
    else if ( (POLEGAR > 815) && (INDICADOR > 670) &&(MEDIO<=264) &&(MINDINHO<=521))
    {
      UCA0TXBUF = 'Z';
    }
    else if ( (POLEGAR < 710) && ((INDICADOR <= 670) && (INDICADOR > 498)) && ((MEDIO > 264) && (MEDIO  <= 380))  && (xAccel > 0))
    {
      UCA0TXBUF = 'Ç';
    } 
   else {
 
      UCA0TXBUF = '.';     
    }


  }

}
#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    UCA0TXBUF = 0x00;

  __bic_SR_register_on_exit(CPUOFF);
}

void i2cInit(void)
{
    // set up I2C module
    UCB0CTL1 |= UCSWRST;                // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;            // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 10;                    // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                // Clear SW reset, resume operation
}

void i2cWrite(unsigned char address)
{
    //__disable_interrupt();
    UCB0I2CSA = address;                // Load slave address
    IE2 |= UCB0TXIE;                // Enable TX interrupt
    while(UCB0CTL1 & UCTXSTP);            // Ensure stop condition sent
    UCB0CTL1 |= UCTR + UCTXSTT;            // TX mode and START condition
    __bis_SR_register(CPUOFF + GIE);        // sleep until UCB0TXIFG is set ...
}

void i2cRead(unsigned char address)
{
    __disable_interrupt();
    UCB0I2CSA = address;                // Load slave address
    IE2 |= UCB0RXIE;                // Enable RX interrupt
    while(UCB0CTL1 & UCTXSTP);            // Ensure stop condition sent
    UCB0CTL1 &= ~UCTR;                // RX mode
    UCB0CTL1 |= UCTXSTT;                // Start Condition
    __bis_SR_register(CPUOFF + GIE);        // sleep until UCB0RXIFG is set ...
}
// USCIAB0TX_ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
    if(UCB0CTL1 & UCTR)                    // TX mode (UCTR == 1)
    {
        if (TX_ByteCtr)                        // TRUE if more bytes remain
        {
            TX_ByteCtr--;                // Decrement TX byte counter
            UCB0TXBUF = TX_Data[TX_ByteCtr];    // Load TX buffer
        }
        else                        // no more bytes to send
        {
            UCB0CTL1 |= UCTXSTP;            // I2C stop condition
            IFG2 &= ~UCB0TXIFG;            // Clear USCI_B0 TX int flag
            __bic_SR_register_on_exit(CPUOFF);    // Exit LPM0
        }
    }
    else // (UCTR == 0)                    // RX mode
    {
        RX_ByteCtr--;                        // Decrement RX byte counter
        if (RX_ByteCtr)                        // RxByteCtr != 0
        {
            RX_Data[RX_ByteCtr] = UCB0RXBUF;    // Get received byte
            if (RX_ByteCtr == 1)            // Only one byte left?
            UCB0CTL1 |= UCTXSTP;            // Generate I2C stop condition
        }
        else                        // RxByteCtr == 0
        {
            RX_Data[RX_ByteCtr] = UCB0RXBUF;    // Get final received byte
            __bic_SR_register_on_exit(CPUOFF);    // Exit LPM0
        }
    }
}

int coleta_valores_MPU(int sel_xAccel,int sel_yAccel,int sel_zAccel){
        
        
  
        // Initialize the I2C state machine
	i2cInit();
	
	// Wake up the MPU-6050
	slaveAddress = 0x68;					// MPU-6050 address
	TX_Data[1] = 0x6B;						// address of PWR_MGMT_1 register
	TX_Data[0] = 0x00;						// set register to zero (wakes up the MPU-6050)
	TX_ByteCtr = 2;
	i2cWrite(slaveAddress);


	
		// Point to the ACCEL_ZOUT_H register in the MPU-6050
		slaveAddress = 0x68;					// MPU-6050 address
		TX_Data[0] = 0x3B;					// register address
		TX_ByteCtr = 1;
		i2cWrite(slaveAddress);

		// Read the two bytes of data and store them in zAccel
		slaveAddress = 0x68;					// MPU-6050 address
		RX_ByteCtr = 6;
		i2cRead(slaveAddress);
		xAccel  = RX_Data[5] << 8;				// MSB
		xAccel |= RX_Data[4];					// LSB
		yAccel  = RX_Data[3] << 8;				// MSB
		yAccel |= RX_Data[2];					// LSB
		zAccel  = RX_Data[1] << 8;				// MSB
		zAccel |= RX_Data[0];					// LSB

		// do something with the data

		__no_operation();                       // Set breakpoint >>here<< and read


        
        if((sel_xAccel==1) && (sel_yAccel==0) && (sel_zAccel==0)){
        return xAccel;
        }
        else if((sel_xAccel==0) && (sel_yAccel==1) && (sel_zAccel==0)){
        return yAccel;
        }
        else if((sel_xAccel==0) && (sel_yAccel==0) && (sel_zAccel==1)){
        return zAccel;
        } 
          

return 0;
}

