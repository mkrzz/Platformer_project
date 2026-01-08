#pragma once

#include "GameObject.h"

class Platform : public GameObject
{
 public:
  Platform() = default;

  bool initialisePlatform(
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
