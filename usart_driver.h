//this is .h file for usart driver BY DEFAULT IT IS SET TO 2400 BAUD
#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#define END '/' //USE THIS CHARACTER FOR SET THE LAST CHARACTER OF A STRING
#define DUMMY 0x00

unsigned char received_data=0;
unsigned char numb[]={0,0,0};

//void interrupt(); // if you are using more interrupts, put this inside the general interrupt function
void usart_init();
void usart_send(unsigned char *package);
void usart_sendn(unsigned char number);
void usart_sendc(unsigned char c);
void usart_receiver(unsigned char choose);

#endif