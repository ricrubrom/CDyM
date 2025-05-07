#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "game_utils.h"

void timer_init(void)
{
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS02) | (1 << CS00);
    OCR0A = 155;
    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
    tick++;
    gameTick++;
    temporization_flag ^= 1;
    if (gameState == SHOW_PASSWORD || gameState == WIN || gameState == LOSE)
    {
        if (tick >= 100)
        {
            second++;
            tick = 0;
        }
    }
    else if (gameState == GAME || gameState == HIT || gameState == MISS)
    {
        if (gameTick >= 100)
        {
            gameSecond++;
            gameTick = 0;
        }
    }
}
