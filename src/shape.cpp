#include <shape.hpp>
#include <material.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace math3d;

shape::shape():
  name_("default"),
  material_(nullptr),
  inv_matrix_(matrix::identity())
{}

shape::shape(std::string const& name, Material* material):
  name_(name),
  material_(material),
  inv_matrix_(matrix::identity())
{}

shape::shape(Material* material):
  name_("default"),
  material_(material),
  inv_matrix_(matrix::identity())
{}

shape::shape(std::string const& name):
    name_(name),
    material_(),
    inv_matrix_(matrix::identity())
{}

shape::~shape()
{}

// --------------- //
// --- methods --- //
// --------------- //

std::string const& shape::name() const {
  return name_;
}

Material* shape::material() const {
  return material_;
}

matrix const& shape::inv_matrix() const {
  return inv_matrix_;
}

void shape::print_on(std::ostream& out) const {
  out << "Name: " << name_ << "Material: " << *material_;
}

void shape::translate(double x, double y, double z) {
  matrix temp(make_translation(x, y, z));
  temp.invert();
  inv_matrix_ *= temp;
}

void shape::scale(double x, double y, double z) {
  matrix temp(make_scale(x, y, z));
  temp.invert();
  inv_matrix_ *= temp;
}

void shape::rotate_x(double angle) {
  double ang = angle * M_PI / 180;
  matrix temp(make_rotation_x(ang));
  temp.invert();
  inv_matrix_ *= temp;
}

void shape::rotate_y(double angle) {
  double ang = angle * M_PI / 180;
  matrix temp(make_rotation_y(ang));
  temp.invert();
  inv_matrix_ *= temp;
}

void shape::rotate_z(double angle) {
  double ang = angle * M_PI / 180;
  matrix temp(make_rotation_z(ang));
  temp.invert();
  inv_matrix_ *= temp;
}

// --- operators --- //
std::ostream& operator<<(std::ostream& output, shape const& s) {
  s.print_on(output);
  return output;
}








