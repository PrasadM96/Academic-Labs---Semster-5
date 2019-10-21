/*************************************************************************
Title:    Testing output to a HD44780 based LCD display.
Author:   Peter Fleury  <pfleury@gmx.ch>  http://tinyurl.com/peterfleury
File:     $Id: test_lcd.c,v 1.8 2015/01/31 18:04:08 peter Exp $
Software: AVR-GCC 4.x
Hardware: HD44780 compatible LCD text display
          AVR with external SRAM interface if memory-mapped LCD interface is used
          any AVR with 7 free I/O pins if 4-bit IO port mode is used
**************************************************************************/
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"
#define FOSC 16000000 // Clock Speed


/*
** constant definitions
*/
static const PROGMEM unsigned char copyRightChar[] =
{
	0x07, 0x08, 0x13, 0x14, 0x14, 0x13, 0x08, 0x07,
	0x00, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00
};

//keypad
char keyMap[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void Col_init(void)
{
  DDRB = 0xF0;  // bit 0.3 are columns (0 is input)
  PORTB = 0x0F;  //pullups on these bits 

  DDRC = 0x0F;
  PORTC = 0x00;
  //very short delay
  asm volatile ("nop");  
  asm volatile ("nop"); 
}

void Row_init(void)
{
  DDRC = 0xF0;  // bit 3..6 used for rows
  PORTC = 0x0F;  //pullups on these bits 
  DDRB = 0x0F;
  PORTB = 0x00;
  _delay_ms(1);
}

unsigned char Read_key(void){
  unsigned char col,row;	
  
  
  Col_init();      //set up columns to read
 
  col=10; row=10;       // init value
  
  lcd_puts(PINC);

	// read columns first - 0 if key in that column pressed
	if (!(PINB & 0x01)) 
			    {col = 0; }  // Col2 = bit0 is low
  else if (!(PINB & 0x02)) 
			    {col = 1;}   // Col1 = bit1 is low
  else if (!(PINB & 0x04)) 
          {col = 2; }  // Col0 = bit2 is low 
  else if (!(PINB & 0x08)) 
          {col = 3; }  // Col0 = bit2 is low 

  Row_init();   //set up rows to read
				
			
  if (!(PINC & 0x01)) 
          {row = 0; }  // Col2 = bit0 is low
  else if (!(PINC & 0x02)) 
          {row = 1;}   // Col1 = bit1 is low
  else if (!(PINC & 0x04)) 
          {row = 2; }  // Col0 = bit2 is low 
  else if (!(PINC & 0x08)) 
          {row = 3; }  // Col0 = bit2 is low 
    
	_delay_ms(50); // switch debounce 
  if (col==10 | row==10)
    return 'H';
	return keyMap[row][col];  // value is sum of row and column   
}

///

//eeprom

void EEPROMwrite(unsigned int address,char data){
	while(EECR & (1<<EEPE));
	
	EEAR = address;
	EEDR = data;
	
	EECR |= (1<<EEMPE);
	
	EECR |= (1<<EEPE);
}

char EEPROMread (unsigned int address){
	while(EECR & (1<<EEPE));
	
	EEAR = address;
	
	EECR = (1<<EERE);
	
	return EEDR;
}


char * cipher(char s[],char c){
   int i;
   for(i=0;s[i]!='\0';i++){
      s[i]=s[i]+(int)(c-'0');
   }
   return s;
}


int main(void)
{
          
   char read_val;
   int flag=0,temp=0;
   EEPROMwrite(0,'4');
    /* initialize display, cursor off */
   lcd_init(LCD_DISP_ON);
   read_val= Read_key();
   char *str;
   
   while(1){
 /*  
   lcd_clrscr();
    read_val= Read_key();
     lcd_putc(read_val);
     _delay_ms(100);*/
     lcd_clrscr();
     lcd_puts_P( "Enter your" );
     lcd_gotoxy(0,1);
     lcd_puts_P("choice");
     _delay_ms(2000);
     lcd_command(LCD_MOVE_DISP_LEFT);
     lcd_clrscr();
     int complete=0;
      
     while(!complete){
	if(temp==0){
	   lcd_puts("1.Encryption");
	   lcd_gotoxy(0,1);
	   lcd_puts("2.Change the key");
	   _delay_ms(2000);
	   while(read_val!='1' && read_val!='2'){read_val= Read_key(); /*lcd_clrscr();lcd_putc(read_val);*/}
	 }else{
	       break;
	  }
	
	if(read_val=='1'){
	   lcd_clrscr();
	   lcd_puts("Enter text and");
	   lcd_gotoxy(0,1);
       lcd_puts("To end Press *");
	   _delay_ms(2000);
	   lcd_clrscr();
	   lcd_gotoxy(0,0);
	   
	   read_val= Read_key();
	   _delay_ms(200);
	   int i=0;
	   char c[100];
	    
	   
	  while(read_val!='*'){ 
	  // lcd_clrscr();
	       if(read_val!='H'){
			 c[i]=read_val;
			// strcat(str,c);
			 lcd_gotoxy(i,0);
			 lcd_putc(c[i]);
			 _delay_ms(200);
			 read_val='H';
			 i++;  
	      }
	       while(read_val=='H'){read_val= Read_key();_delay_ms(20);} 
	   }
	   c[i]='\0';
	   
	   
	   lcd_clrscr();
	   char key=EEPROMread (0);
	   char *s=cipher(c,key);
	  
	   lcd_puts("Encrypted text-");
	   lcd_gotoxy(0,1);
     //lcd_puts_p(c);
     	int j;
	  	for(j=0;c[j]!='\0';j++){
	  		lcd_gotoxy(j,1);
	  		lcd_putc(s[j]);
	  	}	
	   _delay_ms(4000);
	   
	   flag = 1;
	   
	  
	   
	}else if(read_val=='2'){
	   lcd_clrscr();
	   lcd_puts("Enter the key..");
	   lcd_gotoxy(0,1);
	   _delay_ms(1000);
	   read_val= Read_key();
	   while(read_val=='H'){read_val= Read_key();  lcd_gotoxy(0,1);}
	   lcd_putc(read_val);
	  _delay_ms(200);
	   EEPROMwrite(1,' ');
	   EEPROMwrite(0,read_val);
	   
	   lcd_clrscr();
	   _delay_ms(1000);
	   lcd_puts("Key is changed..");
	   _delay_ms(2000);
	   flag=1;
	 
	}
	
	if(flag==1){
	   lcd_clrscr();
	   lcd_puts("Continue????");
	   lcd_gotoxy(0,1);
        lcd_puts("1.Yes    2.No");
	   _delay_ms(2000);
	   read_val=Read_key();
	   while(read_val!='1' && read_val!='2'){read_val= Read_key();/* lcd_clrscr();lcd_putc(read_val);*/}
	   
	   if(read_val=='1'){complete=1;read_val='0';break;}
	   else if(read_val=='2'){
	     lcd_clrscr();
	     lcd_puts("Good bye");
	     temp=1;
	     read_val='0';
	     exit(1);
	   
	   }
	}
      }
     
      
   }
   

}
