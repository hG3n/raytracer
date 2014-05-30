#include <camera.hpp>
#include <matrix.hpp>
#include <cmath>

Camera::Camera(std::string const& name , math3d::point const& pos , double alpha, math3d::point const& lookat, math3d::vector const& up):
  name_(name),
  pos_(pos),
  alpha_(alpha),
  lookat_(lookat),
  up_(up)
{}

Camera::Camera(Camera const& cam):
  name_(cam.name_),
  pos_(cam.pos_),
  alpha_(cam.alpha_),
  lookat_(cam.lookat_),
  up_(cam.up_)
{}

Camera::~Camera()
{}

// --------------- //
// --- methods --- //
// --------------- //
std::string const& Camera::name() const {
  return name_;
}

math3d::point const& Camera::pos() const {
  return pos_;
}

double Camera::alpha() const {
  return alpha_;
}

ray const Camera::compute_eye_ray(double width, double height, double x, double y) {

  math3d::vector w = normalize(pos_ - lookat_);
  math3d::vector u = normalize(cross(up_,w));
  math3d::vector v = normalize(cross(w,u));

  double distance = (0.5 * width) / tan(0.5 * (alpha_ * M_PI / 180)); //distance of cam to view plane
  math3d::vector cam_dir = distance * w; //camera view direction

  math3d::point center_viewPlane = pos_ - cam_dir;
  math3d::point bottomLeft = center_viewPlane - 0.5 * height * v - 0.5 * width * u;
  math3d::point pp = bottomLeft + x * u + y * v; //math3d::point on view plane

  math3d::vector dir = pp - pos_; //compute ray dir

  ray r(pos_ , normalize(dir) );

  return r;
}

std::ostream& operator<<(std::ostream& out, Camera const& cam) {
    out << "Name: " << cam.name()
        << " Position: " << cam.pos()
        << " Oeffnungswinkel: " << cam.alpha();
    return out;
}
