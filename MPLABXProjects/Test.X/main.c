/*
 * File:   main.c
 * Author: Loay
 *
 * Created on September 16, 2020, 2:41 PM
 */


#include <xc.h>
#include "config.h"
#include "system.h"

unsigned char counter = 0, nResets = 20;
void __interrupt() SwitchPress(void) {
    
    if (INTCONbits.INTF) {
        PORTBbits.RB3 = 1;
        CounterTask(3);
        PORTBbits.RB3 = 0;
        INTCONbits.INTF = 0;
    }
    if (TMR1IF) {
        TMR1 = 15536;   // to prevent reseting to zero after each enterrupt
        counter++;
        if (counter == nResets) {    // limiting number of overflows
            PORTBbits.RB3 = ~PORTBbits.RB3;
            counter = 0; // reset forever
//            TMR1ON = 0;  // stop timer
        }
        TMR1IF = 0;
    }
}

void main(void) {
    // interrupt flags
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.PEIE = 1;
    
    // interrupt output led
    TRISBbits.TRISB3 = 0;
    PORTBbits.RB3 = 0;
    
    //timer settings
    TMR1 = 15536;    // initial value to start from
//    TMR1 = 0;    // initial value to start from

    TMR1IE = 1;     // enable TMR1 interrupt bit
    TMR1CS = 0;     // internal clk source
    T1CKPS0 = 0;    // selecting 1-prescaler 
    T1CKPS1 = 0;
    TMR1ON = 1;     // starting timer one;
    


    while (1) {
        LampTask();
        MotorTask();
    }
    return;
}
