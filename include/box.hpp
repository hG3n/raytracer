#ifndef SHAPE_BOX_HPP
#define SHAPE_BOX_HPP

#include <shape.hpp>
#include <point.hpp>

#include <iostream>

class box: public shape{

  public:

  box();
  box(math3d::point const&, math3d::point const&, std::string const&, Material*);
  box(box const&);
  ~box();

  /*virtual*/ bool intersect(ray const&, double&, HitPoint&) const;
  /*virtual*/ void print_on(std::ostream&) const;

  /*virtual*/ std::string const type() const;
  /*virtual*/ void get_details(std::ostream&) const;

  private:

  math3d::vector const get_normal(int const) const;

  private:

  math3d::point min_;
  math3d::point max_;

};

void ensure_min_max(math3d::point&, math3d::point&);

#endif


