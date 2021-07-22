#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
Game::Game(std::size_t grid_width, std::size_t grid_height, int randomNumber)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      randomNumber(0) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    // starts the clock for the frame
    //std::cout << "Snake Speed: " << snake.speed << std::endl;
    frame_start = SDL_GetTicks();
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();

    renderer.Render(snake, RegularFood, Game::randomNumber);
    
    // ends the clock for the frame
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, Game::randomNumber);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target millisec_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      // wait for a specified number of seconds before returning , if frame_duration is less than target_frame_duration, then we wait the difference between the two
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

int Game::RNG() {
    int max = 3;
    int min = 0;

    srand(time(0));
    int randNum = (rand() % max) + 1;

    return randNum;
}

int Game::PlaceFood() {
  int x, y;
  while (true) {
    // using our random number generator to generate random points for the food
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    
    Game::randomNumber = Game::RNG();
    if (!snake.SnakeCell(x, y)) {

      RegularFood.x = x;
      RegularFood.y = y;
      if (Game::randomNumber == 1) {std::cout << "Placed Regular food!" << std::endl;}
      else if (Game::randomNumber == 2) {std::cout << "Placed Shrink food!" << std::endl;}
      else if (Game::randomNumber == 3) {std::cout << "Placed Speed food!" << std::endl;}

      return Game::randomNumber;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  
  snake.Update(Game::randomNumber, food.growing, food.shrinking, food.speeding);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (RegularFood.x == new_x && RegularFood.y == new_y) {
    std::cout << "score increased" << std::endl;
    score++;
    std::cout << "score: " << GetScore() << std::endl;
    std::cout << "size of body: " << snake.body.size() << std::endl;
    PlaceFood();
    // Grow snake and increase speed.
    if (Game::randomNumber == 1){
      food.GrowBody();
    }
    else if (Game::randomNumber == 2) {
      food.ShrinkDown();
    }
    else if (Game::randomNumber == 3) {
      food.SpeedUp();
    }
    snake.speed += 0.02;
  }

  
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.body.size(); }