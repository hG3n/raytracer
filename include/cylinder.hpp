#ifndef SHAPE_CYLINDER_HPP
#define SHAPE_CYLINDER_HPP

#include <shape.hpp>
#include <point.hpp>

class cylinder: public shape{
  public:
    cylinder();
    cylinder(math3d::point const&, double, double, std::string const&, Material*);
    cylinder(cylinder const&);
    ~cylinder();

    /*virtual*/ bool intersect(ray const&, double&, HitPoint&) const;
    /*virtual*/ void print_on(std::ostream&) const;

    /*virtual*/ std::string const type() const;
    /*virtual*/ void get_details(std::ostream&) const;

  private:
    math3d::point center_;
    double        radius_;
    double        height_;
};

#endif
