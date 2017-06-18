//
//  Juego de la vida
//  Paula Torres
//  17 junio 2017
//

#include <cstring>
#include "grid.h"

// Constructor
Grid::Grid(int nrows, int ncols, int width, int height) {
    this->nrows = nrows;
    this->ncols = ncols;
    this->width = width;
    this->height = height;
    
    grid = true;
    cells = newMatrix();
    
    rect.w = width / ncols;
    rect.h = height / nrows;
    
    // Colores por defecto
    
    bgColor = { 0, 0, 0, 0 };
    cellColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    gridColor = { 0x80, 0x80, 0x80, 0xFF };
}

// Destructor
Grid::~Grid() {
    deleteMatrix(cells);
}

// Vivir celula (indices matriz)
void Grid::liveCell(int i, int j) {
    if (i >= 0 && i < nrows && j >= 0 && j < ncols)
        cells[i][j] = 1;
}

// Matar celula (indices matriz)
void Grid::killCell(int i, int j) {
    if (i >= 0 && i < nrows && j >= 0 && j < ncols)
        cells[i][j] = 0;
}

// Estado inicial (matar todas las celulas)
void Grid::reset() {
    for (int i = 0; i < nrows; i++)
        memset(cells[i], 0, ncols * sizeof(**cells));
}

// Calcular siguiente generacion
void Grid::nextGeneration() {
    char ** next = newMatrix();
    
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (cells[i][j]) {
                switch (neighbours(i, j)) {
                        // Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
                    case 0:
                    case 1:
                        next[i][j] = 0;
                        break;
                        // Any live cell with two or three live neighbours lives on to the next generation.
                    case 2:
                    case 3:
                        next[i][j] = 1;
                        break;
                        // Any live cell with more than three live neighbours dies, as if by overpopulation.
                    default:
                        next[i][j] = 0;
                }
            } else if (neighbours(i, j) == 3) {
                // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                next[i][j] = 1;
            } else {
                next[i][j] = 0;
            }
        }
    }
    
    deleteMatrix(cells);
    cells = next;
}

// Dibujar tablero en pantalla
void Grid::draw(SDL_Renderer * renderer) {
    
    // Blank screen
    SDL_SetRenderDrawColor(renderer, bgColor.red, bgColor.green, bgColor.blue, bgColor.alpha);
    SDL_RenderClear(renderer);
    
    // Draw cells
    
    SDL_SetRenderDrawColor(renderer, cellColor.red, cellColor.green, cellColor.blue, cellColor.alpha);
    
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (cells[i][j]) {
                rect.x = rect.w * j;
                rect.y = rect.h * i;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    
    // Draw grid lines (if enabled)
    
    if (grid) {
        
        SDL_SetRenderDrawColor(renderer, gridColor.red, gridColor.green, gridColor.blue, gridColor.alpha);
        
        // Draw horizontal lines
        
        for (int i = 1; i <= nrows; i++) {
            int y = rect.h * i;
            SDL_RenderDrawLine(renderer, 0, y, width, y);
        }
        
        // Draw vertical lines
        
        for (int j = 1; j <= ncols; j++) {
            int x = rect.w * j;
            SDL_RenderDrawLine(renderer, x, 0, x, height);
        }
    }
}

// Color de fondo
void Grid::setBackgroundColor(const Color & color) {
    bgColor = color;
}

// Color de la celula
void Grid::setCellColor(const Color & color) {
    cellColor = color;
}

// Color de la cuadricula
void Grid::setGridColor(const Color & color) {
    gridColor = color;
}

// Alternar dibujo cuadricula
void Grid::toggleGrid() {
    grid = !grid;
}

// Cambiar dimensiones de la pantalla
void Grid::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    rect.w = width / ncols;
    rect.h = height / nrows;
}

// Ancho de celda
int Grid::getCellWidth() const {
    return rect.w;
}

// Alto de celda
int Grid::getCellHeight() const {
    return rect.h;
}

// Conteo de vecinos (Moore)
int Grid::neighbours(int i, int j) const {
    // (i-1 j-1)  (i-1 j)  (i-1 j+1)
    // (i   j-1)   -----   (i   j+1)
    // (i+1 j-1)  (i+1 j)  (i+1 j+1)
    
    int count = 0;
    
    for (int m = i - 1; m <= i + 1; m++)
        for (int n = j - 1; n <= j + 1; n++)
            // Skip central cell
            if (!(m == i && n == j))
                count += getCell(m, n);
    
    return count;
}

// Valor de una celula (controlando bordes)
int Grid::getCell(int i, int j) const {
    return (i >= 0 && i < nrows && j >= 0 && j < ncols) ? cells[i][j] : 0;
}

// Crear nueva matriz
char ** Grid::newMatrix() const {
    char ** matrix = new char * [nrows];
    
    for (int i = 0; i < nrows; i++)
        matrix[i] = new char[ncols]();
    
    return matrix;
}

// Eliminar matriz vieja
void Grid::deleteMatrix(char ** matrix) const {
    for (int i = 0; i < nrows; i++)
        delete [] matrix[i];
    
    delete [] matrix;
}
