/**
 * @file game_mef.h
 * @brief Declaraciones de funciones relacionadas con la máquina de estados del juego.
 *
 * Este archivo contiene las declaraciones de todas las funciones que manejan
 * los diferentes estados del juego de ingreso de contraseñas.
 */

#ifndef GAME_MEF_H
#define GAME_MEF_H

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
 * @brief Ejecuta un paso de la máquina de estados del juego.
 *
 * Según el estado actual del juego, delega el control a la función correspondiente.
 * Esta función debe ser llamada periódicamente, idealmente desde el lazo principal.
 */
void game_mef(void);

/**
 * @brief Estado inicial del juego. Espera el inicio por teclado.
 */
void handle_start_state(void);

/**
 * @brief Muestra la contraseña al usuario antes de comenzar el juego.
 */
void handle_show_password_state(void);

/**
 * @brief Controla la lógica de ingreso y verificación de la contraseña.
 */
void handle_game_state(void);

/**
 * @brief Se ejecuta al ingresar un carácter correcto.
 */
void handle_hit_state(void);

/**
 * @brief Se ejecuta al ingresar un carácter incorrecto.
 */
void handle_miss_state(void);

/**
 * @brief Maneja la lógica cuando se gana el juego.
 */
void handle_win_state(void);

/**
 * @brief Maneja la lógica cuando se pierde el juego.
 */
void handle_lose_state(void);

#endif
