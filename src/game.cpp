//
//  Juego de la vida
//  Paula Torres
//  18 junio 2017
//

#include <iostream>
#include "game.h"

using namespace std;

// Constructor
Game::Game(int nrows, int ncols, int width, int height, int fps) : grid(nrows, ncols, width, height) {
    
    // Iniciar SDL
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    
    // Create window
    
    if (window = SDL_CreateWindow("Juego de la vida", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE), !window) {
        cerr << "No se pudo crear una ventana: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    
    // Create renderer
    
    if (renderer = SDL_CreateRenderer(window, 0, 0), !renderer) {
        cerr << "No se pudo crear un objeto de dibujo: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    // Valores por defecto
    
    state = PAUSED;
    bgActive = { 0, 0, 0, 0 };
    bgInactive = { 0, 0, 0, 0 };
    frameDelay = 1000 / fps;
}

// Destructor
Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Bucle principal del juego
void Game::play() {
    while (true) {
        
        // Atender eventos
        
        switch (dispatchEvents()) {
            case NONE:
                grid.nextGeneration();
                break;
            
            case DISPATCHED:
                break;
                
            case QUIT:
                return;
        }

        // Dibujar y actualizar pantalla
        
        grid.draw(renderer);
        SDL_RenderPresent(renderer);
    }
}

// Color de la celula (RGBA)
void Game::setCellColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    grid.setCellColor({ red, green, blue, alpha });
}

// Color de fondo cuando esta en modo activo
void Game::setActiveBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    bgActive = { red, green, blue, alpha };
    
    if (state == PLAYING)
        grid.setBackgroundColor(bgActive);
}

// Color de fondo cuando esta en pausa
void Game::setInactiveBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    bgInactive = { red, green, blue, alpha };
    
    if (state == PAUSED)
        grid.setBackgroundColor(bgInactive);
}

// Color de la cuadricula
void Game::setGridColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    grid.setGridColor({ red, green, blue, alpha });
}

// Atender un evento (ventana, teclado, raton)
Game::EventResult Game::dispatchEvents() {
    SDL_Event event;
    
    if (state == PLAYING ? SDL_WaitEventTimeout(&event, frameDelay) : SDL_WaitEvent(&event)) {
        switch (event.type) {
            // Pantalla redimensionada
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    grid.setSize(event.window.data1, event.window.data2);
                }
                break;
                
            // Tecla pulsada
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        grid.nextGeneration();
                        break;
                        
                    case SDLK_ESCAPE:
                        return QUIT;
                        
                    case SDLK_SPACE:
                        switch (state) {
                            case PAUSED:
                                setPlaying();
                                break;
                                
                            case PLAYING:
                                setPaused();
                        }
                        break;
                        
                    case SDLK_r:
                        grid.reset();
                        break;
                        
                    case SDLK_v:
                        grid.toggleGrid();
                }
                
            // Desplazamiento del raton
            case SDL_MOUSEMOTION:
                if ((event.motion.state & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK)
                    liveCell(event.motion.x, event.motion.y);
                else if ((event.motion.state & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK)
                    killCell(event.motion.x, event.motion.y);
                
            // Boton del raton pulsado
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        liveCell(event.button.x, event.button.y);
                        break;
                        
                    case SDL_BUTTON_RIGHT:
                        killCell(event.button.x, event.button.y);
                        break;
                }
                break;
                
            // Salir del programa
            case SDL_QUIT:
                return QUIT;
        }
        
        return DISPATCHED;
    } else {
        return NONE;
    }
}

// Poner en modo activo
void Game::setPlaying() {
    state = PLAYING;
    grid.setBackgroundColor(bgActive);
}

// Poner en pausa
void Game::setPaused() {
    state = PAUSED;
    grid.setBackgroundColor(bgInactive);
}

// Vivir celula (coordenadas ventana)
void Game::liveCell(int x, int y) {
    grid.liveCell(y / grid.getCellHeight(), x / grid.getCellWidth());
}

// Matar celula (coordenadas ventana)
void Game::killCell(int x, int y) {
    grid.killCell(y / grid.getCellHeight(), x / grid.getCellWidth());
}
