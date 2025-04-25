#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU 16000000UL

volatile uint8_t overflow_count = 0;

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
	if (overflow_count >= 24) // Aproximadamente 50 ms
	{
		PORTB ^= (1 << PB0); // Toggle PB0 (LED)
		overflow_count = 0;
	}
}

int main(void)
{
	DDRB |= (1 << PB0);		// PB0 como salida (LED)
	PORTB &= ~(1 << PB0); // LED apagado inicialmente

	Timer0_Init(); // Inicializar Timer0
	sei();				 // Habilitar interrupciones globales

	while (1)
	{
		// Nada en el loop principal, todo se maneja con interrupci�n
	}
}
