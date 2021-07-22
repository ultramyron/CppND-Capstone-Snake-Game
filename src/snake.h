#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include <vector>


class Food {
public:

Food()
  : growing(false),
  shrinking(false),
  speeding(false){};

void SetGrowing(bool& growing){
  growing = !growing;
}
bool GrowBody(){
  growing = true;
  return growing;
}
bool ShrinkDown() {
  shrinking = true;
  return shrinking;
}
bool SpeedUp() {
  speeding = true;
  return speeding;
}
  bool growing;
  bool shrinking;
  bool speeding;


};
class Snake : public Food{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2){}

  void Update(int flag, bool &growing, bool &shrinking, bool &speeding);

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, int flag, bool &growing, bool &shrinking, bool &speeding);


  int grid_width;
  int grid_height;

  friend class Food;

};
#endif