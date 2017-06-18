//
//  Juego de la vida
//  Paula Torres
//  17 junio 2017
//

#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include "color.h"

class Grid {
public:
    // Constructor
    Grid(int nrows, int ncols, int width, int height);
    // Destructor
    ~Grid();
    
    // Vivir celula (indices matriz)
    void liveCell(int i, int j);
    // Matar celula (indices matriz)
    void killCell(int i, int j);
    // Estado inicial (matar todas las celulas)
    void reset();
    // Calcular siguiente generacion
    void nextGeneration();
    // Dibujar tablero en pantalla
    void draw(SDL_Renderer * window);
    
    // Color de fondo
    void setBackgroundColor(const Color & color);
    // Color de la celula
    void setCellColor(const Color & color);
    // Color de la cuadricula
    void setGridColor(const Color & color);
    // Alternar dibujo cuadricula
    void toggleGrid();
    // Cambiar dimensiones de la pantalla
    void setSize(int width, int height);
    // Ancho de celda
    int getCellWidth() const;
    // Alto de celda
    int getCellHeight() const;
    
private:
    // Conteo de vecinos (Moore)
    int neighbours(int i, int j) const;
    // Valor de una celula (controlando bordes)
    int getCell(int i, int j) const;
    // Crear nueva matriz
    char ** newMatrix() const;
    // Eliminar matriz vieja
    void deleteMatrix(char ** matrix) const;
    
    int nrows;          // Numero de filas
    int ncols;          // Numero de columnas
    int width;          // Ancho de pantalla
    int height;         // Alto de pantalla
    bool grid;          // Mostrar cuadricula
    char ** cells;      // Matriz de celulas
    SDL_Rect rect;      // Rectangulo (celda)
    Color bgColor;      // Color de fondo
    Color cellColor;    // Color de celula
    Color gridColor;    // Color de cuadricula
};

#endif /* GRID_H */
