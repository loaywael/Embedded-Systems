///*
// * File:   main.c
// * Author: Ezio
// *
// * Created on September 20, 2020, 3:08 PM
// */
//
//
#include <xc.h>
#include "system.h"
#include "config.h"


void main(void) {
    while(1) {
        uint16_t duty = 0; 
        uint16_t freq = 2000;
        initPWM(freq);
        
        while(duty < 1024) {
            setPWM(duty);
            duty += 3;
            __delay_ms(2);    
        }
        __delay_ms(500);
        while(duty > 0) {
            setPWM(duty);
            duty -= 1;
            __delay_ms(2);    
        }
        __delay_ms(100);
    return;
    }
}
