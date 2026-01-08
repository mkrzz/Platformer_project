#include "Enemy.h"

Enemy::Enemy()
{
  enemy_direction = { 0, 0 };
  movement_speed  = 0.0f;

}

bool Enemy::initialiseEnemies(
  sf::Texture& texture, const std::string& filename, sf::Vector2f position,
  sf::Vector2f scale)
{
  if (!initialiseSprite(texture, filename))
    return false;

  getSprite()->setPosition(position);
  getSprite()->setScale(scale);
  return true;
}

void Enemy::update(float dt) 
{
  sf::Vector2f currentPos = getSprite()->getPosition();

  if (is_vertical)
  {
    currentPos.y += enemy_direction.y * movement_speed * dt;

    if (currentPos.y < min_bounds || currentPos.y > max_bounds)
    {
      enemy_direction.y *= -1; 
      currentPos.y = std::clamp(currentPos.y, min_bounds, max_bounds);
    }
    if (enemy_direction.y > 0)
    {
      //flip sprite upwards
      getSprite()->setScale(0.2f, -0.2f); 
    }
    else
    {
      //Flip sprite downwards
      getSprite()->setScale(0.2f, 0.2f);
    }
  }
  else
  {
    currentPos.x += enemy_direction.x * movement_speed * dt;

    if (currentPos.x < min_bounds)
    {
      currentPos.x = min_bounds;
      enemy_direction.x *= -1; 
    }
    else if (currentPos.x > max_bounds)
    {
      currentPos.x = max_bounds;
      enemy_direction.x *= -1;
      
    }
    if (enemy_direction.x > 0)
    {
      getSprite()->setScale(0.2f, 0.2f); 
    }
    else
    {
      getSprite()->setScale(-0.2f, 0.2f);
    }
  }

  getSprite()->setPosition(currentPos);
}

void Enemy::setMovement(Vector2 direction, float speed) 
{
  enemy_direction = direction;
  movement_speed  = speed;

}

void Enemy::setBounds(float min, float max, bool vertical) 
{
  min_bounds = min;
  max_bounds = max;
  is_vertical = vertical;

};