#ifndef MEF_H
#define MEF_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define BUFFER_SIZE 64

typedef enum
{
  REPOSO,
  ESPERA,
  DATO,
  TRANSFER
} MEF_states;

void MEF_init();
void MEF_update();
void send_string();

#endif