#pragma once
#include <Component.hpp>
#include <memory>
#include <string>

class Box
{
private:
  std::string m_tag = "Default";

public:
  Box(const std::string &);
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CBoundingBox> cBoundingBox;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CInput> cInput;

  const std::string &tag() const;
};
