#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define F_CPU 16000000UL

volatile uint8_t Dispatch1A = 1;
volatile uint8_t Dispatch1B = 1;
volatile uint8_t Dispatch2 = 1;
volatile uint8_t Dispatch3 = 1;

ISR(TIMER1_COMPA_vect) // Interrumpe cada 20ms
{
  static uint8_t tick1 = 0;
  static uint8_t tick2 = 0;
  static uint8_t tick3 = 0;
  tick1++;
  tick2++;
  tick3++;
  if (tick1 % 5 == 0)
  {
    Dispatch1A = 1;
  }
  if (tick1 % 10 == 0)
  {
    Dispatch1B = 1;
    tick1 = 0;
  }
  if (tick2 % 8 == 0)
  {
    Dispatch2 = 1;
    tick2 = 0;
  }
  if (tick3 % 25 == 0)
  {
    Dispatch3 = 1;
    tick3 = 0;
  }
}

void dispatcher()
{
  if (Dispatch1A || Dispatch1B)
  {
    Tarea1(); // Adentro pregunta por sus flags
    Dispatch1A = 0;
    Dispatch1B = 0;
  }
  if (Dispatch2)
  {
    Tarea2();
    Dispatch2 = 0;
  }
  if (Dispatch3)
  {
    Tarea3();
    Dispatch3 = 0;
  }
}

void timer_init()
{

  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC, 1024
  OCR1A = 311;
  TIMSK1 = (1 << OCIE1A);
  sei();
}