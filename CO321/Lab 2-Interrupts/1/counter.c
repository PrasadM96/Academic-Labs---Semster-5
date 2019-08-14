#include<avr/io.h>
#include<stdio.h>
#include<util/delay.h>

#define DELAY 500

int main(){
	int count=0,i;
	
	DDRD = DDRD & ~(1<<7);
	
	for (i=0;i<=5;i++){
		DDRB = DDRB | (1<<i);
	}
	
	
	
	while(1){
		if(PIND>>7 && 1){
		    PORTB = PORTB & ~count;
		    _delay_ms(DELAY);
			count++;
		}
		if(count>126){
				count=0;
		}
		
		PORTB = PORTB | count;
		
	}
	return 0;
}

