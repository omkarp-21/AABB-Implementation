#pragma once
#include <BoxManager.hpp>
#include <SFML/Graphics.hpp>
class Game
{
private:
  bool m_running = true;
  sf::RenderWindow m_window;
  BoxManager m_boxes;

  std::shared_ptr<Box> m_player;

  void init();

  // System Functions
  void sRender();
  void sCollision();
  void sMovement();
  void sUserInput();

  // Helper Functions
  void spawnPlayer();
  void spawnWall(const Vec2 &);

public:
  Game();
  void run();
};
