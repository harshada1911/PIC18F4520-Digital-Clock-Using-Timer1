#include <xc.h>

/* ================= CONFIGURATION BITS ================= */

#pragma config OSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOREN = OFF
#pragma config BORV = 3
#pragma config WDT = OFF
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = ON
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF

/* ================= DEFINITIONS ================= */

#define _XTAL_FREQ 4000000

// Common Cathode 7-segment codes
unsigned char seg[10] =
{
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

volatile unsigned int tick_10ms = 0;
volatile unsigned char sec = 0, min = 0;
volatile unsigned char pause = 0;

/* ================= TIMER1 ISR ================= */

void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)
    {
        // Reload Timer1 for 10 ms (4 MHz, prescaler 1:8)
        TMR1H = 0xFB;
        TMR1L = 0x1E;
        PIR1bits.TMR1IF = 0;

        if (!pause)
        {
            tick_10ms++;
            if (tick_10ms >= 100)
            {
                tick_10ms = 0;
                sec++;

                if (sec == 60)
                {
                    sec = 0;
                    min++;
                    if (min == 60)
                        min = 0;
                }
            }
        }
    }
}

/* ================= DISPLAY MULTIPLEX ================= */

void display(unsigned char d1, unsigned char d2,
             unsigned char d3, unsigned char d4)
{
    PORTA = (PORTA & 0xF0) | 0x01;   // Digit 1
    PORTD = seg[d1] & 0x7F; __delay_ms(2);

    PORTA = (PORTA & 0xF0) | 0x02;   // Digit 2
    PORTD = seg[d2] & 0x7F; __delay_ms(2);

    PORTA = (PORTA & 0xF0) | 0x04;   // Digit 3
    PORTD = seg[d3] & 0x7F; __delay_ms(2);

    PORTA = (PORTA & 0xF0) | 0x08;   // Digit 4
    PORTD = seg[d4] & 0x7F; __delay_ms(2);
}

/* ================= MAIN ================= */

void main(void)
{
    TRISD = 0x00;      // Segment output
    TRISA = 0x00;      // Digit control output
    TRISB = 0x03;      // RB0, RB1 as input

    ADCON1 = 0x0F;     // All pins digital
    PORTA = 0x00;
    PORTD = 0x00;

    // Timer1 configuration
    T1CON = 0x31;      // ON, prescaler 1:8
    TMR1H = 0xFB;
    TMR1L = 0x1E;

    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1)
    {
        if (RB0)       // Pause / Resume
        {
            pause = !pause;
            __delay_ms(300);
        }

        if (RB1)       // Reset
        {
            sec = 0;
            min = 0;
        }

        display(min / 10, min % 10,
                sec / 10, sec % 10);
    }
}
