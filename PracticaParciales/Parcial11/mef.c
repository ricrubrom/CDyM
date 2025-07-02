#include "mef.h"

MEF_states state;
static uint8_t buffer[BUFFER_SIZE];
static uint8_t start_flag;
static uint8_t read_pos;

void MEF_init()
{
  state = REPOSO;
  for (int i = 0; i < BUFFER_SIZE; i++)
    buffer[i] = 0;
  start_flag = 0;
  DDRC |= (1 << PINC0);
  UCSR0C = 0b00000110;
  UCSR0B = 0b00001000;
  UBRR0L = 103 // BD=9600bps;
}

void send_string(uint8_t str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    buffer[i] = str[i]
  }
  start_flag();
}
// REPOSO, INICIO, ESPERA, DATO, and FIN
void MEF_update()
{
  switch (state)
  {
  case REPOSO:
    if (start_flag)
    {
      state = TRANSFER;
      read_pos = 0;
    }
    break;
  case TRANSFER:
    UDR0 = buffer[read_pos++];
    state = ESPERA;
  case ESPERA:
    if (buffer[read_pos] != '\0')
    {
      if !(UCSR0A & (1 << TXC0)) // TXC0 vs UDRE0??
      {
        state = TRANSFER;
      }
    }
    else
    {
      state = REPOSO;
    }
    break;
  default:
    break;
  }
}