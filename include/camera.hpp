#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <point.hpp>
#include <ray.hpp>

#include <string>
#include <iostream>

class Camera
{
  public:

    Camera(std::string const& name = "camera",
           math3d::point const& pos = math3d::point(),
           double alpha = 45.0,
           math3d::point const& lookat = math3d::point(0.0,0.0,-1.0),
           math3d::vector const& up = math3d::vector(0.0,1.0,0.0));
    Camera(Camera const&);
    ~Camera();

    std::string const& name() const;
    math3d::point const& pos() const;
    double alpha() const;

    ray const compute_eye_ray(double, double, double, double);

  private:
    std::string    name_;
    math3d::point  pos_;
    double         alpha_;
    math3d::point  lookat_;
    math3d::vector up_;
};

std::ostream& operator<<(std::ostream&, Camera const&);

#endif
