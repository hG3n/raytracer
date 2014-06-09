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
#include "sdf_loader.hpp"
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

class application {
  public:
    void run() {
      Renderer renderer;

      SDFloader sdf;
      sdf.read("scene.sdf");

      renderer.set_scene(sdf.scene());
      renderer.render();
    }

    void animate() {
      std::string file;
      std::ostringstream convert;

      Renderer renderer;
      SDFloader sdf;
      std::string transform;

    }

  private:
};


int main(int argc, char* argv[]) {

  SDFloader sdf;
  sdf.read("scene.sdf");

  // set resolution and checkersize
  const std::size_t width  = 800;
  const std::size_t height = 600;

  // create output window
  glutwindow::init(width, height, 100, 100, "Raytracer", argc, argv);

  // create a ray tracing Renderer
  Renderer app /* (scene) */;
  app.set_scene(sdf.scene());

  std::cout << app.scene() << std::endl;
  // start computation in thread
  std::thread thr(std::bind(&Renderer::render, &app));

  // start output on glutwindow
  glutwindow::instance().run();

  // wait on thread
  thr.join();

  //example_math3d();

  return 0;
}
