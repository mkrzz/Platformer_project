
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include "Platform.h"
#include "SFML/Audio.hpp"
#include "Enemy.h"


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  bool checkCollision(const GameObject& obj1, const GameObject& obj2);
  
 private:
  sf::RenderWindow& window;
  
  sf::Font menu_font;
  sf::Font play_font;
  sf::Font quit_font;
  sf::Font dead_font;
  sf::Font score_font;

  sf::Text menu_text;
  sf::Text play_text;
  sf::Text quit_text;
  sf::Text dead_text;
  sf::Text play_again_text;
  sf::Text player_lives_text;
  sf::Text score_text;
  sf::Text ui_move_text;
  sf::Text ui_jump_text;
  sf::Text win_text;
  sf::Text collect_orb_menu_text;

  sf::Texture platform_a_texture;
  sf::Texture platform_b_texture;
  sf::Texture platform_c_texture;

  sf::Texture ui_A_key_texture;
  sf::Texture ui_D_key_texture;
  sf::Texture ui_spacebar_texture;
  sf::Sprite A_key;
  sf::Sprite D_key;
  sf::Sprite spacebar;

  sf::Texture heart_texture;
  sf::Sprite heart;

  sf::Texture orb_texture;
  sf::Sprite orb;
  sf::Sprite menu_orb;

  sf::Texture enemy_texture_right_arrow;
  sf::Texture enemy_texture_up_arrow;

  sf::Texture background_texture_a;
  sf::Texture background_texture_b;
  sf::Texture background_texture_c;
  sf::Sprite background_a;
  sf::Sprite background_b;
  sf::Sprite background_c;

  sf::Texture player_texture;

  sf::Texture eye_texture_1;
  sf::Texture eye_texture_2;
  sf::Texture eye_texture_3;
  sf::Texture eye_texture_4;
  sf::Texture eye_texture_5;

  std::vector<sf::Texture*> eye_textures;
  std::vector<GameObject> platforms;
  std::vector<Enemy> enemies;
  std::vector<GameObject> orbs;
  

  sf::SoundBuffer jump_sound_buffer;
  sf::Sound jump_sound;
  sf::SoundBuffer bubble_pop_buffer;
  sf::Sound bubble_pop;
  sf::SoundBuffer death_sound_buffer;
  sf::Sound death_sound;
  sf::SoundBuffer hurt_sound_buffer;
  sf::Sound hurt_sound;
  sf::SoundBuffer crowd_cheer_sound_buffer;
  sf::Sound crowd_cheer_sound;
  sf::SoundBuffer background_sound_buffer;
  sf::Sound background_music;
  sf::SoundBuffer menu_play_sound_buffer;
  sf::Sound menu_play_sound;
  sf::SoundBuffer menu_music_sound_buffer;
  sf::Sound menu_music;
  
  sf::Clock damage_timer;
  float damage_cooldown = 1.0f;
  sf::Clock eye_timer;
  float eye_cooldown = 0.2f;
  /*sf::Clock slime_timer;
  float slime_cooldown = 1.0f;*/

  Vector2 player_direction = {0, 0};	
  Vector2 player_velocity   = {0, 0};
  
  
  float gravity            = 800.0f;
  float jump_strength      = -500.0f;
  
  int player_lives = 3;
  int score        = 0;
  float player_scale = 0.2f;
  

  int orbs_collected = 0;
  int total_orbs     = 20;
  
  //int jump_count     = 0;
  //float jump_cooldown = 0.0f;
  //float jump_cooldown_timer = 4.0f;
  bool can_jump             = false;

  bool in_menu = true;
  bool play_selected = true;
  bool game_over     = false;
  bool is_running = true;
  bool is_dead       = false;
  bool is_active     = true;
  bool ui_loaded     = false;
  bool has_won       = false;

  void initialisePlatforms();
  void menuTexts();
  void eyeTextures();
  void movePlayer(float dt);
  void handlePlayerInput();
  void applyGravity(float dt);
  void checkPlatformCollisions();
  void checkWallCollisions();
  void backgroundTextures();
  void soundEffects();
  void moveScreen();
  void initialiseEnemies();
  void initialiseOrbs();
  void deadText();
  void restartGame();
  void renderMenu();
  void renderWorld();
  void toggleMenuSelection();
  void handleMenuSelection();
  void handleMoveLeft();
  void handleMoveRight();
  void handleJump();
  void stopPlayerHorizontalMovement();
  void checkPlayerEnemyCollision();
  void playerLives();
  void screenSpeed(float dt);
  void updateEnemies(float dt);
  void scoreText();
  void checkPlayerOrbCollision();
  void uiTextures();
  void winText();
  void resetPlayerColour();
  void menuMusic();
  void backgroundMusic();
  void menuPlaySound();
  
  

  GameObject player;
  GameObject platform;
  GameObject enemy;
  GameObject Orbs;
  
  

  sf::View view1;

};

#endif // PLATFORMER_GAME_H
