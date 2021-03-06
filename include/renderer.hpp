#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <cmath>
#include <string>

#include <thread>

#include <vector.hpp>
#include <matrix.hpp>
#include <point.hpp>
#include <scene.hpp>
#include <ray.hpp>
#include <color.hpp>
#include <hitpoint.hpp>
#include <light.hpp>

#include <GL/glut.h>

class Renderer {

  public:
    Renderer();
    ~Renderer();

    Scene const& scene() const;

    void set_scene(Scene const&);
    void set_image(std::string const&);

    void render();

  private:
    HitPoint const trace_ray(ray const&);
    Color const shade(HitPoint const&) const;
    bool intersect_all(ray const&, double) const;

  private:
    Scene scene_;
    glutwindow& window_;
    ppmwriter image_;
    Color ambientlight_;
};

#endif
