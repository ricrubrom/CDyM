#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#define F_CPU 16000000UL

#define DEBOUNCE_TIME0 100
#define DEBOUNCE_TIME1 200

#define DEBOUNCE_TIME(i) 10 * (i + 1)

typedef enum
{
  REPOSO,
  APRETANDO,
  APRETADO,
  SOLTANDO
} MEF_State;

MEF_State states[2] = [ REPOSO, REPOSO ];
uint8_t tick[2] = [ 0, 0 ];

void MEF_Update(uint8_t button_pin)
{
  switch (states[button_pin])
  {
  case REPOSO:
    if (!(PINC & (1 << button_pin)))
    {
      tick[button_pin] = 0;
      states[button_pin] = APRETANDO;
    }
    break;
  case APRETANDO:
    tick[button_pin]++;
    if (tick[button_pin] >= DEBOUNCE_TIME(button_pin))
    {
      states[button_pin] = APRETADO;
    }
    break;
  case APRETADO:
    if (PINC & (1 << button_pin))
    {
      tick[button_pin] = 0;
      states[button_pin] = SOLTANDO;
    }
    break;
  case SOLTANDO:
    tick[button_pin]++;
    if (tick[button_pin] >= DEBOUNCE_TIME(button_pin))
    {
      states[button_pin] = REPOSO;
    }
    break;
  default:
    break;
  }
}

int main()
{
  // Pulsadores en PINC0 y PINC1
  DDRC &= ~((1 << PINC0) | (1 << PINC1)); // Entradas
  PORTC |= ((1 << PINC0) | (1 << PINC1)); // Pull ups

  while (1)
  {
    MEF_Update(PINC0);
    MEF_Update(PINC1);
    _delay_ms(10) // Creo que 10ms es un buen compromiso entre tiempo de respuesta del sistema ante la accion, y no ejecutar tantas veces la MEF.
  }
  return 0;
}