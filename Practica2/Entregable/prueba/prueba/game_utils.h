/**
 * @file game_utils.h
 * @brief Declaraciones y variables globales para el manejo de temporización en el juego.
 *
 * Contiene la definición del enum de estados del juego, variables de temporización
 * y la declaración de la función de inicialización del temporizador.
 */

#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @brief Estados posibles del juego.
 */
typedef enum
{
    START,         ///< Esperando inicio (*)
    SHOW_PASSWORD, ///< Mostrando la contraseña
    GAME,          ///< Juego en progreso
    HIT,           ///< Acierto en un carácter
    MISS,          ///< Error en un carácter
    WIN,           ///< El jugador ganó
    LOSE           ///< El jugador perdió
} GameState;

/**
 * @brief Inicializa el temporizador Timer0.
 */
void timer_init(void);

#endif
