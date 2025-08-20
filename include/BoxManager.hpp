#pragma once
#include <Box.hpp>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::shared_ptr<Box>> BoxVec;
typedef std::map<std::string, BoxVec> BoxMap;
class BoxManager
{
private:
  BoxVec m_boxes;
  BoxMap m_boxMap;

public:
  BoxManager() {}

  std::shared_ptr<Box> addBox(const std::string &tag);

  const BoxVec &getBoxes();
  const BoxVec &getBoxes(const std::string &tag);
};
