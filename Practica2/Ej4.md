## 🧪 Ejercicio N°4: Temporizadores

### a) Componentes principales del módulo TIMER0 y modos de funcionamiento

El **TIMER0** es un temporizador de 8 bits presente en microcontroladores AVR como el ATmega328P. Sus componentes principales son:

- **TCNT0 (Timer/Counter Register)**: contiene el valor actual del contador (0 a 255).
- **TCCR0A y TCCR0B (Timer/Counter Control Registers A y B)**: configuran el modo de operación y la fuente de reloj.
- **OCR0A y OCR0B (Output Compare Registers A y B)**: valores contra los que se compara el contador para generar eventos.
- **TIMSK0 (Timer Interrupt Mask Register)**: habilita las interrupciones asociadas al timer.
- **TIFR0 (Timer Interrupt Flag Register)**: contiene las banderas de interrupción.

#### Modos de funcionamiento:

1. **Normal Mode (Overflow)**: el contador cuenta de 0 a 255 y genera una interrupción cuando vuelve a 0.
2. **CTC (Clear Timer on Compare Match)**: el contador se reinicia al alcanzar OCR0A.
3. **Fast PWM**: genera señales PWM con actualización rápida.
4. **Phase Correct PWM**: genera señales PWM con simetría en la subida y bajada.

---

### b) Funcionamiento del prescaler y cálculo de frecuencias

El **prescaler** divide la frecuencia del reloj del sistema antes de alimentar el contador. Las opciones típicas de división son: 1, 8, 64, 256, y 1024.

#### Fórmulas:

- **Frecuencia del Timer0**:

  $$
  f*{TIMER0} = \frac{f*{CLK}}{prescaler}
  $$

- **Frecuencia de desborde (Overflow)** en modo normal (8 bits):

  $$
  f*{OVERFLOW} = \frac{f*{TIMER0}}{256} = \frac{f\_{CLK}}{prescaler \times 256}
  $$

#### Borrado de bandera de desborde:

Se borra escribiendo un `1` en la posición correspondiente del registro `TIFR0`, por ejemplo:

```c
TIFR0 |= (1 << TOV0);
```

---

### c) Retardo de 1 ms con CLKIO = 8 MHz

Primero, se busca una configuración que produzca un **overflow cada 1 ms**.

$$
f\_{OVERFLOW} = \frac{1}{0.001 \, \text{s}} = 1000 \, \text{Hz}
$$

Con:

$$
f\_{CLK} = 8\,\text{MHz} \Rightarrow prescaler = 64
$$

$$
f\_{TIMER0} = \frac{8\,000\,000}{64} = 125\,000\,\text{Hz}
$$

$$
f\_{OVERFLOW} = \frac{125\,000}{256} \approx 488.28\,\text{Hz}
$$

Eso da un overflow cada:

$$
T\_{OVERFLOW} = \frac{1}{488.28} \approx 2.048\,\text{ms}
$$

Para lograr 1 ms, se puede usar **CTC mode** con OCR0A = 124:

$$
\text{Período deseado: } 1\,\text{ms} \Rightarrow f = 1000\,\text{Hz}
$$

$$
OCR0A = \frac{f*{TIMER0}}{f*{deseado}} - 1 = \frac{125\,000}{1000} - 1 = 124
$$

#### Configuración:

```c
TCCR0A = (1 << WGM01); // Modo CTC
TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64
OCR0A = 124; // 1ms
```

---

### d) Generar interrupción periódica de 1 ms (CLKIO = 8 MHz)

Con los valores anteriores:

```c
// Configurar TIMER0 en modo CTC
TCCR0A = (1 << WGM01);
TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
OCR0A = 124; // 1 ms

// Habilitar interrupción por comparación
TIMSK0 = (1 << OCIE0A);

// Activar interrupciones globales
sei();
```

Y la rutina de interrupción:

```c
ISR(TIMER0_COMPA_vect) {
    // Código a ejecutar cada 1ms
}
```

