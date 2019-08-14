// Measuring time taken to execute a piece of code

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

volatile uint32_t n;
 
ISR(TIMER1_OVF_vect){ // Timer1 overflow interrupt service routine
	n++; // increment overflow count 
} 

int main (void) { 
	int i, j; 
	uint32_t elapsed_time; 	// uint32_t is unsigned 32-bit integer data type 

	TIMSK = 0b00000100; 	// enable Timer 1 overflow interrupt 
	TCCR1A = 0b00000000; 	// normal mode 
	TCCR1B = 0b00000001; 	// no prescaler, internal clock 

	n = 0; 		// reset n 
	TCNT1 = 0; 	// reset Timer 1 
	sei(); 		// enable interrupt subsystem globally 

	// ----- start code -------------- 
	for (i = 0; i < 100; i++) 
		for (j = 0; j < 1000; j++){;} 
	// ----- end code ----------------- 

	elapse_time = n * 65536/16 + (uint32_t) TCNT1; // elapsed time in microseconds
	cli(); // disable interrupt subsystem globally 
	return 0;
}
