
#include "Game.h"
#include <iostream>
#include "GameObject.h"
#include "Platform.h"
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "Orbs.h"


Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  
  in_menu = true;


  menuTexts();
  eyeTextures();
  initialisePlatforms();
  initialiseEnemies();
  backgroundTextures();
  soundEffects();
  moveScreen();
  initialiseOrbs();
  uiTextures();
  menuMusic();
  
  
     
  return true;

}

void Game::update(float dt)
{
  if (is_running == true)
  {
    
      if (!in_menu)
      {

        movePlayer(dt);
        applyGravity(dt);
        handlePlayerInput();
        screenSpeed(dt);
        updateEnemies(dt);
        
      
      }
     
      checkPlatformCollisions();
      checkWallCollisions();
      checkPlayerEnemyCollision();
      checkPlayerOrbCollision();    
      resetPlayerColour();
    
  }

  if ((is_dead || has_won) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {

    restartGame();

  }

  
}

void Game::render()
{
  
    if (in_menu)
    {
      
      renderMenu();
      
    }
    else if (has_won)
    {

      winText();

    }
    else if (is_dead)
    {
      
      deadText();
      
    }
    else if (is_running)
    {

      renderWorld();
      
    }
    
}

void Game::mouseClicked(sf::Event event)
{
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
   
  if (in_menu)
  {
    
      if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
      {

        toggleMenuSelection();

      }
      else if (event.key.code == sf::Keyboard::Enter)
      {

        handleMenuSelection();
        backgroundMusic();
        menuPlaySound();
        
      }
      
  }

  
  if (event.key.code == sf::Keyboard::A)
  {

    handleMoveLeft();

  }
  else if (event.key.code == sf::Keyboard::D)
  {

    handleMoveRight();

  }

  
  if (event.key.code == sf::Keyboard::Space)
  {
   
    handleJump();
      
  }

}

void Game::keyReleased(sf::Event event) 
{
    if ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))
    {
      
        stopPlayerHorizontalMovement();

    }
       
        
}






// - - - - - - - - - - - - - Initialisation - - - - - - - - - - - - -


void Game::initialiseEnemies()
{
  // textures
  enemy_texture_right_arrow.loadFromFile("../Data/Images/Yellow_paint_large/"
                                         "paint_arrow_right_double.png");
  enemy_texture_up_arrow.loadFromFile("../Data/Images/Yellow_paint_large/"
                                      "paint_arrow_up_double.png");

   Enemy enemy1;
  enemy1.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy1.getSprite()->setPosition(780, -300);
  enemy1.getSprite()->setScale(0.2f, 0.2f);
  enemy1.getSprite()->setColor(sf::Color::Red);
  enemy1.setMovement(Vector2(0.f, 1.0f), 200.f);
  enemy1.setBounds(-600.0f, -180.0f, true);
  enemies.push_back(enemy1);

  Enemy enemy2;
  enemy2.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy2.getSprite()->setPosition(350, -1520);
  enemy2.getSprite()->setScale(0.2f, 0.2f);
  enemy2.getSprite()->setColor(sf::Color::Red);
  enemy2.setMovement(Vector2(-1.0f, 0.0f), 200.f);
  enemy2.setBounds(280.0f, 900.0f, false);
  enemies.push_back(enemy2);

  Enemy enemy3;
  enemy3.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy3.getSprite()->setPosition(540, -800);
  enemy3.getSprite()->setScale(0.2f, 0.2f);
  enemy3.getSprite()->setColor(sf::Color::Red);
  enemy3.setMovement(Vector2(0.f, 1.0f), 300.f);
  enemy3.setBounds(-1300.0f, -750.0f, true);
  enemies.push_back(enemy3);

  Enemy enemy4;
  enemy4.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy4.getSprite()->setPosition(400, -1700);
  enemy4.getSprite()->setScale(0.2f, 0.2f);
  enemy4.getSprite()->setColor(sf::Color::Red);
  enemy4.setMovement(Vector2(0.f, 1.0f), 300.f);
  enemy4.setBounds(-1900.0f, -1600.0f, true);
  enemies.push_back(enemy4);

  Enemy enemy5;
  enemy5.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy5.getSprite()->setPosition(180, -2500);
  enemy5.getSprite()->setScale(0.2f, 0.2f);
  enemy5.getSprite()->setColor(sf::Color::Red);
  enemy5.setMovement(Vector2(0.f, 1.0f), 100.f);
  enemy5.setBounds(-2700.0f, -2500.0f, true);
  enemies.push_back(enemy5);

  Enemy enemy6;
  enemy6.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy6.getSprite()->setPosition(700, -2100);
  enemy6.getSprite()->setScale(0.2f, 0.2f);
  enemy6.getSprite()->setColor(sf::Color::Red);
  enemy6.setMovement(Vector2(-1.f, 0.0f), 200.f);
  enemy6.setBounds(600.0f, 950.0f, false);
  enemies.push_back(enemy6);

  /*Enemy enemy7;
  enemy7.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy7.getSprite()->setPosition(450, -2700);
  enemy7.getSprite()->setScale(0.2f, 0.2f);
  enemy7.getSprite()->setColor(sf::Color::Red);
  enemy7.setMovement(Vector2(0.f, 1.0f), 300.f);
  enemy7.setBounds(-3000.0f, -2300.0f, true);
  enemies.push_back(enemy7);*/

  Enemy enemy8;
  enemy8.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy8.getSprite()->setPosition(100, -3120);
  enemy8.getSprite()->setScale(0.2f, 0.2f);
  enemy8.getSprite()->setColor(sf::Color::Red);
  enemy8.setMovement(Vector2(1.f, 0.0f), 200.f);
  enemy8.setBounds(100.0f, 500.0f, false);
  enemies.push_back(enemy8);

  Enemy enemy9;
  enemy9.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy9.getSprite()->setPosition(200, -3025);
  enemy9.getSprite()->setScale(0.2f, 0.2f);
  enemy9.getSprite()->setColor(sf::Color::Red);
  enemy9.setMovement(Vector2(1.f, 0.0f), 120.f);
  enemy9.setBounds(100.0f, 280.0f, false);
  enemies.push_back(enemy9);

  Enemy enemy10;
  enemy10.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy10.getSprite()->setPosition(680, -3500);
  enemy10.getSprite()->setScale(0.2f, 0.2f);
  enemy10.getSprite()->setColor(sf::Color::Red);
  enemy10.setMovement(Vector2(0.f, 1.f), 100.f);
  enemy10.setBounds(-3700.f, -3400.f, true);
  enemies.push_back(enemy10);

  Enemy enemy11;
  enemy11.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy11.getSprite()->setPosition(200, -4220);
  enemy11.getSprite()->setScale(0.2f, 0.2f);
  enemy11.getSprite()->setColor(sf::Color::Red);
  enemy11.setMovement(Vector2(0.f, 1.f), 200.f);
  enemy11.setBounds(-4400.f, -4200.f, true);
  enemies.push_back(enemy11);

  Enemy enemy12;
  enemy12.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy12.getSprite()->setPosition(720, -3330);
  enemy12.getSprite()->setScale(0.2f, 0.2f);
  enemy12.getSprite()->setColor(sf::Color::Red);
  enemy12.setMovement(Vector2(1.f, 0.0f), 80.f);
  enemy12.setBounds(720.0f, 950.0f, false);
  enemies.push_back(enemy12);

  Enemy enemy13;
  enemy13.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy13.getSprite()->setPosition(450, -4200);
  enemy13.getSprite()->setScale(0.2f, 0.2f);
  enemy13.getSprite()->setColor(sf::Color::Red);
  enemy13.setMovement(Vector2(0.f, 1.f), 200.f);
  enemy13.setBounds(-4000.f, -3700.f, true);
  enemies.push_back(enemy13);

  Enemy enemy14;
  enemy14.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy14.getSprite()->setPosition(380, -3530);
  enemy14.getSprite()->setScale(0.2f, 0.2f);
  enemy14.getSprite()->setColor(sf::Color::Red);
  enemy14.setMovement(Vector2(1.f, 0.0f), 150.f);
  enemy14.setBounds(380.0f, 600.0f, false);
  enemies.push_back(enemy14);

  Enemy enemy15;
  enemy15.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy15.getSprite()->setPosition(380, -4150);
  enemy15.getSprite()->setScale(0.2f, 0.2f);
  enemy15.getSprite()->setColor(sf::Color::Red);
  enemy15.setMovement(Vector2(1.f, 0.0f), 150.f);
  enemy15.setBounds(350.0f, 600.0f, false);
  enemies.push_back(enemy15);

  Enemy enemy16;
  enemy16.getSprite()->setTexture(enemy_texture_right_arrow);
  enemy16.getSprite()->setPosition(300, -4340);
  enemy16.getSprite()->setScale(0.2f, 0.2f);
  enemy16.getSprite()->setColor(sf::Color::Red);
  enemy16.setMovement(Vector2(1.f, 0.0f), 125.f);
  enemy16.setBounds(300.0f, 700.0f, false);
  enemies.push_back(enemy16);

  //ARROW TOUCHING LAST ORB
  Enemy enemy17;
  enemy17.getSprite()->setTexture(enemy_texture_up_arrow);
  enemy17.getSprite()->setPosition(760, -4100);
  enemy17.getSprite()->setScale(0.2f, 0.2f);
  enemy17.getSprite()->setColor(sf::Color::Red);
  enemy17.setMovement(Vector2(0.f, 1.f), 200.f);
  enemy17.setBounds(-4200.f, -3900.f, true);
  enemies.push_back(enemy17);
}

void Game::initialisePlatforms()
{
  // textures
  platform_a_texture.loadFromFile("../Data/Images/Yellow_paint_large/"
                                  "paint_drips_a_double.png ");
  platform_b_texture.loadFromFile("../Data/Images/Yellow_paint_large/"
                                  "paint_drips_b_double.png ");

  // Set position for platform 1
  GameObject platform1;
  platform1.getSprite()->setTexture(platform_a_texture);
  platform1.getSprite()->setPosition(50, 600);
  platform1.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform1);

  // Set position for platform 2
  GameObject platform2;
  platform2.getSprite()->setTexture(platform_a_texture);
  platform2.getSprite()->setPosition(400, 500);
  platform2.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform2);

  // Set position for platform 3
  GameObject platform3;
  platform3.getSprite()->setTexture(platform_a_texture);
  platform3.getSprite()->setPosition(150, 400);
  platform3.getSprite()->setScale(0.55f, 0.55f);
  platforms.push_back(platform3);

  
  GameObject platform4;
  platform4.getSprite()->setTexture(platform_b_texture);
  platform4.getSprite()->setPosition(500, 300);
  platform4.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform4);

  GameObject platform5;
  platform5.getSprite()->setTexture(platform_a_texture);
  platform5.getSprite()->setPosition(300, 200);
  platform5.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform5);

  GameObject platform6;
  platform6.getSprite()->setTexture(platform_a_texture);
  platform6.getSprite()->setPosition(550, 100);
  platform6.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform6);

  GameObject platform7;
  platform7.getSprite()->setTexture(platform_b_texture);
  platform7.getSprite()->setPosition(350, 0);
  platform7.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform7);

  GameObject platform8;
  platform8.getSprite()->setTexture(platform_b_texture);
  platform8.getSprite()->setPosition(700, -100);
  platform8.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform8);

  GameObject platform9;
  platform9.getSprite()->setTexture(platform_b_texture);
  platform9.getSprite()->setPosition(350, -200);
  platform9.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform9);

  GameObject platform10;
  platform10.getSprite()->setTexture(platform_a_texture);
  platform10.getSprite()->setPosition(150, -300);
  platform10.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform10);

  GameObject platform11;
  platform11.getSprite()->setTexture(platform_b_texture);
  platform11.getSprite()->setPosition(500, -400);
  platform11.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform11);

  GameObject platform12;
  platform12.getSprite()->setTexture(platform_a_texture);
  platform12.getSprite()->setPosition(300, -500);
  platform12.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform12);

  GameObject platform13;
  platform13.getSprite()->setTexture(platform_a_texture);
  platform13.getSprite()->setPosition(400, -620);
  platform13.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform13);

  GameObject platform14;
  platform14.getSprite()->setTexture(platform_b_texture);
  platform14.getSprite()->setPosition(100, -750);
  platform14.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform14);

  // 1st orb platform
  GameObject platform15;
  platform15.getSprite()->setTexture(platform_a_texture);
  platform15.getSprite()->setPosition(900, -400);
  platform15.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform15);

  GameObject platform16;
  platform16.getSprite()->setTexture(platform_a_texture);
  platform16.getSprite()->setPosition(350, -850);
  platform16.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform16);

  GameObject platform17;
  platform17.getSprite()->setTexture(platform_b_texture);
  platform17.getSprite()->setPosition(600, -950);
  platform17.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform17);

  GameObject platform18;
  platform18.getSprite()->setTexture(platform_a_texture);
  platform18.getSprite()->setPosition(850, -1050);
  platform18.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform18);

  GameObject platform19;
  platform19.getSprite()->setTexture(platform_a_texture);
  platform19.getSprite()->setPosition(600, -1150);
  platform19.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform19);

  GameObject platform20;
  platform20.getSprite()->setTexture(platform_a_texture);
  platform20.getSprite()->setPosition(350, -1250);
  platform20.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform20);

  GameObject platform21;
  platform21.getSprite()->setTexture(platform_b_texture);
  platform21.getSprite()->setPosition(100, -1350);
  platform21.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform21);

  // long platform - position an enemy
  GameObject platform22;
  platform22.getSprite()->setTexture(platform_b_texture);
  platform22.getSprite()->setPosition(250, -1460);
  platform22.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform22);
  // long platform -  position an enemy
  GameObject platform23;
  platform23.getSprite()->setTexture(platform_a_texture);
  platform23.getSprite()->setPosition(450, -1460);
  platform23.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform23);
  // long platform - position an enemy
  GameObject platform24;
  platform24.getSprite()->setTexture(platform_b_texture);
  platform24.getSprite()->setPosition(600, -1460);
  platform24.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform24);
  // long platform - position an enemy
  GameObject platform25;
  platform25.getSprite()->setTexture(platform_a_texture);
  platform25.getSprite()->setPosition(750, -1460);
  platform25.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform25);

  GameObject platform26;
  platform26.getSprite()->setTexture(platform_a_texture);
  platform26.getSprite()->setPosition(850, -1550);
  platform26.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform26);

  // 2nd long platform - position an enemy
  // orb is here

  GameObject platform27;
  platform27.getSprite()->setTexture(platform_b_texture);
  platform27.getSprite()->setPosition(150, -1680);
  platform27.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform27);

  // 2nd long platform - position an enemy
  GameObject platform28;
  platform28.getSprite()->setTexture(platform_b_texture);
  platform28.getSprite()->setPosition(500, -1680);
  platform28.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform28);
  // 2nd long platform - position an enemy
  GameObject platform29;
  platform29.getSprite()->setTexture(platform_a_texture);
  platform29.getSprite()->setPosition(650, -1680);
  platform29.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform29);

  GameObject platform30;
  platform30.getSprite()->setTexture(platform_a_texture);
  platform30.getSprite()->setPosition(900, -1800);
  platform30.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform30);

  //orb
  GameObject platform31;
  platform31.getSprite()->setTexture(platform_b_texture);
  platform31.getSprite()->setPosition(680, -1900);
  platform31.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform31);

  GameObject platform32;
  platform32.getSprite()->setTexture(platform_a_texture);
  platform32.getSprite()->setPosition(500, -2000);
  platform32.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform32);

  GameObject platform33;
  platform33.getSprite()->setTexture(platform_b_texture);
  platform33.getSprite()->setPosition(300, -2100);
  platform33.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform33);

  //orb 
  GameObject platform34;
  platform34.getSprite()->setTexture(platform_a_texture);
  platform34.getSprite()->setPosition(550, -2200);
  platform34.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform34);

  GameObject platform35;
  platform35.getSprite()->setTexture(platform_b_texture);
  platform35.getSprite()->setPosition(700, -2300);
  platform35.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform35);

  GameObject platform36;
  platform36.getSprite()->setTexture(platform_a_texture);
  platform36.getSprite()->setPosition(500, -2400);
  platform36.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform36);

  GameObject platform37;
  platform37.getSprite()->setTexture(platform_b_texture);
  platform37.getSprite()->setPosition(250, -2500);
  platform37.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform37);

  GameObject platform38;
  platform38.getSprite()->setTexture(platform_a_texture);
  platform38.getSprite()->setPosition(450, -2600);
  platform38.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform38);

  GameObject platform39;
  platform39.getSprite()->setTexture(platform_b_texture);
  platform39.getSprite()->setPosition(700, -2700);
  platform39.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform39);

  // two close orbs are here
  GameObject platform40;
  platform40.getSprite()->setTexture(platform_a_texture);
  platform40.getSprite()->setPosition(0, -2500);
  platform40.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform40);

  GameObject platform41;
  platform41.getSprite()->setTexture(platform_b_texture);
  platform41.getSprite()->setPosition(400, -2820);
  platform41.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform41);

  GameObject platform42;
  platform42.getSprite()->setTexture(platform_a_texture);
  platform42.getSprite()->setPosition(200, -2950);
  platform42.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform42);

  GameObject platform43;
  platform43.getSprite()->setTexture(platform_b_texture);
  platform43.getSprite()->setPosition(400, -3050);
  platform43.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform43);

  GameObject platform44;
  platform44.getSprite()->setTexture(platform_a_texture);
  platform44.getSprite()->setPosition(600, -3180);
  platform44.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform44);

  GameObject platform45;
  platform45.getSprite()->setTexture(platform_b_texture);
  platform45.getSprite()->setPosition(700, -3270);
  platform45.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform45);

  GameObject platform46;
  platform46.getSprite()->setTexture(platform_a_texture);
  platform46.getSprite()->setPosition(500, -3340);
  platform46.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform46);

  GameObject platform47;
  platform47.getSprite()->setTexture(platform_b_texture);
  platform47.getSprite()->setPosition(300, -3460);
  platform47.getSprite()->setScale(0.5f, 0.5f);
  platforms.push_back(platform47);

  GameObject platform48;
  platform48.getSprite()->setTexture(platform_a_texture);
  platform48.getSprite()->setPosition(100, -3560);
  platform48.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform48);

  GameObject platform49;
  platform49.getSprite()->setTexture(platform_b_texture);
  platform49.getSprite()->setPosition(330, -3660);
  platform49.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform49);

  GameObject platform50;
  platform50.getSprite()->setTexture(platform_a_texture);
  platform50.getSprite()->setPosition(520, -3770);
  platform50.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform50);

  GameObject platform51;
  platform51.getSprite()->setTexture(platform_b_texture);
  platform51.getSprite()->setPosition(720, -3870);
  platform51.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform51);

  GameObject platform52;
  platform52.getSprite()->setTexture(platform_a_texture);
  platform52.getSprite()->setPosition(500, -3970);
  platform52.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform52);

  GameObject platform53;
  platform53.getSprite()->setTexture(platform_b_texture);
  platform53.getSprite()->setPosition(280, -4070);
  platform53.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform53);

  GameObject platform54;
  platform54.getSprite()->setTexture(platform_a_texture);
  platform54.getSprite()->setPosition(140, -4170);
  platform54.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform54);

  GameObject platform55;
  platform55.getSprite()->setTexture(platform_b_texture);
  platform55.getSprite()->setPosition(370, -4270);
  platform55.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform55);

  // first platform player lands on 
  GameObject platform56;
  platform56.getSprite()->setTexture(platform_b_texture);
  platform56.getSprite()->setPosition(10, 400);
  platform56.getSprite()->setScale(0.4f, 0.4f);
  platforms.push_back(platform56);
}

void Game::initialiseOrbs()
{
  orb_texture.loadFromFile("../Data/Images/Yellow_paint_large/"
                           "paint_circle_purple.png");

  GameObject orb1;
  orb1.getSprite()->setTexture(orb_texture);
  orb1.getSprite()->setPosition(960, -460);
  orb1.getSprite()->setScale(0.12f, 0.12f);  
  orbs.push_back(orb1);

  GameObject orb2;
  orb2.getSprite()->setTexture(orb_texture);
  orb2.getSprite()->setPosition(750, -1520);
  orb2.getSprite()->setScale(0.12f, 0.12f);  
  orbs.push_back(orb2);

  GameObject orb3;
  orb3.getSprite()->setTexture(orb_texture);
  orb3.getSprite()->setPosition(150, -1740);
  orb3.getSprite()->setScale(0.12f, 0.12f);  
  orbs.push_back(orb3);

  GameObject orb4;
  orb4.getSprite()->setTexture(orb_texture);
  orb4.getSprite()->setPosition(25, -2560);
  orb4.getSprite()->setScale(0.12f, 0.12f);  
  orbs.push_back(orb4);

  GameObject orb5;
  orb5.getSprite()->setTexture(orb_texture);
  orb5.getSprite()->setPosition(900, -160);
  orb5.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb5);

  GameObject orb6;
  orb6.getSprite()->setTexture(orb_texture);
  orb6.getSprite()->setPosition(145, -370);
  orb6.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb6);

  GameObject orb7;
  orb7.getSprite()->setTexture(orb_texture);
  orb7.getSprite()->setPosition(460, 430);
  orb7.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb7);

  GameObject orb8;
  orb8.getSprite()->setTexture(orb_texture);
  orb8.getSprite()->setPosition(610, -2260);
  orb8.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb8);

  GameObject orb9;
  orb9.getSprite()->setTexture(orb_texture);
  orb9.getSprite()->setPosition(770, -1970);
  orb9.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb9);

  //first orb before last ladder
  GameObject orb10;
  orb10.getSprite()->setTexture(orb_texture);
  orb10.getSprite()->setPosition(335, -3520); 
  orb10.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb10);

  GameObject orb11;
  orb11.getSprite()->setTexture(orb_texture);
  orb11.getSprite()->setPosition(180, -3615); 
  orb11.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb11);

  GameObject orb12;
  orb12.getSprite()->setTexture(orb_texture);
  orb12.getSprite()->setPosition(350, -3720); 
  orb12.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb12);

  GameObject orb13;
  orb13.getSprite()->setTexture(orb_texture);
  orb13.getSprite()->setPosition(530, -3830); 
  orb13.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb13);

  GameObject orb14;
  orb14.getSprite()->setTexture(orb_texture);
  orb14.getSprite()->setPosition(880, -3930); 
  orb14.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb14);

  GameObject orb15;
  orb15.getSprite()->setTexture(orb_texture);
  orb15.getSprite()->setPosition(570, -4030); 
  orb15.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb15);

  GameObject orb16;
  orb16.getSprite()->setTexture(orb_texture);
  orb16.getSprite()->setPosition(370, -4130); 
  orb16.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb16);

  //floating orb (last orb to get 20/20)
  GameObject orb17;
  orb17.getSprite()->setTexture(orb_texture);
  orb17.getSprite()->setPosition(750, -4250);
  orb17.getSprite()->setScale(0.17f, 0.17f);
  orbs.push_back(orb17);

  //highest orb
  GameObject orb18;
  orb18.getSprite()->setTexture(orb_texture);
  orb18.getSprite()->setPosition(500, -4330);
  orb18.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb18);

  GameObject orb19;
  orb19.getSprite()->setTexture(orb_texture);
  orb19.getSprite()->setPosition(600, -1050);
  orb19.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb19);

  GameObject orb20;
  orb20.getSprite()->setTexture(orb_texture);
  orb20.getSprite()->setPosition(170, -2560);
  orb20.getSprite()->setScale(0.12f, 0.12f);
  orbs.push_back(orb20);
  
}


// - - - - - - - - - - - - - Game Logic - - - - - - - - - - - - -


void Game::movePlayer(float dt)
{
  // player speed and movement logic
  float speed = 200.f;
  player.move(player_direction.x * speed * dt, player_direction.y * speed * dt);

}

void Game::applyGravity(float dt)
{
  // gravity logic + player velocity

  player_velocity.y += gravity * dt;
  player.move(player_velocity.x * dt, player_velocity.y * dt);

}

void Game::checkPlatformCollisions()
{
  for (auto& platform : platforms)
  {

    if (checkCollision(player, platform))
    {
      // sets back to 0 when hitting platform - slides through platform slowly
      // (happy accident, works well with the logic of the game)
      
      player_velocity.y = 0;
      

      if (can_jump)
      {
       
          can_jump = false;
          
      }
    }
  }
}

void Game::checkWallCollisions()
{
  sf::Vector2f playerPos = player.getSprite()->getPosition();
  float playerWidth      = player.getSprite()->getGlobalBounds().width;

  if (playerPos.x < 0)
  {

    player.setPosition(0, playerPos.y);

  }

  // Clamp to right edge
  else if (playerPos.x + playerWidth > window.getSize().x)
  {

    player.setPosition(window.getSize().x - playerWidth, playerPos.y);

  }

  // if player sprite goes below bottom of screen
  float viewBottom = view1.getCenter().y + (window.getSize().y / 2.0f);
  float playerTop  = player.getSprite()->getPosition().y;

  if (playerTop > viewBottom)
  {

    death_sound.play();
    death_sound.setVolume(50);
    is_running = false;
    is_dead    = true;
    
  }

}

void Game::checkPlayerEnemyCollision()
{
  // Only take damage if cooldown has passed
  if (damage_timer.getElapsedTime().asSeconds() >= damage_cooldown)
  {
    for (auto& enemy : enemies)
    {
      sf::FloatRect playerBounds = player.getSprite()->getGlobalBounds();
      sf::FloatRect enemyBounds  = enemy.getSprite()->getGlobalBounds();

      enemyBounds.left += 10;
      enemyBounds.top += 10;
      enemyBounds.width -= 20;
      enemyBounds.height -= 40;
            
      
      bool noCollision =
        (playerBounds.left + playerBounds.width < enemyBounds.left) ||
        (enemyBounds.left + enemyBounds.width < playerBounds.left) ||
        (playerBounds.top + playerBounds.height < enemyBounds.top) ||
        (enemyBounds.top + enemyBounds.height < playerBounds.top);

      if (!noCollision)
      {

        hurt_sound.play();
        player_lives--;
        damage_timer.restart();
        player.getSprite()->setColor(sf::Color(255, 176, 156, 255));
                

        if (player_lives <= 0)
        {

          is_running = false;
          is_dead    = true;
          death_sound.play();

        }

        break;
      }
    }
  }
}

void Game::updateEnemies(float dt)
{

  for (auto& enemy : enemies)
  {

    enemy.update(dt);

  }
}

bool Game::checkCollision(const GameObject& obj1, const GameObject& obj2)
{
  // Get the bounding boxes of both objects
  sf::FloatRect bounds1 = obj1.getSprite()->getGlobalBounds();
  sf::FloatRect bounds2 = obj2.getSprite()->getGlobalBounds();

  // shortened the platform bounding box height and width - this makes the player slip through the platform quicker
  bounds2.height -= 130;
  bounds2.top += 10;
  bounds2.width -= 25;
  bounds2.left += 10;

  bool noCollision = (bounds1.left + bounds1.width < bounds2.left) ||
                     (bounds2.left + bounds2.width < bounds1.left) ||
                     (bounds1.top + bounds1.height < bounds2.top) ||
                     (bounds2.top + bounds2.height < bounds1.top);

  return !noCollision;
}

void Game::checkPlayerOrbCollision()
{
    for (auto& Orb : orbs)
    {
      sf::FloatRect playerBounds = player.getSprite()->getGlobalBounds();
      sf::FloatRect orbBounds  = Orb.getSprite()->getGlobalBounds();

      bool noCollision =
        (playerBounds.left + playerBounds.width < orbBounds.left) ||
        (orbBounds.left + orbBounds.width < playerBounds.left) ||
        (playerBounds.top + playerBounds.height < orbBounds.top) ||
        (orbBounds.top + orbBounds.height < playerBounds.top);

      if (!noCollision && Orb.getSprite()->getPosition().x != -100)
      {
        bubble_pop.play();
        /*player_scale += 0.1f;*/
        /*player.getSprite()->setScale(player_scale, player_scale);*/
        Orb.getSprite()->setPosition(-100, 100);
        orbs_collected ++;

        if (orbs_collected >= total_orbs)
        {

          has_won = true;
          is_running = false;
          crowd_cheer_sound.play();

        }
        
        
        break;
      }

    }
}



// - - - - - - - - - - - - - Rendering - - - - - - - - - - - - - - -


void Game::renderMenu()
{
  
  window.draw(menu_text);
  window.draw(play_text);
  window.draw(quit_text);
  window.draw(collect_orb_menu_text);
  window.draw(menu_orb);
  window.draw(A_key);
  window.draw(D_key);
  window.draw(spacebar);    
  uiTextures(); //not sure why this works but it does so im keeping it
  
}

void Game::renderWorld()
{
  
    //dark purple (48, 25, 52,  255)
  window.clear(sf::Color(8, 8, 8,  255));
  window.setView(window.getDefaultView());

  window.draw(background_a);
  window.draw(background_b);
  window.draw(background_c);

  window.setView(view1);
  window.draw(*player.getSprite());

  // draw platforms
  for (auto& platform : platforms)
  {

    window.draw(*platform.getSprite());

  }

  // draw enemies
  for (auto& enemy : enemies)
  {

    window.draw(*enemy.getSprite());

  }

  for (auto& Orb : orbs)
  {
    
    window.draw(*Orb.getSprite());
    
  }

  playerLives();
  scoreText();
  
}

void Game::playerLives()
{
  if (!heart_texture.loadFromFile("../Data/Images/Heart.png"))
  {

    std::cout << "Texture did not load";

  }

  for (int i = 0; i < player_lives; ++i)
  {

    heart.setTexture(heart_texture);
    heart.setScale(1.0f, 1.0f);
    heart.setPosition(10 + i * 40, 10);
    window.setView(window.getDefaultView());
    window.draw(heart);

  }
}



// - - - - - - - - - - - - - Menu / Game UI - - - - - - - - - - - - -


void Game::menuTexts()
{

  // menu font file
  if (!menu_font.loadFromFile("../Data/Fonts/DRIPINK.otf"))
  {
    std::cout << "Font did not load";
  }

  // play font file
  if (!play_font.loadFromFile("../Data/Fonts/AlteHaasGroteskBold.ttf"))
  {
    std::cout << "Font did not load";
  }

  orb_texture.loadFromFile("../Data/Images/Yellow_paint_large/"
                           "paint_circle_purple.png");

  // menu title text
  menu_text.setFont(menu_font);
  menu_text.setString("EYEDROP");
  menu_text.setCharacterSize(200);
  menu_text.setLetterSpacing(3 );
  menu_text.setFillColor(sf::Color::Black);
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 20);

  // play text in menu
  play_text.setFont(play_font);
  play_text.setString(" [PLAY]");
  play_text.setCharacterSize(30);
  play_text.setLetterSpacing(3);
  play_text.setFillColor(sf::Color::Black);
  play_text.setPosition(
    window.getSize().x / 2 - play_text.getGlobalBounds().width / 2, 300);

  // quit text in menu
  quit_text.setFont(play_font);
  quit_text.setString(" QUIT");
  quit_text.setCharacterSize(30);
  quit_text.setLetterSpacing(3);
  quit_text.setFillColor(sf::Color::Black);
  quit_text.setPosition(
    window.getSize().x / 2 - quit_text.getGlobalBounds().width / 2, 370);

  collect_orb_menu_text.setFont(play_font);
  collect_orb_menu_text.setString("COLLECT 20     TO WIN");
  collect_orb_menu_text.setCharacterSize(20);
  collect_orb_menu_text.setLetterSpacing(4);
  collect_orb_menu_text.setFillColor(sf::Color::Black);
  collect_orb_menu_text.setPosition(374, 470);

  menu_orb.setTexture(orb_texture);
  menu_orb.setScale(0.10f, 0.10f);
  menu_orb.setPosition(570, 466);
  /*menu_orb.setColor(sf::Color::Black);*/

  
}

void Game::toggleMenuSelection()
{

  play_selected = !play_selected;

  if (play_selected)
  {

    play_text.setString(" [PLAY]");
    quit_text.setString(" QUIT");

  }

  else
  {

    play_text.setString("  PLAY");
    quit_text.setString("[QUIT]");

  }

}

void Game::handleMenuSelection()
{

  if (play_selected)
  {

    in_menu    = false;
    is_running = true;

    // reset positions after menu
    view1.setCenter(540, 360);
    player.setPosition(50, 0);
    player_velocity = { 0.f, 0.f };

  }
  else
  {

    window.close();

  }

}

void Game::restartGame()
{

  is_dead      = false;
  is_running   = true;
  has_won      = false;
  player_lives = 3;
  orbs_collected = 0;
  total_orbs     = 20;

  player.getSprite()->setScale(0.2f,0.2f);  
  player.getSprite()->setPosition(50, 0);

  view1.setSize(window.getDefaultView().getSize());
  view1.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

  player_velocity = { 0.f, 0.f };

  // reset the level
  platforms.clear();
  enemies.clear();
  orbs.clear();
  
  
  initialisePlatforms();
  initialiseEnemies();
  initialiseOrbs();
  background_music.stop();
  background_music.play();

}

void Game::scoreText()
{

  if (!score_font.loadFromFile("../Data/Fonts/horror.ttf"))
  {
    std::cout << "Font did not load";
  }

  score_text.setFont(score_font);
  score_text.setCharacterSize(40);
  score_text.setFillColor(sf::Color(142, 15, 223, 255));
  score_text.setPosition(955.f, 18.f);
  score_text.setString("" + std::to_string(orbs_collected) + " / " + std::to_string(total_orbs));
  window.draw(score_text);

}

void Game::winText()
{

  window.setView(window.getDefaultView());
  window.clear(sf::Color::Black);

  sf::Text win_text;
  win_text.setFont(menu_font);
  win_text.setCharacterSize(120);
  win_text.setLetterSpacing(3);
  win_text.setString("YOU WIN");
  win_text.setFillColor(sf::Color::Green);
  win_text.setPosition(
    window.getSize().x / 2 - win_text.getGlobalBounds().width / 2, 180);

  sf::Text play_again_text;
  play_again_text.setFont(play_font);
  play_again_text.setCharacterSize(35);
  play_again_text.setLetterSpacing(3);
  play_again_text.setString("press enter to play again");
  play_again_text.setFillColor(sf::Color::Green);
  play_again_text.setPosition(
    window.getSize().x / 2 - play_again_text.getGlobalBounds().width / 2, 350);

  

  

  window.draw(win_text);
  window.draw(play_again_text);
  background_music.stop();

  
}

void Game::deadText()
{

  window.setView(window.getDefaultView());
  window.clear(sf::Color::Black);

  sf::Text dead_text;
  dead_text.setFont(menu_font);
  dead_text.setCharacterSize(120);
  dead_text.setLetterSpacing(3);
  dead_text.setString("DEAD");
  dead_text.setFillColor(sf::Color::Red);
  dead_text.setPosition(
    window.getSize().x / 2 - dead_text.getGlobalBounds().width / 2, 180);

  sf::Text play_again_text;
  play_again_text.setFont(play_font);
  play_again_text.setCharacterSize(35);
  play_again_text.setLetterSpacing(3);
  play_again_text.setString("press enter to play again");
  play_again_text.setFillColor(sf::Color::Red);
  play_again_text.setPosition(
    window.getSize().x / 2 - play_again_text.getGlobalBounds().width / 2, 350);

  window.draw(dead_text);
  window.draw(play_again_text);
  background_music.stop();

}

void Game::uiTextures()
{

  if (!ui_A_key_texture.loadFromFile("../Data/Images/icons8-a-key-50.png"))
  {
    std::cout << "image did not load";
  }

  if (!ui_D_key_texture.loadFromFile("../Data/Images/icons8-d-key-50.png"))
  {
    std::cout << "image did not load";
  }

  if (!ui_spacebar_texture.loadFromFile("../Data/Images/"
                                        "icons8-space-key-50-new.png"))
  {
    std::cout << "image did not load";
  }

  A_key.setTexture(ui_A_key_texture);
  A_key.setPosition(410, 570);
  A_key.setScale(1, 1);

  ui_move_text.setString("MOVE");
  ui_move_text.setFont(play_font);
  ui_move_text.setCharacterSize(18);
  ui_move_text.setLetterSpacing(5);
  ui_move_text.setColor(sf::Color::Black);
  ui_move_text.setPosition(420, 625);
  window.draw(ui_move_text);

  D_key.setTexture(ui_D_key_texture);
  D_key.setPosition(460, 570);
  D_key.setScale(1, 1);

  spacebar.setTexture(ui_spacebar_texture);
  spacebar.setPosition(592, 535);
  spacebar.setScale(1.2, 1.2);

  ui_jump_text.setString("JUMP");
  ui_jump_text.setFont(play_font);
  ui_jump_text.setCharacterSize(18);
  ui_jump_text.setLetterSpacing(5);
  ui_jump_text.setColor(sf::Color::Black);
  ui_jump_text.setPosition(602, 625);
  window.draw(ui_jump_text);

}


// - - - - - - - - - - - - - Player Input - - - - - - - - - - - - - -


void Game::handleMoveLeft()
{

  player_direction.x = -1;

  // sets random eye texture when keys are pressed
  if (eye_timer.getElapsedTime().asSeconds() > eye_cooldown)
  {

    int randomIndex = rand() % eye_textures.size();
    player.getSprite()->setTexture(*eye_textures[randomIndex]);
    eye_timer.restart();

  }

}

void Game::handleMoveRight()
{

  player_direction.x = 1;

  if (eye_timer.getElapsedTime().asSeconds() > eye_cooldown)
  {

    int randomIndex = rand() % eye_textures.size();
    player.getSprite()->setTexture(*eye_textures[randomIndex]);
    eye_timer.restart();

  }

}

void Game::handleJump()
{

  // changes eye texture each time space bar is pressed
  int randomIndex = rand() % eye_textures.size();
  player.getSprite()->setTexture(*eye_textures[randomIndex]);

  if (!can_jump)
  {

    jump_sound.play();
    player_velocity.y = jump_strength;
    can_jump          = true;

  }

}

void Game::stopPlayerHorizontalMovement()
{

  player_direction.x = 0;

}

void Game::handlePlayerInput()
{

  sf::Vector2f playerPos = player.getSprite()->getPosition();
  float playerWidth      = player.getSprite()->getGlobalBounds().width;

  // collision detection with walls (left and right)
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    if (playerPos.x > 0)
    {
      player_direction.x = -1;
    }
    else
    {
      player_direction.x = 0;
    }
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    if (
      playerPos.x + player.getSprite()->getGlobalBounds().width <
      window.getSize().x)
    {
      player_direction.x = 1;
    }
    else
    {
      player_direction.x = 0;
    }
  }
  else
  {
    player_direction.x = 0;
  }

}

void Game::resetPlayerColour()
{
  if (damage_timer.getElapsedTime().asSeconds() >= damage_cooldown)
  {

    player.getSprite()->setColor(sf::Color::White);

  }
}



// - - - - - - - - - - - - - Audio / Graphics - - - - - - - - - - - - -


void Game::eyeTextures()
{
  // player texture + scale
  
  player.initialiseSprite(
    player_texture, "../Data/Images/Googly_Eyes/googly-d.png");
   player.getSprite()->setScale(.2, .2);

  

  // eye textures
  eye_texture_1.loadFromFile("../Data/Images/Googly_Eyes/googly-a.png");
  eye_texture_2.loadFromFile("../Data/Images/Googly_Eyes/googly-b.png");
  eye_texture_3.loadFromFile("../Data/Images/Googly_Eyes/googly-c.png");
  eye_texture_4.loadFromFile("../Data/Images/Googly_Eyes/googly-d.png");
  eye_texture_5.loadFromFile("../Data/Images/Googly_Eyes/googly-e.png");

  // storing textures in a vector to randomly access them
  eye_textures = { &eye_texture_1,
                   &eye_texture_2,
                   &eye_texture_3,
                   &eye_texture_4,
                   &eye_texture_5 };
}

void Game::backgroundTextures()
{
  // background texture 1
  if (!background_texture_a.loadFromFile("../Data/Images/Yellow_paint_large/"
                                         "paint_splat_c_double.png"))
  {
    std::cout << "Texture did not load";
  }

  // background texture 2
  if (!background_texture_b.loadFromFile("../Data/Images/Yellow_paint_large/"
                                         "paint_splat_a_double.png"))
  {
    std::cout << "Texture did not load";
  }

  // background texture 3
  if (!background_texture_c.loadFromFile("../Data/Images/Yellow_paint_large/"
                                         "paint_splat_b_double.png"))
  {
    std::cout << "Texture did not load";
  }

  background_a.setTexture(background_texture_a);
  background_a.setPosition(100, 100);
  background_a.setColor(sf::Color(255, 255, 255, 60));  
  background_a.setScale(1, 1);

  background_b.setTexture(background_texture_b);
  background_b.setPosition(600, 50);
  background_b.setColor(sf::Color(255, 255, 255, 50));
  background_b.setScale(1.7, 1.7);

  background_c.setTexture(background_texture_c);
  background_c.setPosition(300, 500);
  background_c.setColor(sf::Color(255, 255, 255, 50));
  background_c.setScale(1.5, 1.5);
}

void Game::soundEffects()
{

  if (!jump_sound_buffer.loadFromFile("../Data/Sound/man-jump-noise.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!bubble_pop_buffer.loadFromFile("../Data/Sound/bubble-pop.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!death_sound_buffer.loadFromFile("../Data/Sound/die.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!hurt_sound_buffer.loadFromFile("../Data/Sound/hurt_sound.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!crowd_cheer_sound_buffer.loadFromFile("../Data/Sound/yay.wav"))
  {
    std::cout << "Sound did not load";
  }   

  if (!menu_play_sound_buffer.loadFromFile("../Data/Sound/play_sound_3.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!menu_music_sound_buffer.loadFromFile("../Data/Sound/menu_music_3.wav"))
  {
    std::cout << "Sound did not load";
  }

  if (!background_sound_buffer.loadFromFile("../Data/Sound/background_music.wav"))    
  {
    std::cout << "Sound did not load";
  }
  
  crowd_cheer_sound.setBuffer(crowd_cheer_sound_buffer);
  hurt_sound.setBuffer(hurt_sound_buffer);
  death_sound.setBuffer(death_sound_buffer);
  bubble_pop.setBuffer(bubble_pop_buffer);
  jump_sound.setBuffer(jump_sound_buffer);


}

void Game::menuMusic()
{
  
                     
  menu_music.setBuffer(menu_music_sound_buffer);
  menu_music.play();
  menu_music.setLoop(true);
  menu_music.setVolume(50); 

}

void Game::backgroundMusic()
{

 
  menu_music.stop();
  background_music.setBuffer(background_sound_buffer);
  background_music.play();
  background_music.setVolume(60);

}

void Game::menuPlaySound() 
{

  menu_play_sound.setBuffer(menu_play_sound_buffer);
  menu_play_sound.play();

}


// - - - - - - - - - - - - - Screen Movement - - - - - - - - - - - - -


void Game::moveScreen()
{

  // screen movement
  view1.setCenter(window.getSize().x / 2, window.getSize().y / 2);
  view1.setSize(window.getSize().x, window.getSize().y);  
  
}

void Game::screenSpeed(float dt)
{

  // lower number = faster
  view1.move(0, -42.5f * dt); 
  

}



































