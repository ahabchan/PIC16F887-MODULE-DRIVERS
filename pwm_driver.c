//this is .c file for PWM driver BY DEFAULT IT USES PORTC PIN 2

#include "pwm_driver.h"
#include <xc.h>

void pwm_init(){
//SET PIN IN PROPER MODE
      CCP1CONbits.P1M0=CLEAR;
      CCP1CONbits.P1M1=SET;
      
      CCP1CONbits.CCP1M2=SET;
      CCP1CONbits.CCP1M3=SET;
      
      PIR1bits.TMR2IF=CLEAR;
      T2CONbits.TMR2ON=SET;
      TRISC2=CLEAR;
      
      pwm_period(256);
      //CALCULATING POWER IN PWM TERMS
      pulse_width(50);
}

void pulse_width(unsigned int width){
      CCP1CON|=((width&0x0003)<<4);
      CCPR1L=width>>2;
}

void pwm_period(unsigned int period){
      PR2=period-1;
}
