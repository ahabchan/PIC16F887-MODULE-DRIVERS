//this is .h file for PWM driver BY DEFAULT IT USES PORTC PIN 2

#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#define CLEAR 0
#define SET 1

void pwm_init();
void pulse_width(unsigned int width); //resolution of 1023 bits 
void pwm_period(unsigned int period);

#endif