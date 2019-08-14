#include<avr/io.h>

void delay_timer0(){

	TCNT2 = 0;
	
	TCCR2A = 0x00;
	TCCR2B = 0x05;
	
	while((TIFR2 & 0x01) == 0);
	
	TCCR2A = 0x00;
	TCCR2B = 0x00;
	
	TIFR2 = 0x01;
}

void test(int oA,int tB){
	TCNT0 = 0;
	OCR0A =oA;
	TCCR0A = 131;
	TCCR0B = tB;
}



int main(void){
	int i=0;
	
	DDRD= DDRD | (1<<6);//PD6
	
	
	
	while(1){
		test(191,5);
		for(i=0;i<1000;i++)delay_timer0();
		test(191,4);
		for(i=0;i<1000;i++)delay_timer0();
		test(191,3);
		for(i=0;i<1000;i++)delay_timer0();
		test(191,2);
		for(i=0;i<1000;i++)delay_timer0();
	}

	return 0;
}
