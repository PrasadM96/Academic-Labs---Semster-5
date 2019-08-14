
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>


//volatile uint32_t n,elapsed_time;

void delay_timer0(){

	int m;
	
	for(m=0;m<5;m++){
		TCNT0 = 0;
	
		TCCR0A = 0x00;
		TCCR0B = 0x05;
	
		while((TIFR0 & 0x01) == 0);
	
		TCCR0A = 0x00;
		TCCR0B = 0x00;
	
		TIFR0 = 0x01;
	}


}
 

int main (void) { 
	int i, j,k,m; 
	
	for(i=1;i<=5;i++){
		DDRB = DDRB | (1<<i);
	}

	sei();	 // enable interrupt subsystem globally 
	
	TIMSK1 = 0x01;// enable Timer 1 overflow interrupt 
	TCCR1A = 0x00; 	// normal mode 
	TCCR1B = 0x04; 	// no prescaler, internal clock 

	
	TCNT1 = 3036; 	// reset Timer 1 
	
	
		

	/////night rider///////
	while(1){
		for(j=1;j<5;j++){
			PORTB = PORTB | (1<<j); 
		    delay_timer0();
			PORTB = PORTB & ~(1<<j); 		
		}
		
		for(k=j-2;k>1;k--){
			PORTB = PORTB | (1<<k); 
			delay_timer0();
			PORTB = PORTB & ~(1<<k); 
			
		}
	}
	///////////////////////
	
	return 0;
}

ISR(TIMER1_OVF_vect){ // Timer1 overflow interrupt service routine
	PORTB =PORTB ^ (1<<5);
} 




