#include <MSP430.h>

int main (void)
 {
	 WDTCTL = WDTPW + WDTHOLD;
	 ADC12CTL0 = SHT0_2 + ADC12ON;
	 ADC12CTL1 = SHP;
	 ADC12IE = BIT0;
	 P6DIR &= ~BIT0;
	 P6SEL |= BIT0;
	 P1DIR |= BIT0;
	 for(;;)
	 {
		 ADC12CTL0 |= (ADC12SC);
		 __bis_SR_register(LPM0_bits + GIE);
	 }
   return 0;
 }   

 #pragma vector = ADC12_VECTOR
 __interrupt void  adc12_isr(void)
 {
	 if(ADC12MEM0 < 0x7FF)
	 {
		 P1OUT &= ~BIT0;
	 }
	 else
	 {
		 P1OUT |= BIT0;
		 __bic_SR_register_on_exit(LPM0_bits);
	 }
 }