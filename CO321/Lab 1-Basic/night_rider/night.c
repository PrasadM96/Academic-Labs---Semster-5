#include<avr/io.h>
#include<util/delay.h>

#define DELAY 100

int main(void){
	int i,j,k;
	
	for(i=1;i<5;i++){
		DDRB = DDRB | (1<<i);
	}
	
	while(1){
		for(j=1;j<5;j++){
			PORTB = PORTB | (1<<j); 
			_delay_ms(DELAY);
			PORTB = PORTB & ~(1<<j); 		
		}
		
		for(k=j-2;k>1;k--){
			PORTB = PORTB | (1<<k); 
			_delay_ms(DELAY);
			PORTB = PORTB & ~(1<<k); 
			
		}
	}
	
	return 0;
}
