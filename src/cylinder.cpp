#include <cmath>

#include <cylinder.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>

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

/*virtual*/ bool cylinder::intersect(ray const& r, double& t, HitPoint& hp) const {

  double t0, t1;
  math3d::point phit;

  double a = r.dir[0] * r.dir[0] + r.dir[2] * r.dir[2];
  double b = 2.0 * (r.dir[0] * r.o[0] + r.dir[2] * r.o[2]);
  double c = r.o[0] * r.o[0] + r.o[2] * r.o[2] - radius_ * radius_;

  double disc = b * b - 4.0 * a * c;

  if(disc < 0.0)
    return(false);
  else {
    double e = std::sqrt(disc);
    double q;

    if(b < 0)
      q = -0.5 * (b - e);
    else
      q = -0.5 * (b + e);

    t0 = q / a;
    t1 = c / q;

    if(t0 > t1)
      std::swap(t0, t1);

    double ymin = center_[1];
    double ymax = center_[1] + height_;

    if(t1< epsilon)
      return false;

    double t = t0;
    if ( t0 < epsilon)
      t = t1;

    hp.pos = r.o + t * r.dir;

    // test clipping
    if(hp.pos[1] < ymin || hp.pos[1] > ymax) {

      if(std::fabs(t-t1) < epsilon)
          return false;

      t = t1;
      hp.pos = r.o + t * r.dir;
      if(hp.pos[1] < ymin || hp.pos[1] > ymax)
        return false;
      }

      hp.norm = normalize(r.o - center_ + t * r.dir) / radius_;
      hp.pos = r.o + t * r.dir;
      hp.material = *material_;
      hp.view = r.dir;
      hp.t = t;
  }
  return true; //loeschen wenn fertig!!
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




