// header i/f
#include "color.hpp"

// header, system
#include <iostream>

Color::Color() {
  data_[0] = 0;
  data_[1] = 0;
  data_[2] = 0;
}

Color::Color(float r, float g, float b) {
  data_[0] = r;
  data_[1] = g;
  data_[2] = b;
}

Color::Color(Color const& rhs){
  data_[0] = rhs.data_[0];
  data_[1] = rhs.data_[1];
  data_[2] = rhs.data_[2];
}

Color::~Color()
{}

// --------------- //
// --- methods --- //
// --------------- //

void Color::print(std::ostream& os) const {
  os << '(' << data_[0] << '|' << data_[1] << '|' << data_[2] << ')' << std::endl;
}

Color::value_t& Color::operator[](unsigned c) {
  return data_[c];
}

const Color::value_t& Color::operator[](unsigned c) const {
  return data_[c];
}

void Color::operator+=(Color const& a) {
  data_[0]+=a.data_[0];
  data_[1]+=a.data_[1];
  data_[2]+=a.data_[2];
}

void Color::operator=(Color const& rhs) {
  data_[0] = rhs.data_[0];
  data_[1] = rhs.data_[1];
  data_[2] = rhs.data_[2];
}

bool Color::operator==(Color const& rhs) {
  return (data_[0] == rhs[0] && data_[1] == rhs[1] && data_[2] == rhs[2]);
}

Color& Color::operator*=(Color const& rhs) {
  data_[0] *= rhs.data_[0];
  data_[1] *= rhs.data_[1];
  data_[2] *= rhs.data_[2];
  return(*this);;
}

Color& Color::operator*=(float const rhs) {
  data_[0] *=rhs;
  data_[1] *=rhs;
  data_[2] *=rhs;
  return(*this);
}

// ------------ //
// --- free --- //
// ------------ //

Color operator+(Color const& a, Color const& b) {
  Color result(a);
  result += b;
  return result;
}

Color operator*(Color const& lhs, Color const& rhs) {
  return Color(lhs)*=rhs;
}

Color operator*(Color const& lhs, float const rhs) {
  return Color(lhs)*= rhs;
}

Color operator*(float const lhs, Color const& rhs) {
  return Color(rhs)*=lhs;
}

std::ostream& operator<<(std::ostream& os, Color const& Color){
  Color.print(os);
  return os;
}
