#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define DELAY 500
int count=0; 

int main(){
	int i;

	
	for (i=0;i<=5;i++){
		DDRB = DDRB | (1<<i);
	}
	
	
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
		    //PORTB = PORTB & ~count;
		    //_delay_ms(DELAY);
			count++;
			PORTB = count;
			//_delay_ms(DELAY);
			if(count>126){
				count=0;
			}
}
