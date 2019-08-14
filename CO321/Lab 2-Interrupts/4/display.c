#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define DELAY 1000
int count=-1; 

int main(){
	int i;

	
	for (i=0;i<=5;i++){
		DDRB = DDRB | (1<<i);
	}
	
	//INT0
	DDRD &= ~(1<<2);
	
	EICRA |= (1<<ISC01);
	EICRA |= (1<<ISC00);
	
	sei();
	
	EIMSK |=(1<<INT0);
	
	//INT1
	DDRD &= ~(1<<3);
	
	EICRA |= (1<<ISC11);
	EICRA |= (1<<ISC10);
	
	sei();
	EIMSK |=(1<<INT1);
	
	PORTB= 0b00000000;
	
	while(1){
		
	}
	return 0;
}

ISR(INT0_vect){

	count++;
	if(count>6){
		PORTB= 0b00000000;
		count=0;
	}
	_delay_ms(DELAY);
	PORTB =PORTB <<1;
	PORTB |= 1;
	
}



ISR(INT1_vect){
	count++;
	if(count>6){
		PORTB= 0b00000000;
	    count=0;
	}
	_delay_ms(DELAY);
	//PORTB &= ~(1<<count);
	
	PORTB =PORTB <<1;

}
