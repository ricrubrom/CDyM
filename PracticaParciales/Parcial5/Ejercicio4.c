#include <avr/io.h>

volatile uint8_t tick;
volatile uint8_t seconds;
volatile uint8_t switch_flag;

void timer_init()
{
  TCCR0A = (1 << WGM01);
  TCCR0B = 0b00000111;
  OCR0A = 155;
  TIMSK = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
  tick++;
  if (tick >= 100)
  {
    tick = 0;
    seconds++;
    if (seconds >= 10)
    {
      seconds = 0;
      switch_flag = 1;
    }
  }
}

void init()
{
  timer_init();

  DDRC |= (1 << DDRC2); // Salida

  tick = 0;
  seconds = 0;
  switch_flag = 0;
}

void main()
{
  init();
  sei();
  while (1)
  {
    if (switch_flag)
    {
      PORTC ^= (1 << PORTC2);
      switch_flag = 0;
    }
  }
  return 0;
}