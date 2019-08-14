#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define DELAY 1000

int main(){
	DDRB |=(1<<0);
	
	DDRD &= ~(1<<2);
	
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	
	sei();
	
	EIMSK |=(1<<INT0);
	
	while(1){
		
	}
	return 0;
}

ISR(INT0_vect){
	PORTB ^= (1<<0);
	//_delay_ms(DELAY);
}
