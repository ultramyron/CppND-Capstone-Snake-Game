#include "snake.h"
#include <cmath>
#include <iostream>
#include <cassert>

void Snake::Update(int flag,  bool &growing,  bool &shrinking,  bool &speeding) {
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
    UpdateBody(current_cell, prev_cell, flag, growing, shrinking, speeding);
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

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, int flag, bool &growing, bool &shrinking, bool &speeding) {
  // Add previous head location to vector
  SDL_Point extraCell = prev_head_cell;
  body.push_back(prev_head_cell);
  // if statements with conditions like "growing" or "faster", etc.

  switch (flag) {
    case 1:
      if (!growing) {
        body.erase(body.begin());
      }
      else {
        std::cout << "I Grew" << std::endl;
        body.push_back(extraCell);
        SetGrowing(growing);
        
        size++;
      }
      break;
    case 2:
      if (!shrinking) {
        body.erase(body.begin());
      }
      else {
        shrinking = false;
        if (size > 1){
        std::cout << "I Shrank" << std::endl;
        size--;
        body.erase(body.begin());
        body.erase(body.begin());
        }
        else{
          std::cout << "already too small" << std::endl;
          shrinking = false;
          body.erase(body.begin());
        }
      }
      break;
    case 3:
      if (!speeding) {
        body.erase(body.begin());
      }
      else {
        std::cout << "Growing Status: " << growing << std::endl;
        std::cout << "I Speed" << std::endl;
        speeding = false;
        speed = speed + .02;
      }
      break;
  }
  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

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
