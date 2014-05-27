#ifndef SHAPE_SPHERE_HPP
#define SHAPE_SPHERE_HPP

#include <shape.hpp>
#include <point.hpp>
#include <ray.hpp>

using namespace math3d;

class sphere: public shape{
  public:

  sphere();
  sphere(point const&, double, std::string const&, Material*);
  sphere(sphere const&);
  ~sphere();

  /*virtual*/ bool intersect(ray const& ,double&, HitPoint& ) const;
  /*virtual*/ void print_on(std::ostream&) const;

  /*virtual*/ std::string const type() const;
  /*virtual*/ void get_details(std::ostream&) const;

  private:

  point center_;
  double radius_;
};

#endif
