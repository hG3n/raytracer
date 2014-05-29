#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

// header, system
#include <point.hpp>
#include <vector.hpp>

struct ray {
    ray():
        o(),
        dir()
    {}

    ray( math3d::point const& p , math3d::vector const& v):
        o(p),
        dir(v)
    {}

    ray(ray const& r):
        o(math3d::point(r.o)),
        dir(math3d::vector(r.dir))
    {}

    ~ray(){}
    math3d::point o;
    math3d::vector dir;
 // enums, typedefs
};

#endif // BUW_RAY_HPP
