/* Inclusi�n de bibliotecas de c�digo */
#include <avr/io.h>      // Biblioteca para manipular los registros del microcontrolador AVR
#define F_CPU 16000000UL // Definici�n de la frecuencia del oscilador en 16 MHz
#include <util/delay.h>  // Biblioteca para generar retardos por software
#include <avr/interrupt.h>

/* Variables globales */
volatile char state = 1;         // Variable para almacenar el estado actual
volatile char seq1 = 0b01010101; // Secuencia inicial para el estado 1
volatile char seq2 = 0b00000001; // Secuencia inicial para los estados 2 y 3
volatile char dir = 0;           // Direcci�n de desplazamiento para el estado 3 (0: izquierda, 1: derecha)
volatile char pressedChange = 0; // Indicador de cambio de estado con el bot�n

/* Interrupci�n por cambio de estado de los botones */
ISR(PCINT1_vect)
{
    // Apago los LEDs conectados a PB3 y PB4
    PORTB &= ~(1 << PORTB3 | 1 << PORTB4);

    // Si el bot�n conectado a PC1 est� presionado
    if (!(PINC & (1 << PINC1)))
    {
        // Enciendo los LEDs correspondientes al estado actual en PB3 o PB4
        PORTB |= (state << 3);
    }

    // Verifico si el bot�n conectado a PC0 est� presionado para cambiar de estado
    if (!(PINC & (1 << PINC0))) // Si el bot�n est� presionado
    {
        if (!pressedChange) // Si el bot�n no estaba previamente presionado
        {
            // Cambio al siguiente estado (1, 2 o 3)
            state = (state % 3) + 1;
            // Reinicio las secuencias y la direcci�n
            seq1 = 0b01010101;
            seq2 = 0b00000001;
            dir = 0;
            pressedChange = 1; // Indico que el bot�n fue presionado
        }
    }
    else // Si el bot�n fue liberado
    {
        pressedChange = 0; // Indico que el bot�n fue liberado
    }
}

/* Interrupci�n por timer (para evitar retardos bloqueantes) */
ISR(TIMER0_COMPA_vect)
{
    static uint16_t overflowCount = 0;

    // Incrementa el contador cada vez que se genera una interrupci�n
    if (overflowCount++ >= 25) // Alcanza 7000 interrupciones, que corresponde a 100 ms
    {
        switch (state)
        {
        case 1:
            // Estado 1: Alternancia de LEDs en el Puerto D
            PORTD = seq1; // Salida de la secuencia actual
            seq1 ^= 0xFF; // Invierto los bits de la secuencia
            break;

        case 2:
            // Estado 2: Desplazamiento de un bit encendido hacia la izquierda
            PORTD = seq2;     // Salida de la secuencia actual
            seq2 = seq2 << 1; // Desplazo el bit encendido hacia la izquierda
            if (seq2 == 0)    // Si la secuencia se desborda
            {
                seq2 = 0b00000001; // Reinicio la secuencia
            }
            break;

        case 3:
            // Estado 3: Desplazamiento de un bit encendido con cambio de direcci�n
            PORTD = seq2; // Salida de la secuencia actual
            if (dir)      // Si la direcci�n es derecha
            {
                seq2 = seq2 >> 1; // Desplazo el bit encendido hacia la derecha
            }
            else // Si la direcci�n es izquierda
            {
                seq2 = seq2 << 1; // Desplazo el bit encendido hacia la izquierda
            }
            // Cambio de direcci�n si se alcanza el extremo
            if ((dir && seq2 == 1 << PORTD0) || (~dir && seq2 == 1 << PORTD7))
            {
                dir ^= 1; // Invierto la direcci�n
            }
            break;

        default:
            // Estado por defecto: Reinicio al estado 1
            state = 1;
            seq1 = 0b01010101;
            break;
        }
        overflowCount = 0; // Reinicio el contador
    }
}

/* Configuraci�n inicial */
void init()
{
    DDRD = 0xFF;                          // Configuro el Puerto D como salida
    DDRC &= ~(1 << PORTC0 | 1 << PORTC1); // Configuro los pines PC0 y PC1 del Puerto C como entradas
    DDRB |= (1 << PORTB3 | 1 << PORTB4);  // Configuro los pines PB3 y PB4 del Puerto B como salidas
    PORTC |= (1 << PORTC0 | 1 << PORTC1); // Activo resistencias pull-up en los pines PC0 y PC1

    /* Configuro las interrupciones de los botones del puerto C */
    PCICR |= (1 << PCIE1);                   // Habilito la interrupci�n en el Puerto C
    PCMSK1 |= (1 << PCINT8) | (1 << PCINT9); // Configuro los pines PC0 y PC1 para interrupciones

    /* Configuro las interrupciones por clock (timer) */
    TCCR0A = 0;                          // Modo normal, no PWM
    TCCR0B = (1 << WGM02) | (1 << CS02); // Modo CTC y prescaler de 1

    // Configurar el valor de comparaci�n (para interrupci�n cada 1 ms)
    OCR0A = 249; // Timer se reinicia cuando llega a 249 (16 MHz / 256 prescaler / 1000 Hz)

    // Habilitar la interrupci�n del Timer0
    TIMSK0 |= (1 << OCIE0A);

    // Habilitar interrupciones globales
    sei();
}

/* Funci�n principal */
int main(void)
{
    init(); // Inicializaci�n del sistema

    /* Bucle principal */
    while (1)
    {
        // El bucle principal est� vac�o, ya que las acciones se manejan mediante interrupciones
    }

    /* Punto de finalizaci�n del programa (NO se debe llegar a este lugar) */
    return 0;
}
