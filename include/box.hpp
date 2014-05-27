#ifndef SHAPE_BOX_HPP
#define SHAPE_BOX_HPP

#include <shape.hpp>
#include <point.hpp>

#include <iostream>

using namespace math3d;

class box: public shape{

  public:

  box();
  box(point const&, point const&, std::string const&, Material*);
  box(box const&);
  ~box();

  /*virtual*/ bool intersect(ray const&, double&, HitPoint&) const;
  /*virtual*/ void print_on(std::ostream&) const;

  /*virtual*/ std::string const type() const;
  /*virtual*/ void get_details(std::ostream&) const;

  private:

  vector const get_normal(int const) const;

  private:

  point min_;
  point max_;

};

void ensure_min_max(point&, point&);

#endif


