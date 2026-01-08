#pragma once



#include "GameObject.h"

class Orbs : public GameObject
{
 public:
 Orbs() = default;

  bool initialiseOrbs(
    sf::Texture& texture, const std::string& filename, sf::Vector2f position,
    sf::Vector2f scale)
  {
    if (!initialiseSprite(texture, filename))

      return false;

    getSprite()->setPosition(position);
    getSprite()->setScale(scale);

    return true;
  }
};
