#include <stdio.h>

// unsigned short suma(unsigned char N)
unsigned char suma(unsigned char N)
{
  return N * (N + 1) / 2;
}

int main()
{

  unsigned char N = 10;
  printf("La suma de los primeros %d numeros es: %d\n", N, suma(N));

  return 0;
}

// Si nos mantenmos con char, el resultado sufre overflow, siendo la respuesta erronea.
// Si cambiamos a short, el resultado es correcto.