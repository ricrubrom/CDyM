## **Ejercicio No 6: Implementación de Máquinas de Estado Finitos (MEF)**

### a) ¿Qué es un modelo de Estados Finitos? ¿Qué elementos contiene? ¿Cómo se especifica?

Un **Modelo de Estados Finitos (MEF)** es una representación matemática que describe el comportamiento de un sistema en función de sus posibles estados y las transiciones entre ellos. Los sistemas que utilizan MEF responden a eventos o entradas y cambian de estado en consecuencia.

**Elementos de un MEF:**

1. **Estados**: Son las configuraciones en las que el sistema puede estar. Por ejemplo, "Encendido" y "Apagado".
2. **Entradas**: Señales externas que pueden causar un cambio de estado.
3. **Transiciones**: Condiciones que determinan cuándo el sistema pasa de un estado a otro.
4. **Acciones**: Operaciones que se ejecutan cuando el sistema entra en un estado o cuando se realiza una transición.

**Especificación**:
El modelo se especifica con una tabla de estados, un diagrama de estados o una lista de condiciones para las transiciones. En el código, generalmente se utiliza una estructura de control, como `switch` o `if-else`, para representar las transiciones entre los estados.

---

### b) ¿Cuál es la diferencia entre el modelo propuesto por Moore y el de Mealy?

- **Modelo de Moore**:

  - La salida depende **solo del estado** en el que se encuentra el sistema.
  - No depende de las entradas, solo de los estados actuales.
  - Ejemplo: Un semáforo cuya salida es siempre un color específico según el estado (rojo, verde, amarillo).

- **Modelo de Mealy**:
  - La salida depende **del estado y de las entradas**.
  - Las salidas pueden cambiar según las entradas, incluso si el estado no cambia.
  - Ejemplo: Un semáforo que cambia el color dependiendo del estado y de un botón de emergencia.

---

### c) Describa diferentes maneras para implementar en C un modelo MEF, ¿Cómo conviene declarar las variables de estados? De un ejemplo resumido del código para una posible implementación.

En C, un modelo MEF puede implementarse utilizando variables que representen los **estados** y **transiciones**. Las formas más comunes son usar `enum` para los estados y `switch-case` o `if-else` para las transiciones.

**Declaración de las variables de estados:**

- Se recomienda usar **`enum`** para representar los estados, lo que mejora la legibilidad y mantenimiento del código.

**Ejemplo de implementación:**

```c
#include <stdint.h>

typedef enum {
    ESTADO_INICIAL,
    ESTADO_CARGANDO,
    ESTADO_EN_EJECUCION,
    ESTADO_FINAL
} estado_t;

estado_t estado_actual = ESTADO_INICIAL;

void actualizar_estado(uint8_t evento) {
    switch (estado_actual) {
        case ESTADO_INICIAL:
            if (evento == 1) {
                estado_actual = ESTADO_CARGANDO;
            }
            break;
        case ESTADO_CARGANDO:
            if (evento == 2) {
                estado_actual = ESTADO_EN_EJECUCION;
            }
            break;
        case ESTADO_EN_EJECUCION:
            if (evento == 3) {
                estado_actual = ESTADO_FINAL;
            }
            break;
        case ESTADO_FINAL:
            // El sistema ya está en el estado final
            break;
    }
}
```

---

### d) ¿Cómo se inicializa una MEF? ¿Cómo se actualiza una MEF?

**Inicialización de la MEF:**
La inicialización de una MEF se realiza configurando la **variable del estado actual** al estado inicial. Esto es importante para asegurar que el sistema comience desde un estado conocido.

**Actualización de la MEF:**
La MEF se actualiza al **cambiar el estado** en función de los eventos o entradas, lo cual puede hacerse mediante un ciclo o función periódica que revise las condiciones de las transiciones.

```c
estado_actual = ESTADO_INICIAL;  // Inicialización de la MEF

// Dentro de un ciclo principal o función de actualización
actualizar_estado(evento);  // Actualiza el estado en función del evento
```

---

### e) Analice diferencias y similitudes de una implementación MEF en lenguaje C y en lenguaje VHDL partiendo del mismo modelo de la MEF.

**Similitudes**:

- Ambas implementaciones describen un sistema de estados y transiciones.
- En C y VHDL, los estados se pueden representar con variables o señales, y las transiciones se gestionan mediante estructuras de control (como `if-else` en C y `case` en VHDL).
- En ambas implementaciones, el sistema se mueve de un estado a otro en respuesta a entradas.

**Diferencias**:

- **En C**:

  - Es más orientado a programas secuenciales que se ejecutan en una CPU.
  - Se utiliza programación estructurada con ciclos y funciones.
  - Se puede usar directamente en sistemas embebidos o aplicaciones que no requieren control en tiempo real estricto.

- **En VHDL**:
  - Es un lenguaje para la descripción de hardware y se utiliza para describir cómo el sistema debe ser implementado en un FPGA o ASIC.
  - Los estados y las transiciones se describen con señales y bloques concurrentes.
  - La ejecución es concurrente y se controla a nivel de hardware, lo que implica que el sistema es capaz de operar en paralelo y en tiempo real.

En resumen, mientras que en C se describe el comportamiento de un sistema secuencialmente, en VHDL se describe cómo un hardware realiza esas operaciones, utilizando conceptos de concurrencia y temporización que son fundamentales para el diseño digital.
