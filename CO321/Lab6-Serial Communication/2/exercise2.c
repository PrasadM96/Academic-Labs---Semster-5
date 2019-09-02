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

void usart_send( unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0) ));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

char cipher(char c){
	int custom;

	if(c>64 && c<91){
		custom=(c-65+3)%26;
		return (custom+65);

	} else if (c>96 && c<123){
		custom=(c-97+3)%26;
		return (custom+97);
	}else{
		return c;
	}


	}



int main( void )
{
	usart_init(MYUBRR);
	int i;
	while(1){
		 char c=usart_receive( );
      if(c==10)
			usart_send(c);
			else
		 	usart_send(cipher(c));
			}







		// for( i=0;word[i]!="\0";i++){
		// 	usart_send(word[i]);
		// }




	return 0;

}
