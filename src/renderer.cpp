////#include <cmath>

#include <renderer.hpp>
#include <sdf_loader.hpp>
#include <camera.hpp>
#include <hitpoint.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <material.hpp>

Renderer::Renderer():
  scene_(),
  window_(glutwindow::instance()),
  image_(window_.width(), window_.height(), "./raytracer.ppm")
{}

Renderer::~Renderer()
{}

// --------------- //
// --- methods --- //
// --------------- //

Scene const& Renderer::scene() const {
  return scene_;
}

void Renderer::set_image(std::string const& file) {
  std::string name = "./" + file + ".ppm";
  image_ = ppmwriter(window_.width(), window_.height(), name);
}

void Renderer::render() {
  Camera camera = scene_.cameras.front();
  HitPoint hitpoint;
  for (std::size_t y = window_.height() - 1; y > 0; --y) {
    for (std::size_t x = 0; x < window_.width(); ++x) {
      Pixel p(x, y);

      //ray r = camera.compute_eye_ray(window_.width(), window_.height(), x , y);
      ray r = ray(math3d::point(float(x)/float(window_.width()),float(y)/float(window_.height()),0), math3d::vector(0,0,-1));

      hitpoint = trace_ray(r);

      if(hitpoint != HitPoint())
        p.color = Color(100,100,100);
      else
        p.color = Color(0,0,0);

      // write pixel to output window
      window_.write(p);
      // write pixel to image writer
      image_.write(p);
    }
  }
  // save final image
  image_.save();
}

HitPoint const Renderer::trace_ray(ray const& r) {

  ray     inv_ray;
  matrix  trans_inv_matrix_;
  matrix  matrix_;

  HitPoint closest;
  point    hp_pos;
  vector   normale;
  vector   view;
  Material material;

  double t_min = 5000000;
  double t = t_min;
  bool   hit = false;

  // compute color for pixel
#if 0 // nur zum debuggen
  scene_.shapes.clear();
  Material m;
  sphere s(point(0,0,0), 1.0,"horst", &m);
  scene_.shapes.push_back(&s);
#endif

  for(shape* i : scene_.shapes) {

    trans_inv_matrix_ = i->inv_matrix();
    trans_inv_matrix_.transpose();

    matrix_ = i->inv_matrix();
    matrix_.invert();

    inv_ray.o   = i->inv_matrix() * r.o;
    inv_ray.dir = i->inv_matrix() * r.dir;

    hit = i->intersect(inv_ray, t, closest);
    if (hit) {
      if(t < t_min) {
        t_min = t;
        hit = true;
        hp_pos = matrix_ * closest.pos;
        normale = normalize(trans_inv_matrix_ * closest.norm);
        view = closest.view;
        material = closest.material;

        closest.pos = hp_pos;
        closest.norm = normale;
        closest.view = view;
        closest.material = material;
        closest.t = t_min;
      }
    }
  }
  return closest;
}

