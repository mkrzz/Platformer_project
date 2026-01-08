#pragma once

#include <SFML/Graphics.hpp>
#include "vector2.h"


class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture& texture, std::string filename);

  sf::Sprite* getSprite() const;

  

  void move(float offsetX, float offsetY)
  {
    if (sprite != nullptr)
    {
      sprite->move(offsetX, offsetY);
    }
  }

  void setPosition(float x, float y) { sprite->setPosition(x, y); }

  private:
  sf::Sprite* sprite = nullptr;

};
