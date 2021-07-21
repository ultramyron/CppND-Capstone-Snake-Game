#include "Food.h"

Food::Food(bool _shrinking, bool _speeding, bool _growing) 
    : _shrinking(false),
    _speeding(false),
    _growing(false) { }

bool Food::GrowBody(){
    _growing = true;
    return _growing;
}
bool Food::ShrinkDown() {
    _shrinking = true;
    return _shrinking;
}

bool Food::SpeedUp() {
    _speeding = true;
    return _speeding;
}