#include <cmath>
#include <triangle.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>

#define epsilon 0.000001f

triangle::triangle():
  shape("triangle"),
  A_(),
  B_(),
  C_()
{}

triangle::triangle(math3d::point const& A, math3d::point const& B, math3d::point const& C, std::string const& name, Material* material):
  shape(name,material),
  A_(A),
  B_(B),
  C_(C)
{}

triangle::triangle(math3d::point const& A, math3d::point const& B, math3d::point const& C):
  shape("triangle"),
  A_(A),
  B_(B),
  C_(C)
{}

triangle::triangle(triangle const& tri):
  shape(tri.name_,tri.material_),
  A_(tri.A_),
  B_(tri.B_),
  C_(tri.C_)
{}

triangle::~triangle()
{}

// --------------- //
// --- methods --- //
// --------------- //

/*virtual*/ bool triangle::intersect(ray const& r, double& t, HitPoint& hp) const {

  hp.norm = -1*normalize(cross((B_ - A_), (C_ - A_))); //normal on triangle plain

  t = -1 * dot((r.o - A_),hp.norm) / dot(r.dir,hp.norm); //intersection of ray with triangle plain
  hp.pos = r.o + t * r.dir;

  if(is_inside(hp.pos)) { //see if hp is inside triangle
    hp.view = r.dir;
    hp.material = *material_;
    hp.t = t;
    return true;
  }
  else
    return false;
}

void triangle::print_on(std::ostream& out) const {
  shape::print_on(out);
  out << "\n A: " << A_ << " B: " << B_ << " C: " << C_;
}

std::string const triangle::type() const {
  return "triangle";
}

void triangle::get_details(std::ostream& out) const {
  out << A_[0] << " " << A_[1] << " " << A_[2] << " " << B_[0] << " " << B_[1] << " " << B_[2] << " " << C_[0] << " " << C_[1] << " " << C_[2] << " ";
}

double triangle::AB() const {
  return sqrt(pow((A_[0] - B_[0]) , 2)+ pow((A_[1] - B_[1]) , 2) + pow((A_[2] - B_[2]) , 2));
}

double triangle::AC() const {
  return sqrt(pow((A_[0] - C_[0]) , 2)+ pow((A_[1] - C_[1]) , 2) + pow((A_[2] - C_[2]) , 2));
}

double triangle::BC() const {
  return sqrt(pow((B_[0] - C_[0]) , 2)+ pow((B_[1] - C_[1]) , 2) + pow((B_[2] - C_[2]) , 2));
}

double triangle::area() const {
  return 0.25 * sqrt((AB()+AC()-BC()) * (AB()-AC()+BC()) * (AC()+BC()-AB()) * (AB()+BC()+AC()));
}

bool triangle::is_inside(math3d::point const& p) const {
  triangle tri_1 = triangle(A_, B_, p);
  triangle tri_2 = triangle(A_, C_, p);
  triangle tri_3 = triangle(C_, B_, p);

  double const area_sum = tri_1.area() + tri_2.area() + tri_3.area();

  return std::fabs(area_sum - area()) < epsilon;
}








