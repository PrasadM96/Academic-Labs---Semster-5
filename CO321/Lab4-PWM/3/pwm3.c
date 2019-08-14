#include<avr/io.h>

void delay_timer0(){

	TCNT2 = 0;
	
	TCCR2A = 0x00;
	TCCR2B = 0x04;
	
	while((TIFR2 & 0x01) == 0);
	
	TCCR2A = 0x00;
	TCCR2B = 0x00;
	
	TIFR2 = 0x01;
}



int main(void){
	int i=0,j,k;
	DDRD= DDRD | (1<<6);//PD6
	
	TCNT0 = 0;
	
	
	TCCR0A = 131;
	TCCR0B = 3;
	//PORTD |= (1<<6);
	
	
	while(1){
		for(i=0;i<=127;i++){
			OCR0A=i;
			for(k=0;k<10;k++)delay_timer0();
		}
	
		for(j=127;j>=0;j--){
			OCR0A=j;
			for(k=0;k<10;k++)delay_timer0();
		}
		
	
	}

	return 0;
}
