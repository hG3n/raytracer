#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <matrix.hpp>
#include <string>
#include <iostream>

class Material;
class ray;
class HitPoint;

class shape{
  public:

  shape();
  shape(std::string const&, Material*);
  shape(Material*);
  shape(std::string const&);
  virtual ~shape();

  virtual bool intersect(ray const&, double&, HitPoint&) const = 0;
  virtual void print_on(std::ostream&) const;

  std::string   const& name() const;
  Material*      material() const;
  math3d::matrix const& inv_matrix() const;

  virtual std::string const type() const = 0;
  virtual void get_details(std::ostream&) const = 0;

  void translate(double, double, double);
  void scale(double, double, double);
  void rotate_x(double);
  void rotate_y(double);
  void rotate_z(double);

  protected:

  std::string    name_;
  Material*      material_;
  //Material       material_;
  math3d::matrix inv_matrix_;

};

std::ostream& operator<<(std::ostream&, shape const&);

#endif
