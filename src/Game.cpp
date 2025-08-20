#include <Game.hpp>
#include <cmath>
Game::Game() { init(); }
void Game::init()
{
  m_window.create(sf::VideoMode(1280, 720), "SFML_Game");
  m_window.setFramerateLimit(60);

  spawnPlayer();
}

void Game::sRender()
{
  m_window.clear();

  for (auto &b : m_boxes.getBoxes())
  {
    b->cShape->rect.setPosition(b->cTransform->pos.x, b->cTransform->pos.y);
    m_window.draw(b->cShape->rect);
  }
  m_window.display();
}

void Game::sUserInput()
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      m_running = false;
    else if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
      case sf::Keyboard::W:
        m_player->cInput->up = true;
        break;
      case sf::Keyboard::A:
        m_player->cInput->left = true;
        break;
      case sf::Keyboard::S:
        m_player->cInput->down = true;
        break;
      case sf::Keyboard::D:
        m_player->cInput->right = true;
        break;
      default:
        break;
      }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
      switch (event.key.code)
      {
      case sf::Keyboard::W:
        m_player->cInput->up = false;
        break;
      case sf::Keyboard::A:
        m_player->cInput->left = false;
        break;
      case sf::Keyboard::S:
        m_player->cInput->down = false;
        break;
      case sf::Keyboard::D:
        m_player->cInput->right = false;
        break;
      default:
        break;
      }
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        spawnWall(Vec2(static_cast<float>(event.mouseButton.x),
                       static_cast<float>(event.mouseButton.y)));
      }
    }
  }
}

void Game::sMovement()
{
  bool upBound =
      ((m_player->cTransform->pos.y - m_player->cBoundingBox->halfSize.y) > 0);
  bool downBound =
      ((m_player->cTransform->pos.y + m_player->cBoundingBox->halfSize.y) <
       m_window.getSize().y);
  bool leftBound =
      ((m_player->cTransform->pos.x - m_player->cBoundingBox->halfSize.x) > 0);
  bool rightBound =
      ((m_player->cTransform->pos.x + m_player->cBoundingBox->halfSize.x) <
       m_window.getSize().x);

  m_player->cTransform->vel = {0.0f, 0.0f};
  float playerSpeed = 5.0f;

  // Diagonal
  if (m_player->cInput->up && m_player->cInput->left && upBound && leftBound)
  {
    m_player->cTransform->vel =
        Vec2(playerSpeed * -cos(atan2(1, 1)), playerSpeed * -sin(atan2(1, 1)));
  }
  else if (m_player->cInput->up && m_player->cInput->right && upBound &&
           rightBound)
  {
    m_player->cTransform->vel =
        Vec2(playerSpeed * cos(atan2(1, 1)), playerSpeed * -sin(atan2(1, 1)));
  }
  else if (m_player->cInput->down && m_player->cInput->left && downBound &&
           leftBound)
  {
    m_player->cTransform->vel =
        Vec2(playerSpeed * -cos(atan2(1, 1)), playerSpeed * sin(atan2(1, 1)));
  }
  else if (m_player->cInput->down && m_player->cInput->right && downBound &&
           rightBound)
  {
    m_player->cTransform->vel =
        Vec2(playerSpeed * cos(atan2(1, 1)), playerSpeed * sin(atan2(1, 1)));
  }

  // Straight
  else if (m_player->cInput->up && upBound)
    m_player->cTransform->vel.y = -playerSpeed;
  else if (m_player->cInput->down && downBound)
    m_player->cTransform->vel.y = playerSpeed;
  else if (m_player->cInput->left && leftBound)
    m_player->cTransform->vel.x = -playerSpeed;
  else if (m_player->cInput->right && rightBound)
    m_player->cTransform->vel.x = playerSpeed;

  m_player->cTransform->prevPos = m_player->cTransform->pos;
  m_player->cTransform->pos += m_player->cTransform->vel;
}
void Game::sCollision()
{
  for (auto &w : m_boxes.getBoxes("Wall"))
  {
    float dx = std::abs(m_player->cTransform->pos.x - w->cTransform->pos.x);
    float dy = std::abs(m_player->cTransform->pos.y - w->cTransform->pos.y);
    float ox =
        m_player->cBoundingBox->halfSize.x + w->cBoundingBox->halfSize.x - dx;
    float oy =
        m_player->cBoundingBox->halfSize.y + w->cBoundingBox->halfSize.y - dy;
    Vec2 overLap = {ox, oy};

    if (overLap.x > 0 && overLap.y > 0)
    {
      // Previous overlap method
      float prevDX =
          std::abs(m_player->cTransform->prevPos.x - w->cTransform->pos.x);
      float prevDY =
          std::abs(m_player->cTransform->prevPos.y - w->cTransform->pos.y);
      float prevOX = m_player->cBoundingBox->halfSize.x +
                     w->cBoundingBox->halfSize.x - prevDX;
      float prevOY = m_player->cBoundingBox->halfSize.y +
                     w->cBoundingBox->halfSize.y - prevDY;
      Vec2 direction = {0.0f, 0.0f};
      direction.x =
          ((m_player->cTransform->pos.x > m_player->cTransform->prevPos.x)
               ? 1
               : -1);
      direction.y =
          ((m_player->cTransform->pos.y > m_player->cTransform->prevPos.y)
               ? 1
               : -1);
      if (prevOX > 0) // Collision from Y-axis
      {
        m_player->cTransform->prevPos = m_player->cTransform->pos;
        m_player->cTransform->pos.y += overLap.y * (-direction.y);
      }
      else if (prevOY > 0) // Collision from X-axis
      {
        m_player->cTransform->prevPos = m_player->cTransform->pos;
        m_player->cTransform->pos.x += overLap.x * (-direction.x);
      }
    }
  }
}

void Game::spawnPlayer()
{
  float wMidX = m_window.getSize().x / 2.0f;
  float wMidY = m_window.getSize().y / 2.0f;
  auto b = m_boxes.addBox("Player");

  b->cTransform = std::make_shared<CTransform>();
  b->cTransform->pos = {wMidX, wMidY};
  b->cTransform->prevPos = {wMidX, wMidY};

  b->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(100.0f, 100.0f));

  b->cShape = std::make_shared<CShape>(Vec2(100.0f, 100.0f), sf::Color::Green);
  b->cInput = std::make_shared<CInput>();

  m_player = b;
}

void Game::spawnWall(const Vec2 &mousePos)
{
  auto w = m_boxes.addBox("Wall");

  w->cTransform = std::make_shared<CTransform>();
  w->cTransform->pos = {mousePos.x, mousePos.y};
  w->cTransform->prevPos = {mousePos.x, mousePos.y};

  w->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(100.0f, 100.0f));

  w->cShape = std::make_shared<CShape>(Vec2(100.0f, 100.0f), sf::Color::Red);
}

void Game::run()
{
  while (m_running)
  {
    sUserInput();
    sMovement();
    sCollision();
    sRender();
  }
}
