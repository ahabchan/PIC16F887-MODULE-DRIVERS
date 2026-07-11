//this is .c file for usart driver
/*
void interrupt(){
 if(PIR1.RCIF){
  received_data=RCREG;
 }
}   */
#include <xc.h>
#include "usart_driver.h"

#define _XTAL_FREQ 4000000

void usart_init(unsigned long baud) {
    TXSTAbits.SYNC = 0; //0 = ASYNCHRONOUS EUSART, 1 = SYMCHRONOUS EUSART
    BAUDCTLbits.BRG16 = 0; //0 = 8 BIT GENERATOR FOR BAUD RATE
    if (baud >= 9600) {
        TXSTAbits.BRGH = 1; //1= HIGH
        SPBRG = (_XTAL_FREQ / (16UL * baud)) - 1;
    } else {
        TXSTAbits.BRGH = 0; // low speed
        SPBRG = (_XTAL_FREQ / (64UL * baud)) - 1;
    }
    RCSTAbits.SPEN = 1; //ENABLE TX AND RX AS SERIAL PORT TERMINAL

    TXSTAbits.TXEN = 1; //ENABLES TRANSMISSION
    RCSTAbits.CREN = 1;
}

void usart_send(unsigned char *package) {
    //STARTING DATA TRANSMISSION
    while (*package != '\0') {
        while (*package){
            while (!PIR1bits.TXIF); //WAIT FOR THE TXREG FOR BE READY TO RECEIVE NEW DATA TO BE HOLD
            TXREG = *package++; //SENDING CHARACTER TO THE TRANSMITTER REGISTER
        }
    }
}

void usart_sendc(unsigned char c) {
    //STARTING DATA TRANSMISSION
    while (!PIR1bits.TXIF); //WAIT FOR THE TXREG FOR BE READY TO RECEIVE NEW DATA TO BE HOLD
    TXREG = c; //SENDING CHARACTER TO THE TRANSMITTER REGISTER

}

void usart_sendn(unsigned char number) {
    char digits[3];

    digits[0] = (number / 100) + '0';
    digits[1] = ((number / 10) % 10) + '0';
    digits[2] = (number % 10) + '0';

    unsigned char i = 0;

    if (digits[0] == '0') i++;
    if (digits[1] == '0') i++;

    while (i < 3) {
        while (!PIR1bits.TXIF);
        TXREG = digits[i++];
    }
}

unsigned char usart_read(void)
{
    // Wait until a byte is received
    while(!PIR1bits.RCIF);
    // Handle overrun error (VERY IMPORTANT)
    if(RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    // Return received byte (reading RCREG clears RCIF)
    return RCREG;
}

unsigned char usart_available(void)
{
    return PIR1bits.RCIF;
}
