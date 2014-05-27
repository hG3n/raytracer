#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <color.hpp>
#include <string>

struct Material
{
  Material();
  Material(std::string const&, Color const&, Color const&, Color const&, float);
  Material(Material const&);
  ~Material();

  std::string name;
  Color ka;
  Color kd;
  Color ks;
  float m;

  bool operator==(Material rhs);
  bool operator!=(Material rhs);
};

std::ostream& operator<<(std::ostream& output, Material const& material);

#endif
