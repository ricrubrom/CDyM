#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <time.h>
#include "lcd.h"
#include "keypad.h"
#include "game_mef.h"
#include "game_utils.h"

int main(void)
{
    LCD_Init();
    KEYPAD_init();
    timer_init();
    _delay_ms(10);
    LCDstring(" --Bienvenido--", 15);
    LCDGotoXY(0, 1);
    LCDstring("Presiona * init", 15);
    sei(); // Habilitar interrupciones globales

    while (1)
    {
        game_mef();
    }
}
