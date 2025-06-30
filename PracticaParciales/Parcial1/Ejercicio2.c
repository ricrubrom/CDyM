#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

typedef enum
{
  RELOJ,
  NOTIFICAR,
  RELOJ_ALARMA,
  RELOJ_PAUSA
} MEF_States;

typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
} time_t;

MEF_States state = RELOJ;
time_t passed_time;
time_t cur_time;
time_t alarm_time; // Supongo que viene dado
uint8_t pause_pressed = 0;
uint8_t paused_times = 0;
volatile uint8_t time_flag = 0;
volatile uint8_t tick = 0;

void change_state(MEF_States new_state)
{
  state = new_state;
  passed_time.sec = 0;
  passed_time.min = 0;
  passed_time.hour = 0;
}

uint8_t compare(time_t cur, time_t alarm)
{
  return (cur.hour == alarm.hour) && (cur.min == alarm.min) && (cur.sec == alarm.sec);
}

void MEF_Update()
{
  switch (state)
  {
  case RELOJ:
  {
    if compare (cur_time, alarm_time)
    {
      pause_pressed = 0;
      paused_times = 0;
      change_state(NOTIFICAR);
    }
    break;
  }
  case NOTIFICAR:
  {
    notificar(); // La supongo dada
    if ((PINC & (1 << PINC1)) == 0)
    {
      change_state(RELOJ);
      break;
    }
    if (!pause_pressed && ((PINC & (1 << PINC0)) == 0))
    {
      pause_pressed = 1;
      change_state(RELOJ_PAUSA);
      break;
    }
    if (passed_time.min == 1)
    {
      if pause_pressed
      {
        paused_times++;
        change_state(RELOJ_PAUSA);
        break;
      }
      else
      {
        change_state(RELOJ_ALARMA);
        break;
      }
    }
    break;
  }
  case RELOJ_ALARMA:
  {
    if (PINC & (1 << PINC1) == 0)
    {
      change_state(RELOJ);
      break;
    }
    if (passed_time.min == 5)
    {
      change_state(NOTIFICAR);
      break;
    }
    break;
  }
  case RELOJ_PAUSA:
  {
    if (PINC & (1 << PINC1) == 0)
    {
      change_state(RELOJ);
      break;
    }
    if (paused_times == 3)
    {
      change_state(RELOJ);
      break;
    }
    if (passed_time.min == 5)
    {
      change_state(NOTIFICAR);
      break;
    }
    break;
  }
  default:
    break;
  }
}

ISR(TIMER0_COMPA_vect)
{
  time_flag = 1;
  tick = (tick % 100) + 1
}

void update_time()
{
  passed_time.sec += 1;
  if (passed_time.sec == 60)
  {
    passed_time.sec = 0;
    passed_time.min += 1;
    if (passed_time.min == 60)
    {
      passed_time.min = 0;
      passed_time.hour += 1;
      if (passed_time.hour == 24)
        passed_time.hour = 0;
    }
  }
}

int main()
{
  // Supongo pulsadores en PINC0 y PINC1
  DDRC &= ~((1 << PINC0) | (1 << PINC1));
  PORTC |= (1 << PINC0) | (1 << PINC1);
  // Supongo que no tengo que mostrar la hora

  TCCR0A |= (1 << WGM01);
  TCCR0B = (1 << CS02) | (1 << CS00);
  TIMSK0 |= (1 << OCIE0A);

  OCR0A = 156;
  sei();
  while (1)
  {
    if (time_flag)
    {
      if (tick == 100)
      {
        cur_time = get_time(); // La supongo dada
        update_time();
      }
      MEF_Update();
      time_flag = 0;
    }
  }
}