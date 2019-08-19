
#include <avr/io.h>
#include<util/delay.h>

int main(){

	

	DDRC &= ~(1<<1);//adc1 in avr input
	DDRD = 0xFF;// output
	
	ADCSRA |= ((1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0));//enabel adc and select conversion speed 64 prescaler
	
	//AVCC voltage reference
	ADMUX |= ((1<<REFS0)|(1<<ADLAR)|(0<<REFS1));
	
	
	//ADC1 by multiplexer
	ADMUX |= ((1<<MUX0)|(0<<MUX1)|(0<<MUX2)|(0<<MUX3));
	
	
	
	
	while(1){
	   //activate start conversion bit
	   ADCSRA |= (1<<ADSC);
	
	   //Wait for conversion to complete
	   while(!(ADCSRA & (1<<ADIF)));
	   
	   	PORTD= ADCH;
	   
	   //clear ADIF
	   ADCSRA|=(1<<ADIF);
	}
	
	return 0;
}
