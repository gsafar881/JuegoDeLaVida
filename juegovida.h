#ifndef JUEGOVIDA_H
#define JUEGOVIDA_H

#include <stdbool.h>

//CONSTANTES DEL TABLERO
#define FILAS 40
#define COLUMNAS 60
#define TAM_CELULA 15

//CODIGOS DE ESTADO Y ERRORES
#define ERR_OK 0
#define ERR_NULL_PTR -1
#define ERR_PARAM_INVALIDO -2

//ESTRUCTURA PRINCIPAL
typedef struct {
    int actual[FILAS][COLUMNAS];
    int siguiente[FILAS][COLUMNAS];
    bool pausado;
} JuegoDeLaVida;

//PROTOTIPOS DE FUNCIONES
int inicializar_juego_vida(JuegoDeLaVida *juego);
int limpiar_tablero(JuegoDeLaVida *juego);
int contar_vecinos(const JuegoDeLaVida *juego, int fila, int columna, int *vecinos_out);
int actualizar_generacion(JuegoDeLaVida *juego);

//PATRONES PREDEFINIDOS
int cargar_patron_palo(JuegoDeLaVida *juego, int fila, int columna);
int cargar_patron_bloque(JuegoDeLaVida *juego, int fila, int columna);
int cargar_patron_glider(JuegoDeLaVida *juego, int fila, int columna);

#endif // JUEGOVIDA_H
