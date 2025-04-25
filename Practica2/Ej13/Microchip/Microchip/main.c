#include "lcd.h"
#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Definir los tiempos para el reloj en formato HH:MM:SS
volatile uint8_t hours = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 1;
volatile uint16_t millisecond_count = 0;

// Constantes
#define DEBOUNCE_DELAY_US 5
#define SCAN_DELAY_MS 100
#define MAX_CHARS_LINE_1 16
#define MAX_CHARS_LINE_2 32

// Funci�n de interrupci�n de TIMER2 para actualizar el reloj
ISR(TIMER2_COMPA_vect)
{
    millisecond_count++;

    // Cada 1000 interrupciones (1 segundo)
    if (millisecond_count >= 120)
    {
        millisecond_count = 0;
        seconds++;
        if (seconds >= 60)
        {
            seconds = 0;
            minutes++;
            if (minutes >= 60)
            {
                minutes = 0;
                hours++;
                if (hours >= 24)
                {
                    hours = 0;
                }
            }
        }
    }
}

// Configuraci�n del TIMER2 para generar una interrupci�n cada 1 milisegundo
void Timer2_Init()
{
    // Modo CTC, prescaler de 64
    TCCR2A = 0;                                        // Modo normal
    TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS21); // CTC con prescaler de 64

    // Configurar el valor de comparaci�n para que la interrupci�n ocurra cada 1 milisegundo
    OCR2A = 249; // (F_CPU / (prescaler * 1000 Hz)) - 1 = (16000000 / (64 * 1000)) - 1 = 249

    // Habilitar interrupciones para el Timer2
    TIMSK2 |= (1 << OCIE2A); // Habilitar la interrupci�n de comparaci�n A

    // Habilitar interrupciones globales
    sei();
}

void LCD_Update_Time()
{
    char time_str[9]; // Formato HH:MM:SS
    sprintf(time_str, "%02d:%02d:%02d", hours, minutes, seconds);
    LCDGotoXY(4, 0);                         // Mover al inicio de la primera l�nea
    LCDstring((unsigned char *)time_str, 8); // Mostrar el tiempo en el LCD
}

int main()
{
    // Inicializar el LCD
    LCD_Init();
    LCDstring((unsigned char *)"~~~~00:00:00~~~~", 16);
    // Inicializar el temporizador TIMER2
    Timer2_Init();

    while (1)
    {
        // Actualizar el LCD cada vez que el temporizador interrumpe
        LCD_Update_Time();

        // Puedes agregar otras funcionalidades aqu� si es necesario
        _delay_ms(SCAN_DELAY_MS); // Retardo adicional si es necesario (aunque no deber�a ser necesario con la interrupci�n)
    }

    return 0;
}
