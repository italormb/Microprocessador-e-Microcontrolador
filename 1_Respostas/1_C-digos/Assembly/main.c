#include <msp430g2553.h>
#include <intrinsics.h>
#define BTN BIT3
#define LED1 BIT0
#define LED2 BIT6

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT |= LED1 + LED2;
  P1DIR |= LED1 + LED2;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  P1IES |= BTN;
  P1IE |= BTN;
    for(;;)
    {
        _BIS_SR(GIE + LPM4_bits);
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    while((P1IN&BTN)==0)
    {
     P1OUT |= LED1 + LED2;
      
    }
    P1OUT &= ~(LED1 + LED2);
    
    P1IFG &= ~BTN;
}

