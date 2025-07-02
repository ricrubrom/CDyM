#include <avr/io.h>
#include <stdint.h>

#define F_CPU 16000000UL

void init(uint8_t str[4])
{
  // PB Entrada
  DDRB = 0x00;
  PORTB = 0x11; // Pull-ups
  for (int i = 0; i < 4; i++)
    str[i] = 0;
}

void transform(uint8_t data, uint8_t str[4])
{
  uint8_t i;
  uint8_t remain;
  for (i = 2; i >= 0; i--)
  {
    remain = data % 10;
    str[i] = remain + '0';
    data /= 10;
  }
  // str[3] = '\0';
}

int main()
{
  uint8_t str[4];
  uint8_t data;
  init(str);

  while (1)
  {
    data = ~(PINB);
    transform(data, str);
  }
  return 0
}
