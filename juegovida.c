#include "juegovida.h"
#include <stddef.h>

int limpiar_tablero(JuegoDeLaVida *juego) {
    //Clausula de guarda
    if (juego == NULL) {
        return ERR_NULL_PTR;
    }
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            juego -> actual[i][j] = 0;
            juego -> siguiente[i][j] = 0;
        }
    }
    return ERR_OK;
}

int inicializar_juego_vida(JuegoDeLaVida *juego) {
    //Clausula de guarda
    if (juego == NULL) {
        return ERR_NULL_PTR;
    }
    int codigo_estado = limpiar_tablero(juego);
    if (codigo_estado != ERR_OK) {
        return codigo_estado;
    }

    juego -> pausado = true;
    return ERR_OK;
}

int contar_vecinos(const JuegoDeLaVida *juego, int fila, int columna, int *vecinos_out) {
    //Clausula de guarda
    if (juego == NULL || vecinos_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        return ERR_PARAM_INVALIDO;
    }
    int contador_vecinos = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            //Bordes toroidales
            int fila_vecina = (fila + i + FILAS) % FILAS;
            int columna_vecina = (columna + j + COLUMNAS) % COLUMNAS;

            contador_vecinos += juego -> actual[fila_vecina][columna_vecina];
        }
    }
    *vecinos_out = contador_vecinos;
    return ERR_OK;
}

int actualizar_generacion(JuegoDeLaVida *juego) {
    //Clausula de guarda
    if (juego == NULL) {
        return ERR_NULL_PTR;
    }

    if (juego -> pausado) {
        return ERR_OK;
    }

    //Calculo siguiente generacion
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int vecinos = 0;
            contar_vecinos(juego, i, j, &vecinos);
            int estado_actual = juego -> actual[i][j];

            if (estado_actual == 1) {
                juego -> siguiente[i][j] = (vecinos == 2 || vecinos == 3) ? 1 : 0;
            } else {
                juego -> siguiente[i][j] = (vecinos == 3) ? 1 : 0;
            }
        }
    }

    //Matriz siguiente sobre actual
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            juego -> actual[i][j] = juego -> siguiente[i][j];
        }
    }
    return ERR_OK;
}

//CARGA DE PATRONES

int cargar_patron_palo(JuegoDeLaVida *juego, int fila, int columna) {
    if (juego == NULL) return ERR_NULL_PTR;
    if (fila < 1 || fila >= FILAS - 1 || columna < 0 || columna >= COLUMNAS) {
        return ERR_PARAM_INVALIDO;
    }

    juego -> actual[fila - 1][columna] = 1;
    juego -> actual[fila][columna] = 1;
    juego -> actual[fila + 1][columna] = 1;

    return ERR_OK;
}

int cargar_patron_bloque(JuegoDeLaVida *juego, int fila, int columna) {
    if (juego == NULL) return ERR_NULL_PTR;
    if (fila < 0 || fila >= FILAS - 1 || columna < 0 || columna >= COLUMNAS - 1) {
        return ERR_PARAM_INVALIDO;
    }

    juego -> actual[fila][columna] = 1;
    juego -> actual[fila][columna + 1] = 1;
    juego -> actual[fila + 1][columna] = 1;
    juego -> actual[fila + 1][columna + 1] = 1;

    return ERR_OK;
}

int cargar_patron_glider(JuegoDeLaVida *juego, int fila, int columna) {
    if (juego == NULL) return ERR_NULL_PTR;
    if (fila < 0 || fila >= FILAS - 2 || columna < 0 || columna >= COLUMNAS - 2) {
        return ERR_PARAM_INVALIDO;
    }

    juego -> actual[fila][columna + 1] = 1;
    juego -> actual[fila + 1][columna + 2] = 1;
    juego -> actual[fila + 2][columna] = 1;
    juego -> actual[fila + 2][columna + 1] = 1;
    juego -> actual[fila + 2][columna + 2] = 1;

    return ERR_OK;
}
