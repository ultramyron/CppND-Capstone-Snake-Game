#include "snake.h"
#include <cmath>
#include <iostream>

bool Snake::growing = false;
bool Snake::shrinking = false;
bool Snake::speeding = false;
void Snake::Update(int flag) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell, flag);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, int flag) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  // if statements with conditions like "growing" or "faster", etc.
  // 
  //std::cout << "growing status: " << growing << std::endl;
  //std::cout << "shrinking status: " << shrinking << std::endl;
  //std::cout << "speeding status: " << speeding << std::endl;
  //std::cout << "flag status: " << flag << std::endl;

  switch (flag) {
    case 1:
      if (!growing) {
        body.erase(body.begin());
      }
      else {
        std::cout << "helo"<< std::endl;
        growing = false;
        size++;
      }
      break;
    case 2:
      if (!growing) {
        body.erase(body.begin());
      }
      else {
        std::cout << "helo"<< std::endl;
        growing = false;
        size++;
      }
      break;
    case 3:
      if (!growing) {
        body.erase(body.begin());
      }
      else {
        std::cout << "helo"<< std::endl;
        growing = false;
        size++;
      }
      break;
  }
  /*
  if (!growing && flag == 1) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else{
    std::cout << "helo"<< std::endl;
    growing = false;
    size++;
  }
  
  else if (!speeding && flag == 2) {
    body.erase(body.begin());
  } else {
    std::cout << "helo"<< std::endl;
    speeding = false;
    size++;
  }
  else if (!shrinking && flag == 3) {
    body.erase(body.begin());
  } else {
    std::cout << "helo"<< std::endl;
    shrinking = false;
    size++;
  }
  */
  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Food::GrowBody(){
    Snake::growing = true;
    return Snake::growing;
}
bool Food::ShrinkDown() {
    Snake::growing = true;
    return Snake::growing;
}

bool Food::SpeedUp() {
    Snake::growing = true;
    return Snake::growing;
}