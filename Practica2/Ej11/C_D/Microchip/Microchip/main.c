#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum
{
	ESPERA,
	REBOTE,
	VALIDACION,
	ACTIVADO
} EstadoBoton;

volatile EstadoBoton estado = ESPERA;
volatile uint8_t contador_rebote = 0;
volatile uint8_t rebote_activo = 0;
volatile uint8_t boton_presionado_anterior = 1;

void actualizar_leds_estado(EstadoBoton est)
{
	PORTC = (PORTC & 0xF0) | (1 << est);
}

ISR(PCINT0_vect)
{
	uint8_t estado_boton = (PINB & (1 << PB0)) ? 1 : 0;

	// Solo reaccionamos al flanco de bajada
	if (estado == ESPERA && estado_boton == 0 && boton_presionado_anterior == 1)
	{
		estado = REBOTE;
		actualizar_leds_estado(estado);
		rebote_activo = 1;
		contador_rebote = 0;
	}

	// Guardamos el estado anterior para detectar flancos
	boton_presionado_anterior = estado_boton;
}

ISR(TIMER0_COMPA_vect)
{
	if (rebote_activo)
	{
		contador_rebote++;

		if (contador_rebote >= 20)
		{
			rebote_activo = 0;

			if ((PINB & (1 << PB0)) == 0)
			{
				estado = VALIDACION;
				actualizar_leds_estado(estado);

				PORTB ^= (1 << PB5); // Toggle del LED

				estado = ACTIVADO;
				actualizar_leds_estado(estado);
			}
			else
			{
				estado = ESPERA;
				actualizar_leds_estado(estado);
			}
		}
	}

	// Si estamos en ACTIVADO y el botón ya fue soltado, volvemos a ESPERA
	if (estado == ACTIVADO && (PINB & (1 << PB0)))
	{
		estado = ESPERA;
		actualizar_leds_estado(estado);
	}
}

void setup_timer0()
{
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS01) | (1 << CS00);
	OCR0A = 249;
	TIMSK0 |= (1 << OCIE0A);
}

void setup()
{
	DDRB |= (1 << PB5);	 // LED como salida
	DDRB &= ~(1 << PB0); // Botón como entrada
	PORTB |= (1 << PB0); // Pull-up activado

	DDRC |= 0x0F;
	PORTC &= 0xF0;

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0);

	setup_timer0();

	sei();
}

int main(void)
{
	setup();

	while (1)
	{
		// todo se maneja por interrupciones
	}
}
