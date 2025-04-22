# **Ejercicio No 2: Teclado Matricial 4x4**

## a) Funcionamiento y conexión

### 🔢 Descripción:

- El teclado 4x4 es una matriz de 4 filas × 4 columnas.
- Cada tecla está ubicada en la intersección de una fila y una columna.
- Para detectar una tecla:
  - Se activan las filas una a una (salidas).
  - Se leen las columnas (entradas con pull-up).
  - Si al activar una fila se detecta nivel bajo en una columna, esa tecla fue presionada.

### 🔌 Esquema de conexión:

- Conectar las **filas a pines configurados como salida**.
- Conectar las **columnas a pines configurados como entrada con resistencias pull-up**.

## b) Función de escaneo

```c
#include <avr/io.h>
#include <stdint.h>

uint8_t KEYPAD_Scan(uint8_t *key) {
    const char keys[4][4] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
    };

    for (uint8_t row = 0; row < 4; row++) {
        // -----------------------
        // Activar fila: ponemos en alto todas las filas y en bajo la que queremos activar
        // Supuesto: filas conectadas a PB0–PB3
        // -----------------------
        PORTB |= 0x0F;            // Todas las filas en alto
        PORTB &= ~(1 << row);     // Activamos la fila deseada (única en bajo)

        // Esperar un pequeño tiempo para que estabilice la señal (opcional)
        // _delay_us(1); // Si usás <util/delay.h>

        for (uint8_t col = 0; col < 4; col++) {
            // -----------------------
            // Leer columna: verificamos si la columna tiene nivel bajo (tecla presionada)
            // Supuesto: columnas conectadas a PD4–PD7
            // -----------------------
            if ((PIND & (1 << (col + 4))) == 0) {
                *key = keys[row][col];
                return 1;
            }
        }
    }

    return 0; // Ninguna tecla presionada
}

```

---

