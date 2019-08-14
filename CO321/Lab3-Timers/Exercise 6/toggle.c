
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>



volatile uint32_t n;

void delay_timer0(){

		TCNT2 = 150;
	
		TCCR2A = 0x00;
		TCCR2B = 0x04;
	
		while((TIFR0 & 0x01) == 0);
	
		TCCR2A = 0x00;
		TCCR2B = 0x00;
	
		TIFR2 = 0x01;
	

}
 

int main (void) { 
	int i, j,k,m; 
	
	
	DDRB = DDRB | (1<<5);
	

	sei();	 // enable interrupt subsystem globally 
	
	TIMSK0 = 0x01;// enable Timer 1 overflow interrupt 
	TCCR0A = 0x00; 	// normal mode 
	TCCR0B = 0x04; 	// 1:256 prescaler, internal clock 

	
	TCNT0 = 0; 	// reset Timer 1 

	while(1){
	
	}
	
	return 0;
}

ISR(TIMER0_OVF_vect){ // Timer1 overflow interrupt service routine
	n++;
	if(n==24){
		delay_timer0();
		PORTB = PORTB ^ (1<<5);
		n=0;
	}
} 


