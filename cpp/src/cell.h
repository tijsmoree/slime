#include <SDL2/SDL.h>

#ifndef CELL_H
#define CELL_H

class Cell {
   private:
    float a;

   public:
    float x;
    float y;

    Cell();
    ~Cell() = default;

    void advance(float** field);
};

#endif