/* Inclusión de bibliotecas de código */
#include <avr/io.h>      // Registros del microcontrolador
#define F_CPU 16000000UL // Defino la frecuencia de oscilador en 8MHz
#include <util/delay.h>  // Retardos por software
/* Funcion main */
int main(void)
{
    /* Setup */
    char state = 1;
    char seq1 = 0b01010101;
    char seq2 = 0b00000001;
    char dir = 0;
    DDRD = 0xFF; // Configuro Puerto D como salida
    DDRC &= ~(1 << PORTC0 | 1 << PORTC1);
    DDRB |= (1 << PORTB3 | 1 << PORTB4);
    PORTC |= (1 << PORTC0 | 1 << PORTC1);
    /* Loop */
    while (1)
    {
        PORTB &= ~(1 << PORTB3 | 1 << PORTB4);
        if (!(PINC & (1 << PINC1)))
        {
            PORTB |= (state << 3);
        }

        if (!(PINC & (1 << PINC0)))
        {
            state = (state % 3) + 1;
            seq1 = 0b01010101;
            seq2 = 0b00000001;
            dir = 0;
        }
        switch (state)
        {
        case 1:
            PORTD = seq1;
            seq1 ^= 0xFF;
            _delay_ms(10);
            break;
        case 2:
            PORTD = seq2;
            _delay_ms(10);
            seq2 = seq2 << 1;
            if (seq2 == 0)
            {
                seq2 = 0b00000001;
            }
            break;
        case 3:
            PORTD = seq2;
            _delay_ms(10);
            if (dir)
            {
                seq2 = seq2 >> 1;
            }
            else
            {
                seq2 = seq2 << 1;
            }
            if ((dir && seq2 == 1 << PORTD0) || (~dir && seq2 == 1 << PORTD7))
            {
                dir ^= 1;
            }
            break;
        default:
            state = 1;
            break;
        }
    }
    /* Punto de finalizacion del programa (NO se debe llegar a este lugar) */
    return 0;
}