# **Ejercicio No 3: Interrupciones**

## a) Secuencia ante una interrupción:

1. Finaliza la instrucción actual.
2. Guarda la dirección del programa (PC) en la pila.
3. Desactiva interrupciones (borra bit `I` de `SREG`).
4. Salta a la rutina correspondiente (ISR).
5. Retorna con `RETI`.

## b) Bit I en SREG:

- Habilita las interrupciones globales.
- Tras un RESET, **está en 0** (interrupciones deshabilitadas).
- Se modifica con:
  - `sei();` → habilita.
  - `cli();` → deshabilita.

## c) RESET:

- Reinicia el MCU y los registros.
- Se puede generar por:
  - RESET externo.
  - Watchdog.
  - Brown-out.
- Registro `MCUSR` indica la causa del último reset.

## d) Latencia de interrupción:

- Tiempo entre el evento y la ejecución de la ISR.
- Mínimo: **4 ciclos de reloj** (2 ciclos para finalizar instrucción + 2 para saltar).

## e) Interrupciones anidadas:

- Es cuando una ISR puede ser interrumpida por otra.
- ❌ **No es posible por defecto**. Requiere reactivar el bit `I` dentro de la ISR.

## f) Interrupciones externas INTx:

- Se activan en los pines INT0 e INT1.
- Pueden configurarse por:
  - Nivel bajo.
  - Flanco de bajada o subida.
- Flanco: responde a un cambio momentáneo.
- Nivel: responde mientras el nivel se mantenga.

## g) PIN Change Interrupts:

### ✅ Terminales habilitados:

- Casi todos los pines I/O (PORTB, PORTC, PORTD).

### ⚙️ Configuración:

- Se usan:
  - `PCICR`: habilita grupos de pines.
  - `PCMSKx`: habilita pines individuales.

### 📍 Vectores:

- `PCINT0_vect`, `PCINT1_vect`, `PCINT2_vect`.
- Prioridad fija según vector.

### 🆚 Diferencias con INTx:

| Característica       | INTx         | PCINTx                |
| -------------------- | ------------ | --------------------- |
| Pines                | INT0, INT1   | Casi todos            |
| Configuración        | Precisa      | General               |
| Tipo de interrupción | Flanco/Nivel | Solo cambio de estado |
| Vector por pin       | Sí           | Uno por grupo         |

---

