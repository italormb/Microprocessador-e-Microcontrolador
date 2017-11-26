#include <msp430g2553.h> // Biblioteca da MSP430 MODELO G2553
#define BTN BIT2         // btn=0000 00010
#define LED1 BIT0        // LED=0000 0001
#define LED2 BIT6         // LED2= 0010 0000
led_pisca ()
{
  WDTCTL= WDTPW + WDTHOLD;
  PIOUT=0;
  PIDIR= LED1 + LED2;
  FOR(;;)
  {
    P1OUT|= LED1+ LED2; 
  
    }  
  }
} 
led_apaga()
{
 WDTCTL= WDTPW + WDTHOLD;
  PIOUT=0;
  PIDIR= LED1 + LED2;
  FOR(;;)
  {
   
    PIOUT&=~(LED1+LED2);
    }  
  }
} 

}

void main(void){
WDTCTL = WDTPW | WDTHOLD; //Parar o whatdog timer
P1OUT = 0;                 // Desligar os Leds no inicio
P1DIR = LED1 + LED2;       // Deixar disponiveis os valores
for(;;)
{
led_pisca();
led_apaga()
}
}