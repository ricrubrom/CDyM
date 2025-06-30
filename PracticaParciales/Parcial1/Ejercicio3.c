#include <avr/io.h>

#define BUFFER_SIZE 64;
typedef struct
{
  uint8_t buf[BUFFER_SIZE];
  uint8_t read_pos = 0;
  uint8_t write_pos = 0;
} buffer;

buffer rx_buffer;
buffer tx_buffer;

char productor(uint8_t *cadena)
{
  char i = 0;
  while (cadena[i] != '\0')
  {
    if (((rx_buffer.write_pos + 1) % BUFFER_SIZE) == rx_buffer.read_pos)
      return 0; // Buffer lleno
    rx_buffer.buf[rx_buffer.write_pos] = cadena[i++];
    rx_buffer.write_pos = (rx_buffer.write_pos + 1) % BUFFER_SIZE;
  }
  rx_buffer.buf[rx_buffer.write_pos] = '\0';
  while (rx_buffer.buf[rx_buffer.read_pos] != '\0')
  {
    UDR0 = rx_buffer.buf[rx_buffer.read_pos];
    while ((UCSR0A & (1 << TXC0)) == 0)
      ;
    UCSR0A |= (1 << TXC0);
    rx_buffer.read_pos = (rx_buffer.read_pos + 1) % BUFFER_SIZE;
  }
  return 1;
}

char consumidor()
{
  char c_recv;
  do
  {
    if (((tx_buffer.write_pos + 1) % BUFFER_SIZE) == tx_buffer.read_pos)
      return 0; // Buffer lleno
    while ((UCSR0A & (1 << RXC0)) == 0)
      ;
    UCSR0A |= (1 << RXC0);
    c_recv = UDR0;
    tx_buffer.buf[tx_buffer.write_pos] = c_recv;
    tx_buffer.write_pos = (tx_buffer.write_pos + 1) % BUFFER_SIZE;
  } while (c_recv != '\n');
  return 1;
}