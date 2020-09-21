/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "config.h"
// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


//unsigned char counter = 0;
//unsigned char nResets = 0;
//unsigned char const PRE_SCALER = 1;


inline void initMotorTask(void) {
    TRISC = 0x00;
    PORTC = 0x00;
}

inline void resetMotor(void) {
    PORTC = 0x00;
}

inline void MotorTask(void) {
    initMotorTask();
    unsigned char j = 0;
    unsigned short int const NO_STEPS = 48;
    for (int i=0; i<NO_STEPS; i++){
        PORTC = (unsigned char)(1 << j);   // 2^0, 2^1, 2^2, 2^3, then repeat
        __delay_ms(100);
        j++;
        if(j==4){
            j = 0;
        }
    }
    __delay_ms(1000);
    
    j = 0;
    for (int i=0; i<NO_STEPS; i++){
        PORTC = (unsigned char)(8 >> j);   // 2^3, 2^2, 2^1, 2^0, then repeat
        __delay_ms(100);
        j++;
        if(j==4){
            j = 0;
        }
    }
    __delay_ms(1000);
    resetMotor();
    return;
}


inline void initLampTask(void) {
    
//    initTimer1(1000);
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
}

inline void resetLamp(void) {
    PORTBbits.RB2 = 0;
    INTCONbits.TMR0IE = 0;

}

inline void LampTask(void) {
    initLampTask();
    for (int i=0; i<3; i++) {
        if(PORTBbits.RB1){
            PORTBbits.RB2 = 1;
        __delay_ms(500);
        PORTBbits.RB2 = 0;        
        __delay_ms(500);
        }
    }
    resetLamp();
    return;
}


inline void initCounterTask(void) {
    TRISD = 0x00;
    PORTD = 0x3F;
}

inline void resetCounter(void) {
    PORTD = 0x00;
}

inline void CounterTask(int maxCount) {
    initCounterTask();
    unsigned char segmentCode[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };
    // {'0': 0b00111111, '1': 0b00000110, '2': 0b01011011, '3': 0b01001111,
    //  '4': 0b01100110, '5': 0b01101101, '6': 0b01111101, '7': 0b00000111, 
    //  '8': 0b01111111, '9': 0b01101111}
    for(int i=0; i<maxCount; i++) {
        PORTD = segmentCode[i+1];
        __delay_ms(1000);
    }
    resetCounter();
    return;
}


//inline void initTimer1(int delay_ms) {
//    TMR1 = 0;
//    TMR1IE = 1;
//    TMR1CS = 0;
//    T1CKPS0 = 0;
//    T1CKPS1 = 0;
//    float resetTime = ((4*PRE_SCALER)/(_XTAL_FREQ))*65535;
//    nResets = (unsigned char)(resetTime / delay_ms);
//}

//inline void __interrupt() onDelayTimer() {
//    if(TMR1IF) {
//        counter++;
//        if(counter == nResets) {
//            counter = 0;
//            LampTask();
//        }
//        TMR1IF = 0;
//    }
//}