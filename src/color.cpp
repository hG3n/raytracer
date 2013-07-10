// header i/f
#include "color.hpp"

// header, system
#include <iostream>

Color::Color()
{
  data_[0] = 0;
  data_[1] = 0;
  data_[2] = 0;
}

Color::Color(float r, float g, float b)
{
  data_[0] = r;
  data_[1] = g;
  data_[2] = b;
}

void
Color::print(std::ostream& os) const
{
  os << '(' << data_[0] << '|' << data_[1] << '|' << data_[2] << ')' << std::endl;
}

Color::value_t& 
Color::operator[](unsigned c)
{
  return data_[c];
}

const Color::value_t& 
Color::operator[](unsigned c) const 
{
  return data_[c];
}

void 
Color::operator+=(Color const& a) 
{ 
  data_[0]+=a.data_[0];
  data_[1]+=a.data_[1];
  data_[2]+=a.data_[2];
}

Color 
operator+(Color const& a, Color const& b) 
{
  Color result(a);
  result += b;
  return result;
}

std::ostream& 
operator<<(std::ostream& os, Color const& Color) 
{
  Color.print(os);
  return os;
}
