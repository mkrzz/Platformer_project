#include "GameObject.h"
#include "Game.h"
#include <iostream>

GameObject::GameObject()
{
  sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
  
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
    if (!texture.loadFromFile(filename))
    {
       std::cout << "Error loading file";
      return false;
    }

    sprite->setTexture(texture);
    
    return true;
}


sf::Sprite* GameObject::getSprite() const
{
  return sprite;
}

