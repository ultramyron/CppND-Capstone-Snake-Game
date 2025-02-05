#ifndef GAME_H
#define GAME_H

#include <random>
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "SDL.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int randomNumber);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  int randomNumber;
  Snake snake;
  Food food;
  SDL_Point RegularFood;

// random number generator
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  static int RNG();
  int PlaceFood();
  void Update();
};

#endif