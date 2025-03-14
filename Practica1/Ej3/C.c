#include <stdio.h>

void bin_to_ascii(unsigned char num, char *output)
{
  int i = 0;
  char temp[4];
  while (num > 0)
  {
    temp[i++] = (num % 10) + '0';
    num /= 10;
  }
  if (i == 0)
  {
    temp[i++] = '0';
  }
  temp[i] = '\0';

  // Invertir la cadena
  int j;
  for (j = 0; j < i; j++)
  {
    output[j] = temp[i - j - 1];
  }
  output[i] = '\0';
}

int main()
{
  unsigned int num;
  char output[4]; // Un número de 8 bits puede tener hasta 3 dígitos más el terminador nulo

  printf("Ingrese un numero (0-255): ");
  if (scanf("%u", &num) != 1 || num > 255)
  {
    printf("Entrada inválida. Debe ser un numero entre 0 y 255.\n");
    return 1;
  }

  bin_to_ascii((unsigned char)num, output);
  printf("numero en ASCII: %s\n", output);

  return 0;
}
