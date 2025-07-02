#include <avr/io.h>

static uint8_t tickX;
static uint8_t tickY;
static uint8_t tickZ;

volatile uint8_t dispatch_taskX;
volatile uint8_t dispatch_taskY;
volatile uint8_t dispatch_taskZ;

void timer_init()
{
  TCCR0A = (1 << WGM01);
  TCCR0B = 0b00000111;
  OCR0A = 155;
  TIMSK = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
  tickX++;
  tickY++;
  tickZ++;
  if (tickX == 2)
  {
    dispatch_taskX = 1;
    tickX = 0;
  }
  if (tickY == 5)
  {
    dispatch_taskY = 1;
    tickY = 0;
  }
  if (tickZ == 30)
  {
    dispatch_taskZ = 1;
    tickZ = 0;
  }
}

void task_init()
{
  tickX = 1;
  tickY = 4;
  tickZ = 29;

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