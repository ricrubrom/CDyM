#include <stdio.h>
#include <stdlib.h>

void invert(int *arr, int size)
{
  int i;
  int n = size / sizeof(int);
  int aux;
  for (i = 0; i < n / 2; i++)
  {
    aux = arr[i];
    arr[i] = arr[n - i - 1];
    arr[n - i - 1] = aux;
  }
}

int main()
{
  int size = sizeof(int) * 30;
  int *arr = (int *)malloc(size);
  int i;

  for (i = 0; i < 30; i++)
  {
    arr[i] = i;
  }

  for (i = 0; i < size / sizeof(int); i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  invert(arr, size);
  for (i = 0; i < size / sizeof(int); i++)
  {
    printf("%d ", arr[i]);
  }
  free(arr);
  return 0;
}