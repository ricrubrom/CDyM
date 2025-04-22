# 🧪 Ejercicio Nº 5: Temporizador Asincrónico – RTC (Contador de Tiempo Real)

## a) Diferencias y similitudes entre TIMER0 y TIMER2

| Característica          | TIMER0                             | TIMER2                          |
| ----------------------- | ---------------------------------- | ------------------------------- |
| Resolución              | 8 bits                             | 8 bits                          |
| Fuente de reloj externa | ❌ No                              | ✔️ Sí (cristal de 32.768 kHz)   |
| Modo asincrónico        | ❌ No                              | ✔️ Sí                           |
| Uso común               | PWM, delays, generación de señales | RTC, tareas periódicas precisas |
| Compartido con PWM      | ✔️ Sí                              | ✔️ Sí                           |
| Prescaler disponible    | 1, 8, 64, 256, 1024                | 1, 8, 32, 64, 128, 256, 1024    |
| Reloj independiente     | ❌ Usa reloj del sistema           | ✔️ Puede usar cristal externo   |

**Conclusión:** TIMER2 es ideal para aplicaciones de bajo consumo y precisión temporal como relojes en tiempo real, gracias a su capacidad asincrónica y uso de un cristal externo.

---

## b) Configuración para interrupción cada 10 ms usando cristal de 32.768 kHz

### 🔧 Datos

- Cristal externo: **32.768 kHz**
- Objetivo: **interrupción cada 10 ms**

### 📐 Cálculo de OCR2A

- Frecuencia del reloj: $$ f\_{CLK} = 32.768 \, \text{kHz} $$
- Período del reloj: $$ T = \frac{1}{32.768\,\text{kHz}} \approx 30.5 \, \mu s $$
- Cantidad de ciclos en 10 ms:

  $$
  \frac{10 \, \text{ms}}{30.5 \, \mu\text{s}} \approx 327.68 \Rightarrow \boxed{OCR2A = 327}
  $$

### ⚙️ Configuración en C

```c
// Modo CTC
TCCR2A = (1 << WGM21);

// Reloj sin prescaler (usa directamente el cristal externo)
TCCR2B = (1 << CS20);

// Valor para generar interrupción cada 10 ms
OCR2A = 327;

// Habilitar interrupción por comparación
TIMSK2 = (1 << OCIE2A);

// Habilitar interrupciones globales
sei();
```

### 🧠 Nota importante:

Para que funcione el cristal externo, es necesario habilitar el modo asincrónico. Además, se recomienda esperar a que el oscilador se estabilice (chequear el flag `ASSR`).

---

## c) ICs RTC: DS1302 y DS3231

| IC     | Funcionalidad                         | Interfaz | Ventajas principales                                                   |
| ------ | ------------------------------------- | -------- | ---------------------------------------------------------------------- |
| DS1302 | RTC + RAM (31 bytes)                  | SPI-like | Bajo consumo, batería de respaldo, fácil de usar                       |
| DS3231 | RTC con compensación térmica y alarma | I2C      | Alta precisión (±2 ppm), incluye sensor de temperatura, batería backup |

### 📌 ¿Qué funcionalidad proveen?

- Ambos circuitos proveen una solución **completa de reloj en tiempo real (RTC)**, capaz de llevar cuenta de segundos, minutos, horas, días, meses y años, incluso en modo de bajo consumo.
- Mantienen la hora aun cuando el microcontrolador está apagado, gracias a la **batería de respaldo**.

### 🔌 ¿Cómo se conectan al microcontrolador?

- **DS1302**: se conecta mediante un protocolo **serial síncrono de 3 líneas** (CE, I/O, SCLK).
- **DS3231**: se conecta vía **I2C**, usando los pines **SDA y SCL**.

### ✅ Ventajas

- Permiten liberar recursos del microcontrolador.
- Mayor precisión que usar temporizadores internos.
- Persistencia de la hora gracias a la batería de respaldo.
- El DS3231 en particular tiene muy baja deriva térmica y puede incluir alarmas programables.

