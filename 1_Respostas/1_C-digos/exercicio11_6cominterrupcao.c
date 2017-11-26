#include <msp430g2553.h>
#include <intrinsics.h>

//#define PERIODO 62500  // PISCA EM 1 SEGUNDO; 1 HZ COM ID_3
#define PERIODO 125    // PISCA EM 1000HZ COM ID_2

#define LED BIT0

void Atraso(volatile unsigned int x){
        TA0CCR0 =((PERIODO-1)*x); //10000-1;
	TA0CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;
	//_BIS_SR(LPM0_bits+GIE);
        while(1){
	P1OUT ^= LED;
	TA0CTL &= ~TAIFG;
}
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
	
	BCSCTL1 = CALBC1_1MHZ;		//MCLK e SMCLK @ 1MHz
	DCOCTL = CALDCO_1MHZ;		//MCLK e SMCLK @ 1MHz
	P1OUT &= ~LED;
	P1DIR |= LED;
       Atraso(1000);
       
	
	
}

/*#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
	P1OUT ^= LED;
	TA0CTL &= ~TAIFG;
}  */