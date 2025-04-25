// ROJO - VERDE - AMARILLO

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU 16000000UL

volatile uint16_t overflow_count = 0;
volatile uint8_t led_state = 0;

void Timer0_Init(void)
{
	// Set prescaler to 64: CS01 y CS00 = 1, CS02 = 0 ? 0b011
	TCCR0A = 0x00;											// Modo normal
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
	TIMSK0 = (1 << TOIE0);							// Habilitar interrupci�n por overflow
	TCNT0 = 0;													// Inicializar contador
}

ISR(TIMER0_OVF_vect)
{
	overflow_count++;
	if (overflow_count >= 500) // Aproximadamente 1sg
	{
		switch (led_state)
		{
		case 0:
			PORTB &= ~(1 << PB5); // Apagar LED rojo
			PORTB |= (1 << PB6);	// Encender LED verde
			led_state = 1;
			break;
		case 1:
			PORTB &= ~(1 << PB6); // Apagar LED verde
			PORTB |= (1 << PB7);	// Encender LED amarillo
			led_state = 2;
			break;
		case 2:
			PORTB &= ~(1 << PB7); // Apagar LED amarillo
			PORTB |= (1 << PB5);	// Encender LED rojo
			led_state = 0;
			break;
		}
		overflow_count = 0;
	}
}

int main(void)
{
	DDRB |= ((1 << PB5) | (1 << PB6) | (1 << PB7)); // PB05, 6, y 7 como salida (LED)
	PORTB &= ~((1 << PB6) | (1 << PB7));						// LEDs apagados inicialmente
	PORTB |= (1 << PB5);														// Estado incial del LED en PB5 (encendido)

	Timer0_Init(); // Inicializar Timer0
	sei();				 // Habilitar interrupciones globales

	while (1)
	{
		// Nada en el loop principal, todo se maneja con interrupci�n
	}
}
