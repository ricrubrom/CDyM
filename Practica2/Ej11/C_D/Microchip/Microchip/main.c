#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef enum
{
	ESPERA,
	REBOTE,
	VALIDACION,
	ACTIVADO
} EstadoBoton;

volatile EstadoBoton estado = ESPERA;
volatile uint8_t boton_presionado = 0;

void actualizar_leds_estado(EstadoBoton est)
{
	PORTC = (PORTC & 0xF0) | (1 << est); // Solo C0�C3 se usan para estados
}

ISR(PCINT0_vect)
{
	if ((PINB & (1 << PB0)) == 0)
	{
		if (estado == ESPERA)
		{
			estado = REBOTE;
			actualizar_leds_estado(estado);
		}
	}
}

void MEF_antirebote()
{
	switch (estado)
	{
	case REBOTE:
		_delay_ms(20); // Tiempo para eliminar rebotes
		if ((PINB & (1 << PB0)) == 0)
		{
			estado = VALIDACION;
		}
		else
		{
			estado = ESPERA;
		}
		actualizar_leds_estado(estado);
		break;

	case VALIDACION:
		boton_presionado = 1;
		PORTB ^= (1 << PB5); // Cambiar estado del LED
		estado = ACTIVADO;
		actualizar_leds_estado(estado);
		break;

	case ACTIVADO:
		if ((PINB & (1 << PB0)) != 0)
		{
			estado = ESPERA;
			actualizar_leds_estado(estado);
		}
		break;

	default:
		break;
	}
}

void setup()
{
	DDRB |= (1 << PB5);	 // PB5 como salida (LED)
	DDRB &= ~(1 << PB0); // PB0 como entrada (bot�n)
	PORTB |= (1 << PB0); // Pull-up activado

	DDRC |= 0x0F; // PC0�PC3 como salida para mostrar estado
	PORTC &= 0xF0;

	// Habilitar interrupciones por cambio de pin en PB0
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0);

	sei(); // Habilitar interrupciones globales
}

int main(void)
{
	setup();

	while (1)
	{
		MEF_antirebote();
	}
}
