#include <BoxManager.hpp>

std::shared_ptr<Box> BoxManager::addBox(const std::string &tag)
{
  auto b = std::shared_ptr<Box>(new Box(tag));
  m_boxes.push_back(b);
  m_boxMap[b->tag()].push_back(b);
  return b;
}

const BoxVec &BoxManager::getBoxes() { return m_boxes; }

const BoxVec &BoxManager::getBoxes(const std::string &tag)
{
  return m_boxMap[tag];
}
