#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

// header, system
#include <point.hpp>
#include <vector.hpp>

using namespace math3d;

struct ray {
    ray():
        o(),
        dir()
    {}

    ray( point const& p , vector const& v):
        o(p),
        dir(v)
    {}

    ray(ray const& r):
        o(point(r.o)),
        dir(vector(r.dir))
    {}

    ~ray(){}
    point o;
    vector dir;
 // enums, typedefs
};

#endif // BUW_RAY_HPP
