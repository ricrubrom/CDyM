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

/// Estado actual del juego
extern volatile GameState gameState;

/// Tick general (para mostrar la contraseña, ganar o perder)
extern volatile uint8_t tick;

/// Segundos contados mientras se muestra la contraseña o tras finalizar el juego
extern volatile uint8_t second;

/// Tick durante el juego activo
extern volatile uint8_t gameTick;

/// Segundos contados durante el juego activo
extern volatile uint8_t gameSecond;

/// Bandera de temporización, cambia en cada interrupción
extern volatile uint8_t temporization_flag;

/**
 * @brief Inicializa el temporizador Timer0.
 */
void timer_init(void);

#endif
