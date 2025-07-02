#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define TICK 64 / (F_CPU * 1.0)

uint16_t reads[2];
uint8_t cur_read;
uint8_t flag;
float period;

int init(uint8_t flanco)
{
  reads[0] = 0;
  reads[1] = 0;
  cur_read = 0;
  period = 0;

  TCCR1A = 0; // Normal
  TCCR1B = (flanco << ICES1) | (1 << CS11) | (1 << CS10);

  TIMSK1 = (1 << ICIE1);
  sei();
}

ISR(TIMER1_CAPT_vect)
{
  reads[cur_read++] = ICR1;
  cur_read = cur_read % 2;
  flag = 1;
}

void calculate_period()
{
  uint16_t delta;
  if (reads[0] > reads[1])
    delta = (0xFFFF - reads[0]) + reads[1] + 1;
  else
    delta = reads[1] - reads[0];

  period = delta * TICK;
}

int main()
{
  uint8_t flanco = 1;
  init(flanco);

  while (1)
  {
    if (flag)
    {
      calculate_period();
      flag = 0
    }
  }

  return 0;
}