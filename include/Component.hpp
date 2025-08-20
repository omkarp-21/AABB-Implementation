#pragma once
#include <SFML/Graphics.hpp>
#include <Vec2.hpp>
class CTransform
{
public:
  Vec2 pos = {0.0f, 0.0f};
  Vec2 prevPos = {0.0f, 0.0f};
  Vec2 scale = {1.0f, 1.0f};
  Vec2 vel = {0.0f, 0.0f};
  float angle = 0;

  CTransform() {}
};

class CBoundingBox
{
public:
  Vec2 size;
  Vec2 halfSize;

  CBoundingBox() {}
  CBoundingBox(const Vec2 &s) : size(s), halfSize(Vec2(s.x / 2.0f, s.y / 2.0f))
  {
  }
};

class CShape
{
public:
  sf::RectangleShape rect;

  CShape(Vec2 size, const sf::Color &shape_color)
      : rect(sf::Vector2f(size.x, size.y))
  {
    rect.setFillColor(shape_color);
    rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
  }
};

class CInput
{
public:
  bool up = false;
  bool down = false;
  bool right = false;
  bool left = false;

  CInput() {}
};
