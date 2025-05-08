#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum
{
    START,
    SHOW_PASSWORD,
    GAME,
    HIT,
    MISS,
    WIN,
    LOSE
} GameState;

extern volatile GameState gameState;
extern volatile uint8_t tick;
extern volatile uint8_t second;
extern volatile uint8_t gameTick;
extern volatile uint8_t gameSecond;
extern volatile uint8_t temporization_flag;

void timer_init(void);

#endif
