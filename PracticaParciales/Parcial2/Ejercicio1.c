#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdint.h>

uint8_t tick = 0;

void tarea1()
{
  if (!(tick % 1000))
    PORTB ^= (1 << PORTB0);
}
void tarea2()
{
  static uint8_t pressed = 0;
  if (!(tick % 100))
  {
    if (!pressed)
    {
      if (!(PORTC & (1 << PORTC0)))
      {
        pressed = 1;
        PORTB |= (1 << PORTB1);
      }
    }
    else
    {
      static uint8_t hundred_ticks_pressed = 0;
      hundred_ticks_pressed++;
      if (hundred_ticks_pressed == 5)
      {
        hundred_ticks_pressed = 0;
        pressed = 0;
        PORTB &= ~(1 << PORTB1);
      }
    }
  }
}
void tarea3()
{
  if (!(tick & 5))
  {
    if (UCSR0A & (1 << RXC0) == 0)
    {
      uint8_t c_recv = UDR0;
      while (!(UCSR0A & (1 << UDRE0)))
        ;
      UDR0 = dato;
    }
  }
}

int main(void)
{
  // Cód. de inic.
  while (1)
  {
    Tarea1(); // Cada 1 sg
    Tarea2(); // Sondea PC0 cada 100ms, si apretada prende PB1 0.5sg==500ms
    Tarea3(); // Cada 5ms
    _delay_ms(1);
    tick += 1;
  }
  return 0;
}
