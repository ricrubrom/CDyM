## A

Investigue sobre los diferentes modelos de la familia Atmega AVR. Tabule los periféricos, la cantidad de RAM y de FLASH que poseen las distintas versiones. En particular detalle las características de los modelos Atmega328P y Atmega2560 utilizados en las plataformas Open-Source Arduino UNO y MEGA.

- Atmega328P:

  - Periféricos
    - 2 contadores/temporizadores de 8 bits con pre-escalador separado y modo de comparación
    - 1 contador/temporizador de 16 bits con pre-escalador separado, modo comparación y modo captura
    - 1 Contador de tiempo real con oscilador separado
    - 6 canales PWM
    - 8 canales ADC de 10 bits en paquete TQFP y QFN/MLF (Medición de temperatura)
    - USART serial programable
    - Interfaz serial SPI Maestro/Esclavo
    - Interfaz serial de dos cables orientada a byte
    - Temporizador watchdog programable con oscilador en chip separado
    - Comparador analógico en chip
    - Interrupción y despertar en cambio de pin
      -RAM
    - 2kB SRAM
      -Flash
    - 32kB Flash

- Atmega2560
  - Periféricos
    - 2 Contadores/temporizadores de 8 bits con pre-escaladores separados y modo comparación
    - 4 Contadores/temporizadores de 16 bits con pre-escaladores separados, modo de captura y comparación
    - Contador de tiempo real con oscilador separado
    - 4 canales PWM de 8 bits
    - 6/12 Canales PWM con resolución programable de 2 a 16 bits
    - Modulador de comparación de salida
    - 8/16 canales ADC de 10 bit
    - 2/4 USART serial programable
    - Interfaz serial SPI maestro/esclavo
    - Interfaz serial de dos cables orientada a byte
    - Temporizador watchdog programable con oscilador en chip separado
    - Comparador analógico en chip
    - Interrupción y despertar en cambio de pin
  - RAM
    - 8kB SRAM
  - Flash
    - 256kB Flash

## B

Detalle las características de la CPU AVR, incluyendo: Arquitectura de la CPU (Realice un diagrama en bloques), modelo de programación, modos de direccionamiento y resumen del conjunto de instrucciones.

- Arquitectura
  - Harvard modificado RISC (Buses separados para instrucciones y datos)
- Modelo de Programación
  - Se programa en C o assembler
- Modos de direccionamiento
  - Inmediato
  - Directo
  - Indirecto
  - Indirecto con desplazamiento
  - Relativo
- Instrucciones (RISC)
  - Aritmético lógicas
  - Transferencia de datos
  - Control de flujo
  - Bit y manipulación de bits
  - Control del microcontrolador

## C

Puertos de Entrada/Salida: Describa qué registros se utilizan para controlar los puertos de entrada y salida. Realice un diagrama en bloques de un terminal de entrada y salida y explique su funcionamiento.

- DDRx
  - Data Direction Register
  - Configura si un puerto es entrada o salida
- PORTx
  - Output port register
  - Setea el valor de output en los pines configurados como output
  - Habilita o deshabilita los resistores pull-up en los pines configurados como input
- PINx
  - Input register
  - Se lee una señal de entrada
  - En algunos dispositivos, este registro puede utilizarse para pin toggling
    - Escribir un uno lógico a PINx habilita el puerto PORTx correspondiente, sin importar el bit en DDRx

## D

Investigue cual es la capacidad de corriente que puede manejar un terminal individual configurado como salida. ¿Depende del estado lógico? ¿cuál es la capacidad de corriente que puede manejar el microcontrolador con todos los puertos funcionando simultáneamente?

- 40mA máximo por puerto
- No depende del estado lógico
- Suma de todos los puertos no debe exceder los 200mA

## E

Indique cuales son las dos posibilidades de conexión de un LED a un terminal de entrada y salida. Calcule la resistencia serie para que la corriente máxima por cada LED sea de 5mA. Muestre como configurar el terminal como salida y como modificar su estado lógico.

- Puede ser activa en alto o en bajo
  - Activa en alto cuando el ánodo esta conectado a VCC, y el cátodo a GND
  - Activa en bajo al revés
- La resistencia necesaria debe ser

  $$
    V=R\cdot i \\
    \frac{V}{R} = i \le 5ma \\
    \frac{V}{R} \le 5ma \\
    \frac{5V_{VCC} - 2V_{GND}}{5mA} \le R \\
    R\ge 600\Omega
  $$

## F

Se desea conectar un pulsador a una entrada digital del MCU. Investigue los posibles esquemas de conectar un pulsador y determine el algoritmo más adecuado para detectar en cada caso cuando el pulsador se presiona y se suelta. ¿Qué es una resistencia de pull-up? ¿y de pull-down? ¿Importa su valor? Investigue sobre cómo utilizar los pull-up internos del MCU.

- Se puede conectar de dos formas
  - Pulsador conectado a VCC y resistencia en GND (pull-down, se activa al apretar el botón)
  - Pulsador conectado a GND y resistencia en VCC (pull-up, se activa al no apretar el botón)
- Si importa el valor de la resistencia, debe ser entre 300 y 1k $\Omega$.
