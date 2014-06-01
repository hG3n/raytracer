#include <box.hpp>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <ray.hpp>
#include <hitpoint.hpp>

#define epsilon 0.00001

bool is_inbetween(double num, double min, double max) {
  return (num >= min && num <= max);
}

box::box():
  shape("box"),
  min_(math3d::point()),
  max_(1,1,1)
{}

box::box(math3d::point const& min, math3d::point const& max, std::string const& name, Material* material):
  shape(name, material),
  min_(min),
  max_(max)
{}

box::box(box const& b):
  shape(b.name_, b.material_),
  min_(b.min_),
  max_(b.max_)
{}

box::~box()
{}

// --------------- //
// --- methods --- //
// --------------- //

/*virtual*/ bool box::intersect(ray const& r, double& t, HitPoint& hp) const {
  math3d::point min(min_);
  math3d::point max(max_);
  ensure_min_max(min, max);

  double ox = r.o[0];
  double oy = r.o[1];
  double oz = r.o[2];

  double dx = r.dir[0];
  double dy = r.dir[1];
  double dz = r.dir[2];

  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  double a = 1.0 / dx;
  if (a >= 0) {
    tx_min = (min[0] - ox) * a;
    tx_max = (max[0] - ox) * a;
  }
  else {
    tx_min = (max[0] - ox) * a;
    tx_max = (min[0] - ox) * a;
  }

  double b = 1.0 / dy;
  if (b >= 0) {
    ty_min = (min[1] - oy) * b;
    ty_max = (max[1] - oy) * b;
  }
  else {
    ty_min = (max[1] - oy) * b;
    ty_max = (min[1] - oy) * b;
  }

  double c = 1.0 / dz;
  if (c >= 0) {
    tz_min = (min[2] - oz) * c;
    tz_max = (max[2] - oz) * c;
  }
  else {
    tz_min = (max[2] - oz) * c;
    tz_max = (min[2] - oz) * c;
  }

  double t0, t1;
  int face_in, face_out;

  // find largest entering t value
  if(tx_min > ty_min) {
    t0 = tx_min;
    face_in = (a >= 0.0) ? 0 : 3;
  }
  else {
    t0 = ty_min;
    face_in = (b >= 0.0) ? 1 : 4;
  }

  if(tz_min > t0) {
    t0 = tz_min;
    face_in = (c >= 0.0) ? 2 : 5;
  }

  // find smallest exiting t value
  if(tx_max < ty_max) {
    t1 = tx_max;
    face_out = (a >= 0.0) ? 3 : 0;
  }
  else {
    t1 = ty_max;
    face_out = (b >= 0.0) ? 4 : 1;
  }

  if(tz_max < t1) {
    t1 = tz_max;
    face_out = (c >= 0.0) ? 5 : 2;
  }

  if(t0 < t1 && t1 > epsilon) { // condition for a hit
    if(t0 > epsilon) {
      t = t0;  // ray hits outside surface
      hp.norm = get_normal(face_in);
    }
    else {
      t = t1; // ray hits inside surface
      hp.norm = get_normal(face_out);
    }

    hp.pos = r.o + t * r.dir;
    hp.view = r.dir;
    hp.material = *material_;
    hp.t = t;

    return true;
  }
  else 
    return false;
}

void box::print_on(std::ostream& output) const {
  shape::print_on(output);
  output << "\n Min: " << min_ << " Max: " << max_;
}

std::string const box::type() const {
  return "box";
}

void box::get_details(std::ostream& out) const {
  out << min_[0] << " " << min_[1] << " " << min_[2] << " " << max_[0] << " " << max_[1] << " " << max_[2] << " ";
}

math3d::vector const box::get_normal(int const face_hit) const {

  switch(face_hit) {
    case 0: return(math3d::vector(-1, 0, 0));
    case 1: return(math3d::vector(0, -1, 0));
    case 2: return(math3d::vector(0, 0, -1));
    case 3: return(math3d::vector(1, 0, 0));
    case 4: return(math3d::vector(0, 1, 0));
    case 5: return(math3d::vector(0, 0, 1));
    default: return(math3d::vector());
  }
}

void ensure_min_max(math3d::point& min, math3d::point& max)
{
  if(min[0] > max[0])
    std::swap(min[0],max[0]);
  if(min[1] > max[1])
    std::swap(min[1],max[1]);
  if(min[2] > max[2])
    std::swap(min[2],max[2]);
}

