#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

class Food {
private:
    SDL_Point RegularFood;
    SDL_Point SpeedUpFood;
    SDL_Point SmallFood;

    bool _shrinking;
    bool _speeding;
    bool _growing;
public:

    Food(bool _shrinking, bool _speeding, bool _growing);
    bool GrowBody();
    bool SpeedUp();
    bool ShrinkDown();
};

#endif