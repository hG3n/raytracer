#include <cmath>

#include <cylinder.hpp>

#define epsilon 0.00000001f

cylinder::cylinder():
  shape("cylinder"),
  center_(),
  radius_(1.0),
  height_(1.0)
{}

cylinder::cylinder(math3d::point const& center, double radius, double height, std::string const& name, Material* material):
  shape(name, material),
  center_(center),
  radius_(radius),
  height_(height)
{}

cylinder::cylinder(cylinder const& cyl):
  shape(cyl.name_, cyl.material_),
  center_(cyl.center_),
  radius_(cyl.radius_),
  height_(cyl.height_)
{}

cylinder::~cylinder()
{}

// --------------- //
// --- methods --- //
// --------------- //

/*virtual*/ bool cylinder::intersect(ray const& r, double&, HitPoint&) const {
  return true;
}


/*virtual*/ void cylinder::print_on(std::ostream& out) const {
  shape::print_on(out);
  out << "\n Center: " << center_ << " Radius: " << radius_ << " Height: " << height_ << " Material: " << material_;
}

/*virtual*/ std::string const cylinder::type() const {
  return "cylinder";
}


/*virtual*/ void cylinder::get_details(std::ostream& out) const {
  out << center_[0] << " " << center_[1] << " " << center_[2] << " " << radius_ << " " << height_ << " ";
}




