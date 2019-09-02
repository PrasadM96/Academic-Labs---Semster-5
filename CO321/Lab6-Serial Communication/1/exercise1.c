#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void usart_init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = 6;
}

void usart_send( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0) ));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}


int main( void )
{
	usart_init(MYUBRR);
	char arr[]="E/15/065 Prasad Madushanka , E/15/076 Sandushi Dileka , E/15/220 Hashan Maliththa";

	int i=0;

	for(i=0;arr[i]!='\0';i++){
		usart_send(arr[i]);
		_delay_ms(10);

	}

	while(1){

	}

	return 0;

}
