#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <point.hpp>
#include <ray.hpp>

#include <string>
#include <iostream>

using namespace math3d;

class Camera
{
  public:

    Camera(std::string const& name = "camera", point const& pos = point(), double alpha = 45.0, point const& lookat = point(0.0,0.0,-1.0), vector const& up = vector(0.0,1.0,0.0));
    Camera(Camera const&);
    ~Camera();

    std::string const& name() const;
    point const& pos() const;
    double alpha() const;

    ray const compute_eye_ray(double, double, double, double);

  private:
    std::string name_;
    point pos_;
    double alpha_;
    point lookat_;
    vector up_;
};

std::ostream& operator<<(std::ostream&, Camera const&);

#endif
