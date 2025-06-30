#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#define F_CPU 16000000

typedef enum
{
  CERRADO,
  SUBIENDO,
  FRENADO,
  BAJANDO
} MEF_States;

MEF_States state = CERRADO;
volatile uint8_t time_flag = 0;

ISR(TIMER0_COMPA_vect)
{
  time_flag = 1;
}

uint8_t check_button()
{
  return !(PINC & (1 << PINC0))
}

void MEF_Update()
{
  switch (state)
  {
  case CERRADO:
    if (check_button())
    {
      PORTB &= ~(1 << PORTB4);
      PORTB |= (1 << PORTB3); // Apago verde, prendo rojo
      PORTB |= (1 << PORTB1); // Prendo motor subida
      state = SUBIENDO;
    }
    break;
  case SUBIENDO:
    //  reach_top() supongo dada
    if (reach_top() || check_button())
    {
      PORTB &= ~(1 << PORTB1); // Apago motor subida
      state = FRENADO;
    }
    break;
  case FRENADO:
    if (check_button())
    {
      PORTB |= (1 << PORTB2); // Prendo motor bajada
      state = BAJANDO;
    }
    break;
  case BAJANDO:
    // reach_bottom() supongo dada
    if (reach_bottom())
    {
      PORTB &= ~(1 << PORTB2); // Apago motor bajada
      PORTB &= ~(1 << PORTB3);
      PORTB |= (1 << PORTB4); // Apago rojo, prendo verde
      state = CERRADO;
    }
    break;
  default:
    break;
  }
}

int main()
{
  // Inicializacion
  TCCR0A = (1 << WGM01);              // CTC
  TCCR0B = (1 << CS02) | (1 << CS00); // 1024
  TIMSK0 = (1 << OCIE0A);             // Interrupcion Compare
  OCR0A = 156;                        // Valor de top

  // Supongo pulsador en PORTC0, motor subida PB1, motor bajada PB2, semaforo rojo PB3, semaforo Verde PB4
  DDRC &= ~(1 << DDRC0);                                             // Entrada
  DDRB |= (1 << DDRB1) | (1 << DDRB2) | (1 << DDRB3) | (1 << DDRB4); // Salida
  PORTB |= (1 << PORTB4);                                            // Prendo el led por default
  PORTC |= (1 << PORTC0);                                            // Pullup
  sei();
  while (1)
  {
    if (time_flag)
    {
      MEF_Update();
      time_flag = 0;
    }
  }
}