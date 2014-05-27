#include <cmath>
#include <sphere.hpp>
#include <matrix.hpp>
#include <hitpoint.hpp>
#include <sstream>

#define epsilon 0.000001f

using namespace math3d;

sphere::sphere():
    shape("sphere"),
    center_(point()),
    radius_(1.0)
{}

sphere::sphere(point const& center, double radius, std::string const& name, Material* material):
    shape(name, material),
    center_(center),
    radius_(radius)
{}

sphere::sphere(sphere const& sph):
    shape(sph.name_,sph.material_),
    center_(sph.center_),
    radius_(sph.radius_)
{}

sphere::~sphere()
{}

// --------------- //
// --- methods --- //
// --------------- //

/*virtual*/ bool sphere::intersect(ray const& r, double& t, HitPoint&) const {
  return false;
}

void sphere::print_on(std::ostream& output) const
{
    shape::print_on(output);
    output << "\n Center: " << center_ << " Radius: " << radius_;
}

std::string const sphere::type() const
{
    return "sphere";
}

void sphere::get_details(std::ostream& out) const
{
    out << center_[0] << " " << center_[1] << " " << center_[2] << " " << radius_ << " ";
}




