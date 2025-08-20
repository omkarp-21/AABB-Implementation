#include <Box.hpp>

Box::Box(const std::string &tag) : m_tag(tag) {}

const std::string &Box::tag() const { return m_tag; }
