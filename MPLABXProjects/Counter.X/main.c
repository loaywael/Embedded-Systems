/*
 * File:   main.c
 * Author: Ezio
 *
 * Created on September 19, 2020, 1:48 PM
 */


#include <xc.h>
#include "config.h"

unsigned char counts = 0;
void main(void) {
    TRISC1 = 1;
    TRISB = 0;
    TMR1 = 0;
    TMR1CS = 1;
    T1CKPS0 = 0;
    T1CKPS1 = 0;

    PORTB = 0;
//    RC1 = 0;
    TMR1ON = 1;
    T1OSCEN = 0;
    T1SYNC = 0;
    while(1) {
        counts = TMR1&0x0F;
        PORTB = counts;
    }
    

    return;
}
