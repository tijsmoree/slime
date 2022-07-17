#include "world.h"

#include <iostream>
#include <vector>

#include "cell.h"
#include "settings.h"

World::World() : age(0) {
    cells = new Cell *[N];
    for (int i = 0; i < N; i++) {
        cells[i] = new Cell();
    }

    field = new float *[WIDTH];
    copyField = new float *[WIDTH];
    for (int i = 0; i < WIDTH; i++) {
        field[i] = new float[HEIGHT];
        copyField[i] = new float[HEIGHT];

        for (int j = 0; j < HEIGHT; j++) {
            field[i][j] = 0.0f;
            copyField[i][j] = 0.0f;
        }
    }
}

World::~World() {
    for (int i = 0; i < N; i++) {
        delete cells[i];
    }
    delete[] cells;

    for (int i = 0; i < WIDTH; i++) {
        delete[] field[i];
        delete[] copyField[i];
    };
    delete[] field;
    delete[] copyField;
}

void World::advance() {
    age++;

    for (int i = 0; i < N; i++) {
        cells[i]->advance(field);
    }
}

void World::draw(unsigned char *pixels) {
    for (int i = 0; i < N; i++) {
        int x = cells[i]->x + 0.5f;
        int y = cells[i]->y + 0.5f;

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            field[x][y] = 255;
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            copyField[i][j] = field[i][j];

            copyField[i][j] += j < HEIGHT - 1 ? field[i][j + 1] : 0.0f;
            copyField[i][j] += j > 0 ? field[i][j - 1] : 0.0f;
            copyField[i][j] += i < WIDTH - 1 ? field[i + 1][j] : 0.0f;
            copyField[i][j] += i > 0 ? field[i - 1][j] : 0.0f;

            copyField[i][j] +=
                i < WIDTH - 1 && j < HEIGHT - 1 ? field[i + 1][j + 1] : 0.0f;
            copyField[i][j] += i > 0 && j > 0 ? field[i - 1][j - 1] : 0.0f;
            copyField[i][j] +=
                i < WIDTH - 1 && j > 0 ? field[i + 1][j - 1] : 0.0f;
            copyField[i][j] +=
                i > 0 && j < HEIGHT - 1 ? field[i - 1][j + 1] : 0.0f;
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            field[i][j] = 0.11f * ALPHA * copyField[i][j];
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            pixels[(WIDTH * i + j) * 4 + 1] = field[i][j];
        }
    }
}
