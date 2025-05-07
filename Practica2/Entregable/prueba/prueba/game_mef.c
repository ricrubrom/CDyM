#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "keypad.h"
#include "game_mef.h"
#include "game_utils.h"

volatile GameState gameState = START;
volatile uint8_t tick = 0;
volatile uint8_t second = 0;
volatile uint8_t gameTick = 0;
volatile uint8_t gameSecond = 0;
volatile uint8_t temporization_flag = 0;

uint8_t keyPressed = -1;
uint8_t *password = NULL;
uint8_t xPosition = 0;
uint8_t lifes = 3;
uint8_t pressedKeys[4] = {0, 0, 0, 0};
uint8_t currentKey = 0;
uint8_t firstTime = 1;

const uint8_t *dicc[] = {
    "Arbol", "Boton", "CDyMC", "ClavE", "Facil", "Gafas",
    "Hojas", "LiBro", "Lanza", "Nieve", "PeRro", "PecES",
    "PiAno", "PrYKe", "RUEDa", "SERIE", "SalUd", "Salud",
    "Silla", "Tecla", "Valor", "Verde", "YnHRz", "hARdD", "silla"};

void game_mef(void)
{
    if (temporization_flag)
    {
        switch (gameState)
        {
        case START:
            handle_start_state();
            break;

        case SHOW_PASSWORD:
            handle_show_password_state();
            break;

        case GAME:
            handle_game_state();
            break;

        case HIT:
            handle_hit_state();
            break;

        case MISS:
            handle_miss_state();
            break;

        case WIN:
            handle_win_state();
            break;

        case LOSE:
            handle_lose_state();
            break;
        }
    }
}

void handle_start_state(void)
{
    keyPressed = -1;
    KEYPAD_scan(&keyPressed);
    if (keyPressed == '*')
    {
        gameState = SHOW_PASSWORD;
        LCDclr();
        _delay_ms(5);
        if (firstTime)
        {
            srand(tick + 100 * second);
            firstTime = 0;
        }
        password = dicc[rand() % 25];
        LCDGotoXY(0, 0);
        LCDstring("Password: ", 10);
        LCDstring(password, 5);
        tick = 0;
        second = 0;
    }
}

void handle_show_password_state(void)
{
    if (second >= 2)
    {
        second = 0;
        gameTick = 0;
        gameSecond = 0;
        xPosition = 0;
        currentKey = 0;
        lifes = 3;
        LCDclr();
        _delay_ms(5);
        LCDGotoXY(0, 0);
        LCDstring("Password: ", 10);
        LCDGotoXY(13, 1);
        LCDsendChar(lifes + '0');
        LCDstring("/3", 2);
        gameState = GAME;
    }
}

void handle_game_state(void)
{
    if (gameState == GAME)
    {
        pressedKeys[currentKey] = 0;
        KEYPAD_scan(&pressedKeys[currentKey]);
        switch (pressedKeys[currentKey])
        {
        case '#':
            pressedKeys[currentKey] = '\0';
            gameState = (atoi(pressedKeys) == password[xPosition]) ? HIT : MISS;
            break;
        case 0:
            break;
        default:
            LCDGotoXY(currentKey, 1);
            LCDsendChar(pressedKeys[currentKey]);
            currentKey++;
            break;
        }
        if (currentKey >= 4)
        {
            gameState = MISS;
        }
    }
}

void handle_hit_state(void)
{
    xPosition++;
    currentKey = 0;
    LCDGotoXY(10, 0);
    LCDstring(password, xPosition);
    LCDGotoXY(0, 1);
    LCDstring("    ", 4);
    if (xPosition >= 5)
    {
        tick = 0;
        second = 0;
        LCDclr();
        _delay_ms(5);
        LCDGotoXY(0, 0);
        LCDstring("Ganaste!", 8);

        char message[16];
        sprintf(message, "Tiempo: %d seg.", gameSecond);
        uint8_t length = strlen(message);
        uint8_t start_pos = (length < 16) ? (16 - length) / 2 : 0;

        LCDGotoXY(start_pos, 1);
        LCDstring(message, length);

        gameState = WIN;
    }
    else
    {
        gameState = GAME;
    }
}

void handle_miss_state(void)
{
    currentKey = 0;
    LCDGotoXY(0, 1);
    LCDstring("    ", 4);
    lifes--;
    LCDGotoXY(13, 1);
    LCDsendChar(lifes + '0');
    if (lifes <= 0)
    {
        tick = 0;
        second = 0;
        LCDclr();
        _delay_ms(5);
        LCDGotoXY(0, 0);
        LCDstring("Perdiste!", 9);
        gameState = LOSE;
    }
    else
    {
        gameState = GAME;
    }
}

void handle_win_state(void)
{
    if (second >= 5)
    {
        LCDclr();
        _delay_ms(5);
        LCDstring(" --Bienvenido--", 15);
        LCDGotoXY(0, 1);
        LCDstring("Presiona * init", 15);
        gameState = START;
    }
}

void handle_lose_state(void)
{
    if (second >= 5)
    {
        LCDclr();
        _delay_ms(5);
        LCDstring(" --Bienvenido--", 15);
        LCDGotoXY(0, 1);
        LCDstring("Presiona * init", 15);
        gameState = START;
    }
}
