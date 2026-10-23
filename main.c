#include "raylib.h"
#include "juegovida.h"

int main(void) {
  int ancho_pantalla = COLUMNAS * TAM_CELULA;
  int alto_pantalla = FILAS * TAM_CELULA;

  InitWindow(ancho_pantalla, alto_pantalla, "Juego de la Vida de Conway");
  SetTargetFPS(10);

  JuegoDeLaVida juego;

  //Control defensivo del llamado a funcion
  if(inicializar_juego_vida(&juego) != ERR_OK) {
    CloseWindow();
    return -1;
  }

  while (!WindowShouldClose()) {
    //Procesamiento de entradas
    if(IsKeyPressed(KEY_SPACE)) {
      juego.pausado = !juego.pausado;
    }
    if (IsKeyPressed(KEY_C)) {
      limpiar_tablero(&juego);
    }

    //Cargar patrones en el centro
    if (IsKeyPressed(KEY_ONE)) cargar_patron_palo (&juego, FILAS / 2, COLUMNAS / 2);
    if (IsKeyPressed(KEY_TWO)) cargar_patron_bloque (&juego, FILAS / 2, COLUMNAS / 2);
    if (IsKeyPressed(KEY_THREE)) cargar_patron_glider (&juego, FILAS / 2, COLUMNAS / 2);

    //Interaccion con el mouse
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      int columna = GetMouseX() / TAM_CELULA;
      int fila = GetMouseY() / TAM_CELULA;
      if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS){
        juego.actual[fila][columna] = 1;
      }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      int columna = GetMouseX() / TAM_CELULA;
      int fila = GetMouseY() / TAM_CELULA;
      if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS){
        juego.actual[fila][columna] = 0;
      }
    }
    //Actualizar Logica
    actualizar_generacion(&juego);

    //Render
    BeginDrawing();
    ClearBackground((Color){ 30, 30, 30, 255 });

    //Dibujar Celdas
    for (int i = 0; i < FILAS; i++){
      for (int j = 0; j < COLUMNAS; j++){
        if (juego.actual[i][j] == 1){
          DrawRectangle (j * TAM_CELULA, i * TAM_CELULA, TAM_CELULA, TAM_CELULA, RAYWHITE);
        }
        DrawRectangleLines (j * TAM_CELULA, i * TAM_CELULA, TAM_CELULA, TAM_CELULA, (Color){ 60, 60, 60, 255 });
      }
    }
    //Menu de texto
    const char *texto_menu = juego.pausado
    ? "PAUSADO - 1: Palo  2: Bloque  3: Glider | C: Limpiar | Clic Izq: Pintar  Clic Der: Borrar |"
    : "CORRIENDO - Espacio: Pausar";

    DrawText(texto_menu, 8, 8, 16, SKYBLUE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
