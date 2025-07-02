#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t dispatch_taskX;
volatile uint8_t dispatch_taskY;
volatile uint8_t dispatch_taskZ;

ISR(TIMER0_COMPA_vect)
{
  static uint8_t tickX = 1;
  static uint8_t tickY = 4;
  static uint8_t tickZ = 29;
  tickX++;
  tickY++;
  tickZ++;
  if (tickX >= 2)
  {
    tickX = 0;
    dispatch_taskX = 1;
  }
  if (tickY >= 5)
  {
    tickY = 0;
    dispatch_taskY = 1;
  }
  if (tickZ >= 30)
  {
    tickZ = 0;
    dispatch_taskZ = 1;
  }
}

void initTimer()
{
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS00) | (1 << CS01) | (1 << CS02);
  OCR0A = 155;
  TIMSK0 = (1 << OCIE0A);
  sei();
}

void initTasks()
{
  dispatch_taskX = 0;
  dispatch_taskY = 0;
  dispatch_taskZ = 0;
}

void dispatcher()
{
  if (dispatch_taskX)
  {
    taskX();
    dispatch_taskX = 0;
  }
  if (dispatch_taskY)
  {
    taskY();
    dispatch_taskY = 0;
  }
  if (dispatch_taskZ)
  {
    taskZ();
    dispatch_taskZ = 0;
  }
}