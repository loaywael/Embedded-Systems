/*
 * File:   main.c
 * Author: Ezio
 *
 * Created on September 19, 2020, 9:41 AM
 */


#include <xc.h>
#include "config.h"

inline float calcDistance(void) {
    float distance = 0;
    TMR1 = 0;
    PORTCbits.RC0 = 1;
    __delay_us(10);
    PORTCbits.RC0 = 0;
    while(!PORTCbits.RC1);
    TMR1ON = 1;
    while(PORTCbits.RC1);
    TMR1ON = 0;
    distance = (float)(TMR1 * 1e-6 * 340)/2;
    return distance;
}

void main(void) {
    unsigned char dist = 0;
    TRISB = 0x00;
    TRISCbits.TRISC0 = 0;     // Trigger pin
    TRISCbits.TRISC1 = 1;     // Echo pin
    TRISB = 0x00;
    
    PORTB = 0x00;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    
    TMR1CS = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    while(1) {
        // discretizing distance value into 5 digital levels (0, 1, 2, 3, 4)
        dist = (unsigned char)(calcDistance())/5;
        switch(dist) {
            case 1: // 5cm
                PORTB = 0x01;
                break;
            case 2: // 10cm
                PORTB = 0x03;
                break;
            case 3: //15cm
                PORTB = 0x07;
                break;
            case 4: //20cm
                PORTB = 0x0F;
                break;
            default:
                PORTB = 0;
                __delay_ms(100);
        }
    }
    return;
}
