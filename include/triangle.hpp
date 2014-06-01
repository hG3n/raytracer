#ifndef SHAPE_TRIANGLE_HPP
#define SHAPE_TRIANGLE_HPP

#include <string>

#include <point.hpp>
#include <shape.hpp>


class triangle: public shape{
    public:
        triangle();
        triangle(math3d::point const&, math3d::point const&, math3d::point const&, std::string const&, Material*);
        triangle(math3d::point const&, math3d::point const&, math3d::point const&);
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
        bool is_inside(math3d::point const&) const;

    private:
        math3d::point A_;
        math3d::point B_;
        math3d::point C_;
        std::string name_;

};

#endif
