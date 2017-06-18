//
//  Juego de la vida
//  Paula Torres
//  18 junio 2017
//

#ifndef GAME_H
#define GAME_H

#include "grid.h"

class Game {
public:
    // Constructor
    Game(int nrows, int ncols, int width, int height, int fps);
    // Destructor
    ~Game();
    
    // Bucle principal del juego
    void play();
    
    // Color de la celula (RGBA)
    void setCellColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF);
    // Color de fondo cuando esta en modo activo
    void setActiveBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF);
    // Color de fondo cuando esta en pausa
    void setInactiveBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF);
    // Color de la cuadricula
    void setGridColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF);
    
private:
    // Resultado del metodo dispatchEvents()
    enum EventResult { NONE, DISPATCHED, QUIT };
    
    // Atender un evento (ventana, teclado, raton)
    EventResult dispatchEvents();
    // Poner en modo activo
    void setPlaying();
    // Poner en pausa
    void setPaused();
    // Vivir celula (coordenadas ventana)
    void liveCell(int x, int y);
    // Matar celula (coordenadas ventana)
    void killCell(int x, int y);
    
    Grid grid;                              // Tablero de juego
    enum State { PAUSED, PLAYING } state;   // Estado del juego
    SDL_Window * window;                    // Ventana del programa
    SDL_Renderer * renderer;                // Objeto de dibujo
    Color bgActive;                         // Color fondo activo
    Color bgInactive;                       // Color fondo inactivo
    int frameDelay;                         // Retraso entre frames (ms)
};

#endif /* GAME_H */
