#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL

volatile uint8_t tickX = 0;
volatile uint8_t tickY = 0;

volatile uint8_t dispatchX = 0;
volatile uint8_t dispatchY = 0;

void taskX()
{
  // Supongo que el led 1 esta en el PB0
  PORTB ^= (1 << PORTB0);
}

void taskY()
{
  // Supongo que el pulsador esta en PC0, y el led2 en PB1
  static uint8_t pressed = 0;
  static uint8_t taskY_exec = 0;

  if (!pressed)
  {
    if (!(PINC & (1 << PINC0)))
    {
      pressed = 1;
      PORTB |= (1 << PORTB1);
      return;
    }
  }

  taskY_exec++;
  if (taskY_exec >= 10)
  {
    pressed = 0;
    taskY_exec = 0;
    PORTB &= ~(1 << PORTB1);
  }
}

void seosScheduleTask()
{
  tickX++;
  tickY++;
  if (tickX >= 250)
  {
    tickX = 0;
    dispatchX = 1;
  }
  if (tickY >= 50)
  {
    tickY = 0;
    dispatchY = 1;
  }
}

void seosDispatchTask()
{
  if (dispatchX)
  {
    taskX();
    dispatchX = 0;
  }
  if (dispatchY)
  {
    taskY();
    dispatchY = 0;
  }
}