#include "cell.h"

#include <math.h>

#include "settings.h"
#include "utility.h"

#define TWO_PI 6.28318530718f

Cell::Cell() {
    float r = SPAWNRADIUS * sqrt(rnd());
    float f = rnd() * TWO_PI;

    x = WIDTH * 0.5f + r * cos(f);
    y = HEIGHT * 0.5f + r * sin(f);

    a = atan2(HEIGHT * 0.5f - y, WIDTH * 0.5f - x);
}

void Cell::advance(float** field) {
    int xF = x + cos(a) * SIGHT;
    int yF = y + sin(a) * SIGHT;
    int xL = x + cos(a - SIGHTANGLE) * SIGHT;
    int yL = y + sin(a - SIGHTANGLE) * SIGHT;
    int xR = x + cos(a + SIGHTANGLE) * SIGHT;
    int yR = y + sin(a + SIGHTANGLE) * SIGHT;

    if ((xF >= 0 && yF >= 0 && xF < WIDTH && yF < HEIGHT) &&
        (xL >= 0 && yL >= 0 && xL < WIDTH && yL < HEIGHT) &&
        (xR >= 0 && yR >= 0 && xR < WIDTH && yR < HEIGHT)) {
        float valF = field[xF][yF];
        float valL = field[xL][yL];
        float valR = field[xR][yR];

        if (valF < valL && valF > valR) {
            a -= STEERSWING;
        } else if (valF < valR && valF > valL) {
            a += STEERSWING;
        }
    }

    x += cos(a) * SPEED;
    y += sin(a) * SPEED;

    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) {
        a = atan2(HEIGHT * 0.5f - y, WIDTH * 0.5f - x) +
            (rnd() - 0.5f) * BOUNCESWING;
    }
}
