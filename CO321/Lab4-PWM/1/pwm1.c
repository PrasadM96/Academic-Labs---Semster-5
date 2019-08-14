#include<avr/io.h>



int main(void){
	DDRD= DDRD | (1<<6);//PD6
	
	TCNT0 = 0;
	OCR0A = 50;
	
	TCCR0A = 131;
	TCCR0B = 3;
	//PORTD |= (1<<6);
	
	
	while(1){
		
		
	
	}

	return 0;
}
