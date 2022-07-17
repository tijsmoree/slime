#include "cell.h"

#ifndef WORLD_H
#define WORLD_H

class World {
   private:
    Cell** cells;

    float** field;
    float** copyField;

   public:
    int age;

    World();
    ~World();

    void advance();
    void draw(unsigned char* pixels);
};

#endif