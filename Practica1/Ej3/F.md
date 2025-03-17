Explique qué hace la siguiente sentencia de C: PORTC |= (1<< PORTC0) | (1<< PORTC2) | (1<< PORTC3); ¿Cuál es la diferencia con la última del ejercicio anterior. ¿Qué representa PORTCx? ¿Dónde y cómo está definido?

- PORTC |= (1<< PORTC0) | (1<< PORTC2) | (1<< PORTC3);

  - Setea un 1 en los puertos 0, 2 y 3
  - Luego hace un un bitwise or con asignación al resultado de lo anterior y PORTC

- La diferencia es que no modifica los pines que no utiliza

- Representa la "posición" de cada pin
  - PORTC0 = 0x00
  - PORTC1 = 0x01
  - PORTC2 = 0x02
  - PORTC3 = 0x03
  - Y asi

- Proviene de la librería avr/io.h
