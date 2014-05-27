#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <cmath>

#include <thread>
#include <functional>

#include <vector.hpp>
#include <matrix.hpp>
#include <point.hpp>

#include "renderer.hpp"
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

int main(int argc, char* argv[])
{
  // set resolution and checkersize
  const std::size_t width = 800;
  const std::size_t height = 600;

  // create output window
  glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);

  // create a ray tracing Renderer
  Renderer app /* (scene) */ ;

  // start computation in thread
  std::thread thr(std::bind(&Renderer::render, &app));

  // start output on glutwindow
  glutwindow::instance().run();

  // wait on thread
  thr.join();

  example_math3d();

  return 0;
}
