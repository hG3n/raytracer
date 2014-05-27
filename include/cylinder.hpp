#ifndef SHAPE_CYLINDER_HPP
#define SHAPE_CYLINDER_HPP

#include <shape.hpp>
#include <point.hpp>

using namespace math3d;

class cylinder: public shape{
    public:
        cylinder();
        cylinder(point const&, double, double, std::string const&, Material*);
        cylinder(cylinder const&);
        ~cylinder();

        /*virtual*/ bool intersect(ray const&, double&, HitPoint&) const;
        /*virtual*/ void print_on(std::ostream&) const;

        /*virtual*/ std::string const type() const;
        /*virtual*/ void get_details(std::ostream&) const;

    private:
        point center_;
        double radius_;
        double height_;
};

#endif
