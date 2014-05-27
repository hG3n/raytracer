#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <point.hpp>
#include <vector.hpp>
#include <material.hpp>

using namespace math3d;

struct HitPoint {
  HitPoint():
    pos(),
    norm(),
    view(),
    material(),
    t()
  {}

  HitPoint(point const& p, vector const& n, vector const& v, Material const& m, double t_val):
    pos(p),
    norm(n),
    view(v),
    material(m),
    t(t_val)
  {}

  HitPoint(point const& p):
    pos(p),
    norm(),
    view(),
    material(),
    t()
  {}

  ~HitPoint(){}

  point     pos;
  vector    norm;
  vector    view;
  Material  material;
  double    t;

  bool operator==(HitPoint rhs) {
    return (pos == rhs.pos && norm == rhs.norm && view == rhs.view && material == rhs.material && t == rhs.t);
  }

  bool operator!=(HitPoint rhs) {
    return !(*this == rhs);
  }
};

#endif
