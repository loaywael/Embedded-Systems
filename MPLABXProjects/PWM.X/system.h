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

#include "config.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
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

#define _PRE_SCALER 4
#define _XTAL_FREQ 4000000

uint16_t pwmPeroid = 0, pwmDutyCycle = 0, pwmFreq = 100;  
inline void initPWM(uint16_t freq) {
    //--[ Configure The CCP Module For PWM Mode ]--
    // Enable PWM
    CCP1M2 = 1;
    CCP1M3 = 1;
    // Config PWM output pin
    TRISC2 = 0;
    PORTCbits.RC2 = 0;
    // TIMER2 CONFIG
    pwmFreq = freq;
    TMR2ON = 1;
    switch (_PRE_SCALER) {
        case 4:
            T2CKPS0 = 1;
            T2CKPS1 = 0;
            break;
        default:
            T2CKPS0 = 0;
            T2CKPS1 = 0;
            break;
    }
}

inline void setPWM(uint16_t dutyCycle) {
    if((dutyCycle<1024) && (dutyCycle) && (pwmFreq)) {
        // Config PWM Interval
        pwmPeroid = (uint16_t)((1/pwmFreq)*(_XTAL_FREQ/(4*_PRE_SCALER))) - 1;
        CCPR2 = pwmPeroid;
        CCP1CONbits.CCP1Y = dutyCycle & 1;   // cpy 1st bit value
        CCP1CONbits.CCP1X = dutyCycle & 2;   // cpy 2nd bit value        
        CCPR1L = dutyCycle >> 2;  // move the 8-MSBs to CCPR1L Register
    }
}

#endif	/* XC_HEADER_TEMPLATE_H */


