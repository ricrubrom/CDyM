/*
 * keypad.c
 *
 * Created: 29/4/2025 14:12:31
 *  Author: mater
 */

#include "lcd.h"
#include <avr/io.h>
#include <stdint.h>
#include "keypad.h"

// Definición del teclado matricial
const uint8_t keypad_keys[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'};

/**
 * @brief Inicializa el teclado matricial
 */
void KEYPAD_init(void)
{
  // Configurar filas como salidas
  DDRB |= (1 << ROWA) | (1 << ROWB) | (1 << ROWC);
  DDRD |= (1 << ROWD);

  // Configurar columnas como entradas con pull-up
  DDRD &= ~((1 << COLA) | (1 << COLB) | (1 << COLC) | (1 << COLD));
  PORTD |= (1 << COLA) | (1 << COLB) | (1 << COLC) | (1 << COLD);
}

/**
 * @brief Escanea el teclado matricial en busca de teclas presionadas
 * @param key Puntero para almacenar la tecla detectada
 * @return 1 si se detectó un flanco de bajada (nueva tecla presionada), 0 en caso contrario
 */
uint8_t KEYPAD_scan(uint8_t *key)
{
  static uint8_t last_key = 0xFF; // Guarda la tecla previa (sin presionar al inicio)
  uint8_t current_key = 0xFF;

  for (uint8_t row = 0; row < 4; row++)
  {
    // Activar todas las filas (HIGH)
    PORTB |= (1 << ROWA) | (1 << ROWB) | (1 << ROWC);
    PORTD |= (1 << ROWD);

    // Desactivar la fila actual (LOW)
    switch (row)
    {
    case 0:
      PORTB &= ~(1 << ROWA);
      break;
    case 1:
      PORTB &= ~(1 << ROWB);
      break;
    case 2:
      PORTB &= ~(1 << ROWC);
      break;
    case 3:
      PORTD &= ~(1 << ROWD);
      break;
    }

    _delay_us(DEBOUNCE_DELAY_US); // Espera para estabilización

    // Escanear columnas (activas en LOW)
    if (!(PIND & (1 << COLA)))
    {
      current_key = keypad_keys[row * 4];
      break;
    }
    if (!(PIND & (1 << COLB)))
    {
      current_key = keypad_keys[row * 4 + 1];
      break;
    }
    if (!(PIND & (1 << COLC)))
    {
      current_key = keypad_keys[row * 4 + 2];
      break;
    }
    if (!(PIND & (1 << COLD)))
    {
      current_key = keypad_keys[row * 4 + 3];
      break;
    }
  }

  // Detectar flanco de bajada (nueva tecla distinta a la anterior)
  if (current_key != 0xFF && current_key != last_key)
  {
    *key = current_key;
    last_key = current_key;
    return 1;
  }

  // Si no se presiona ninguna tecla, reiniciar el estado
  if (current_key == 0xFF)
  {
    last_key = 0xFF;
  }

  return 0; // No se detectó nueva tecla
}
