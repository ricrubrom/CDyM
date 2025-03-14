## A

Investigue sobre los diferentes modelos de la familia Atmega AVR. Tabule los periféricos, la cantidad de RAM y de FLASH que poseen las distintas versiones. En particular detalle las características de los modelos Atmega328P y Atmega2560 utilizados en las plataformas Open-Source Arduino UNO y MEGA.

- Atmega328P:

  - Perifericos
    - 2 contadores/temporizadores de 8 bits con pre-escalador separado y modo de comparacion
    - 1 contador/temporizador de 16 bits con pre-escalador separado, modo comparacion y modo captura
    - 1 Contador de tiempo real con oscilador separado
    - 6 canales PWM
    - 8 canales ADC de 10 bits en paquete TQFP y QFN/MLF (Medicion de temperatura)
    - USART serial programable
    - Interfaz serial SPI Maestro/Esclavo
    - Interfaz serial de dos cables orientada a byte
    - Temporizador watchdog programable con oscilador en chip separado
    - Comparador analogico en chip
    - Interrupcion y depertar en cambio de pin
      -RAM
    - 2kB SRAM
      -Flash
    - 32kB Flash

- Atmega2560
  - Perifericos
    - 2 Contadores/temporizadores de 8 bits con pre-escaladores separados y modo comparacion
    - 4 Contadores/temporizadores de 16 bits con pre-escaladores separados, modo de captura y comparacion
    - Contador de tiempo real con oscilador separado
    - 4 canales PWM de 8 bits
    - 6/12 Canales PWM con resolucion programable de 2 a 16 bits
    - Modulador de comparacion de salida
    - 8/16 canales ADC de 10 bit
    - 2/4 USART serial programable
    - Interfaz serial SPI maestro/esclavo
    - Interfaz serial de dos cables orientada a byte
    - Temporizador watchdog programable con oscilador en chip separado
    - Comparador analogico en chip
    - Interrupcion y depertar en cambio de pin
  - RAM
    - 8kB SRAM
  - Flash
    - 256kB Flash

## B

Detalle las características de la CPU AVR, incluyendo: Arquitectura de la CPU (Realice un diagrama en bloques), modelo de programación, modos de direccionamiento y resumen del conjunto de instrucciones.

-

## C

Puertos de Entrada/Salida: Describa qué registros se utilizan para controlar los puertos de entrada y salida. Realice un diagrama en bloques de un terminal de entrada y salida y explique su funcionamiento.

-

## D

Investigue cual es la capacidad de corriente que puede manejar un terminal individual configurado como salida. ¿Depende del estado lógico? ¿cuál es la capacidad de corriente que puede manejar el microcontrolador con todos los puertos funcionando simultáneamente?

-

## E

Indique cuales son las dos posibilidades de conexión de un LED a un terminal de entrada y salida. Calcule la resistencia serie para que la corriente máxima por cada LED sea de 5mA. Muestre como configurar el terminal como salida y como modificar su estado lógico.

-

## F

Se desea conectar un pulsador a una entrada digital del MCU. Investigue los posibles esquemas de conectar un pulsador y determine el algoritmo más adecuado para detectar en cada caso cuando el pulsador se presiona y se suelta. ¿Qué es una resistencia de pull-up? ¿y de pull-down? ¿Importa su valor? Investigue sobre cómo utilizar los pull-up internos del MCU.

-

