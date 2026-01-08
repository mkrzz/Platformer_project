#pragma once

#include "GameObject.h"
#include "Vector2.h"


class Enemy : public GameObject
{
 public:
  Enemy();

  bool initialiseEnemies(
    sf::Texture& texture, const std::string& filename, sf::Vector2f position,
    sf::Vector2f scale);
  
  

  void update(float dt);
  void setMovement(Vector2 direction, float speed);
  void setBounds(float min, float max, bool vertical);

  private:

  Vector2 enemy_direction = { 0.0f, 1.0f };
  float movement_speed = 0.0f;
  float min_bounds     = 0.0f;
  float max_bounds     = 0.0f;
  bool is_vertical     = false;

};