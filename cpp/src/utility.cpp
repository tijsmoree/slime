#include <cstdlib>

float rnd() {
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
}