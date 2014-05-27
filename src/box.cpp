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
    min_(),
    max_(1,1,1)
{}

box::box(point const& min, point const& max, std::string const& name, Material* material):
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
  return true;
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

vector const box::get_normal(int const face_hit) const {

  switch(face_hit) {
    case 0: return(vector(-1, 0, 0));
    case 1: return(vector(0, -1, 0));
    case 2: return(vector(0, 0, -1));
    case 3: return(vector(1, 0, 0));
    case 4: return(vector(0, 1, 0));
    case 5: return(vector(0, 0, 1));
    default: return(vector());
  }
}

void ensure_min_max(point& min, point& max)
{
    if(min[0] > max[0])
        std::swap(min[0],max[0]);
    if(min[1] > max[1])
        std::swap(min[1],max[1]);
    if(min[2] > max[2])
        std::swap(min[2],max[2]);
}

