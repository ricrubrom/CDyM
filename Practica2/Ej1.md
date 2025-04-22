# **Ejercicio No 1: Display LCD**

## a) Características y Comandos del LCD 1602A

### 📌 Características principales:

- LCD de **16 caracteres por 2 líneas**.
- Controlado por el **HD44780**.
- Modo de operación en **4 bits o 8 bits**.
- Pines de control: `RS`, `RW`, `E`.
- Pines de datos: `D0` a `D7`.
- Alimentación: **5V**.
- Requiere un **potenciómetro** para ajuste de contraste.

### 🧾 Comandos básicos:

| Comando      | Descripción                   |
| ------------ | ----------------------------- |
| `0x01`       | Limpiar pantalla              |
| `0x02`       | Retornar cursor al inicio     |
| `0x0C`       | Pantalla ON, cursor OFF       |
| `0x38`       | 8 bits, 2 líneas, 5x8         |
| `0x28`       | 4 bits, 2 líneas, 5x8         |
| `0x06`       | Mover cursor hacia la derecha |
| `0x80 + pos` | Posicionar cursor en DDRAM    |

---

## b) Diagrama esquemático en Proteus

📌 **A realizar en Proteus**: conectar el **LCD 1602A** en modo 4 bits y el **teclado matricial 4x4** al microcontrolador (según figura del kit de clase).

---

## c) Compatibilidad de niveles lógicos

- El **LCD 1602A** funciona con **niveles TTL de 5V**, al igual que la mayoría de los microcontroladores del curso (por ejemplo, ATmega328P).
- ✔️ **Compatible directamente**, sin necesidad de conversores de nivel.

---

## d) Funciones de biblioteca `lcd.h` y `lcd.c`

### 🔧 Funciones clave:

- **`LCDinit()`**  
  Inicializa el LCD:

  - Configura el modo de 4 bits.
  - Enciende el display sin cursor.
  - Borra la pantalla.
  - Sitúa el cursor en el inicio.

- **`LCDgotoxy(uint8_t x, uint8_t y)`**  
  Posiciona el cursor:

  - `x`: columna (0–15)
  - `y`: fila (0 o 1)
  - Calcula dirección DDRAM y envía comando.

- **`LCDstring(char *str)`**  
  Muestra una cadena:
  - Recorre carácter por carácter y lo envía al display usando el comando correspondiente.

