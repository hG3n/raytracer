#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <string>

#include <point.hpp>
#include <color.hpp>


struct Light {

  Light(std::string const&, math3d::point const&, Color const&, Color const&);
  ~Light();

  std::string    name;
  math3d::point  pos;
  Color          la;
  Color          ld;
};

std::ostream& operator<<(std::ostream&, Light const&);

#endif
