#ifndef SHAPE_TRIANGLE_HPP
#define SHAPE_TRIANGLE_HPP

#include <string>

#include <point.hpp>
#include <shape.hpp>

using namespace math3d;

class triangle: public shape{
    public:
        triangle();
        triangle(point const&, point const&, point const&, std::string const&, Material*);
        triangle(point const&, point const&, point const&);
        triangle(triangle const&);
        ~triangle();

        /*virtual*/ bool intersect(ray const&, double&, HitPoint&) const;
        /*virtual*/ void print_on(std::ostream&) const;

        /*virtual*/ std::string const type() const;
        /*virtual*/ void get_details(std::ostream&) const;

    private:
        double AB() const;
        double AC() const;
        double BC() const;
        double area() const;
        //bool is_inside(point const&) const;

    private:
        point A_;
        point B_;
        point C_;
        std::string name_;

};

#endif
