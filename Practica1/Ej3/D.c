#include <stdio.h>
#include <unistd.h> // Para usar la función sleep()

void send_serial(unsigned char num)
{
  for (int i = 0; i < 8; i++)
  {
    printf("%d\n", num & 1); // Imprime el bit menos significativo
    num >>= 1;               // Desplaza el número a la derecha
  }
}

int main()
{
  unsigned int num;

  printf("Ingrese un número (0-255): ");
  if (scanf("%u", &num) != 1 || num > 255)
  {
    printf("Entrada inválida. Debe ser un número entre 0 y 255.\n");
    return 1;
  }

  printf("Enviando bits en serie:\n");
  send_serial((unsigned char)num);

  return 0;
}
