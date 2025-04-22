## **Ejercicio No 7: Planificación Cooperativa de Tareas y Modularización**

### a) Planificación cooperativa con interrupción periódica de timer

La **planificación cooperativa** implica que las tareas ceden el control explícitamente. El **timer** genera interrupciones periódicas, y cuando se produce una, el planificador decide qué tarea ejecutar. Es crucial que las tareas cooperen y cedan el control para evitar bloqueos.

---

### b) Determinar el periodo de la interrupción

Los períodos de las tareas son:
- x(): 10 ms
- y(): 25 ms
- z(): 50 ms

El **mínimo común múltiplo (MCM)** de 10, 25 y 50 ms es 50 ms, por lo que el **periodo de la interrupción** debe ser de **50 ms**.

Condiciones para garantizar el funcionamiento:
- La carga del procesador no debe exceder su capacidad.
- Las tareas deben ser cooperativas y no bloquearse.

---

### c) Pseudocódigo para planificador

```plaintext
Tarea_x() { realizar_tarea_x(); ceder_control(); }
Tarea_y() { realizar_tarea_y(); ceder_control(); }
Tarea_z() { realizar_tarea_z(); ceder_control(); }

Planificador() {
    if (tiempo_actual % 10 == 0) ejecutar(Tarea_x);
    if (tiempo_actual % 25 == 0) ejecutar(Tarea_y);
    if (tiempo_actual % 50 == 0) ejecutar(Tarea_z);
}

Interrupcion_Timer() { tiempo_actual++; Planificador(); }
```

**Diagrama temporal**:
```
|-----|-----|-----|-----|-----|-----|
  0ms  10ms  20ms  30ms  40ms  50ms
|---x---|---y---|---z---|---x---|---y---|
```

---

### d) Planificación sin superposición

Si varias tareas coinciden en el mismo tick del sistema, se pueden asignar prioridades a las tareas o ejecutar las que hayan vencido primero. Aquí, las tareas se deben ejecutar de forma que no se solapen, y en caso de que eso suceda, una opción es priorizar las tareas de acuerdo con su importancia o criticidad. El planificador debe asegurarse de que, dentro de un mismo periodo, no haya ejecución simultánea de tareas.

**Solución**:
- Se puede usar un sistema de prioridades o un mecanismo de "round-robin" para garantizar que cada tarea tenga su tiempo de ejecución sin bloquear a las demás.

---

### e) Modularización de software

La **modularización** consiste en dividir un sistema en partes más pequeñas y manejables (módulos). Cada módulo tiene una funcionalidad específica y puede ser desarrollado, probado y mantenido independientemente. Las ventajas incluyen:
- Mejor mantenimiento y escalabilidad.
- Reutilización de código.
- Aislación de cambios: un módulo puede modificarse sin afectar otros.

---

### f) Modularización de archivos en C con clases de POO

En **C**, no existe un concepto de clases como en la POO, pero se pueden emular mediante el uso de **estructuras**. Para modularizar, se puede dividir el código en varios archivos:
- Un archivo de **cabecera** (.h) con las definiciones de las estructuras y las declaraciones de las funciones.
- Un archivo de **implementación** (.c) con la lógica de las funciones.

Ejemplo:
- `mi_modulo.h`: contiene la definición de una estructura.
- `mi_modulo.c`: contiene las funciones que operan sobre la estructura.

---

### g) Uso de `static` en funciones, variables y constantes

El modificador `static` se usa para restringir el alcance de una función, variable o constante a su archivo de origen. Esto ayuda a modularizar el código al evitar que los elementos sean accesibles desde otros archivos.

- **Funciones `static`**: Solo accesibles dentro del archivo donde se definen.
- **Variables `static`**: Mantienen su valor entre llamadas a funciones, pero solo son visibles dentro del archivo.
- **Constantes `static`**: Similar a las variables, pero su valor no puede cambiar.

---

### h) Funciones privadas y públicas

Las **funciones públicas** son aquellas que forman parte de la interfaz de un módulo y pueden ser invocadas desde otros módulos, mientras que las **funciones privadas** son internas y no accesibles desde fuera del módulo.

**Ejemplo**:
- **Función pública**: Una función de la API del módulo, accesible desde otros módulos.
- **Función privada**: Una función auxiliar que solo es útil dentro del módulo.

```c
// mi_modulo.h (públicas)
void funcion_publica();

// mi_modulo.c (privadas)
static void funcion_privada() {
    // Código privado
}
```
