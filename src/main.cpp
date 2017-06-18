//
//  Juego de la vida
//  Paula Torres
//  16 junio 2017
//
//  Opciones:
//
//  life N      - Cuadricula de N * N.
//  life M N    - Cuadricula de M filas y N columnas.
//  life M N F  - Cuadricula de M * N, F fps.
//

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "game.h"

using namespace std;

// Valores por defecto

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 10;
const int GRID_ROWS = 48;
const int GRID_COLS = 64;

// Funcion principal

int main(int argc, char ** argv)
{
    int nrows = GRID_ROWS;
    int ncols = GRID_COLS;
    int fps = SCREEN_FPS;
    
    // Leer valores de consola
    
    if (argc >= 2) {
        nrows = atoi(argv[1]);
        
        if (argc >= 3) {
            ncols = atoi(argv[2]);
            
            if (argc >= 4)
                fps = atoi(argv[3]);
            
        } else {
            ncols = nrows;
        }
        
        if (nrows < 1 || nrows > 100 || ncols < 1 || ncols > 100 || fps < 1 || fps > 500) {
            cerr << "Error: parametros incorrectos." << endl;
            return EXIT_FAILURE;
        }
    } else {
        cout << "Bienvenido al Juego de la Vida" << endl;
        cout << "Opciones:" << endl;
        cout << argv[0] << " N      - Cuadricula de N * N." << endl;
        cout << argv[0] << " M N    - Cuadricula de M filas y N columnas." << endl;
        cout << argv[0] << " M N F  - Cuadricula de M * N, F fps." << endl;
    }
    
    // Crear juego
    Game game(nrows, ncols, SCREEN_WIDTH, SCREEN_HEIGHT, fps);

    // Configurar colores
    game.setCellColor(0xFF, 0, 0);                      // Rojo
    game.setActiveBackgroundColor(0xFF, 0xFF, 0xFF);    // Blanco
    game.setInactiveBackgroundColor(0xC0, 0xC0, 0xC0);  // Gris claro
    game.setGridColor(0x80, 0x80, 0x80);                // Gris
    
    // Iniciar juego
    game.play();

    return EXIT_SUCCESS;
}
