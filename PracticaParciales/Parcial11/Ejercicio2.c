#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

uint8_t pressed[2];
int delay;

int main()
{
  // Supongo led en PB0
  DDRD &= ~((1 << DDRD0) | (1 << DDRD7));
  PORTD |= (1 << PORTD0) | (1 << PORTD7);
  DDRB |= (1 << DDRB0);
  pressed[0] = 0;
  pressed[1] = 0;
  delay = 100;

  while (1)
  {
    if (!pressed[0])
    {
      if (!(PIND & (1 << PIND0)))
      {
        pressed[0] = 1;
        if (delay <= 900)
          delay += 100;
      }
    }
    else
    {
      if ((PIND & (1 << PIND0)))
      {
        pressed[0] = 0;
      }
    }
    if (!pressed[1])
    {
      if (!(PIND & (1 << PIND7)))
      {
        pressed[1] = 1;
        if (delay >= 200)
          delay -= 100;
      }
    }
    else
    {
      if ((PIND & (1 << PIND7)))
      {
        pressed[1] = 0;
      }
    }
    PORTB ^= (1 << PORTB0);
    _delay_ms(delay);
  }
}