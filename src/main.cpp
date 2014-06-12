#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <thread>
#include <functional>

#include <vector.hpp>
#include <matrix.hpp>

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

      #pragma omp parallel for
 //     for(int i = 0; i < 80; ++i) {
      for(int i = 80; i < 251; ++i) {
        convert.str("");
        convert << i;

        file = convert.str();

        //create file
        std::ofstream out(file.c_str());
        std::ofstream myfile;

        //start writing
 //       transform = "define shape sphere s 0 " + std::to_string(i+20) + " 0  20 lightblue\n";
        transform = "define shape sphere sphere 0 99 " + std::to_string(80-(i+3)) + " 20 lightblue\n";

        myfile.open(file);
        myfile << "define material black 0.1 0.1 0.1 0.1 0.1 0.1 0.8 0.8 0.8 80\n"
        << "define material grey       0.4 0.4 0.4  0.5 0.5 0.5  0.8 0.8 0.8  200\n"
        << "define material red        0.7 0.1 0.1  0.8 0.2 0.2  0.6 0.2 0.2  100\n"
        << "define material blue       0.1 0.1 0.6  0.1 0.1 0.6  0.3 0.3 0.5  100\n"
        << "define material lightgrey  0.8 0.8 0.8  0.9 0.9 0.9  0.9 0.9 0.9  100\n"
        << "define material darkgrey   0.2 0.2 0.2  0.3 0.3 0.4  0.7 0.7 0.7  540\n"
        << "define material lightblue  0.3 0.3 0.7  0.4 0.4 0.8  0.9 0.9 0.9  600\n"
        << "define shape box bottom  -150   0 -250   150  -1 150  lightgrey\n"
        << "define shape box back     150   0  150  -150 300 151  grey\n"
        << "define shape box left     150   0 -250   151 300 150  blue\n"
        << "define shape box right   -150   0 -250  -151 300 150  red\n"
        << "define shape box top     -150 300 -250   150 301 150  grey\n"
        << transform
        << "define camera camera  65  0 150 -450  0 80 -1  0 1 0\n"
        << "define light sun      0 299    0  0.97 0.91 0.35  1.0  0.98 0.7\n";
        myfile.close();

        sdf.read(file);

        renderer.set_scene(sdf.scene());
        renderer.set_image(file);
        renderer.render();
        std::cout << i << std::endl;
      }
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
  //Renderer app /* (scene) */;
  //app.set_scene(sdf.scene());

  application app;
  app.animate();

  // start computation in thread
  //std::thread thr(std::bind(&Renderer::render, &app));
  std::thread thr(std::bind(&application::run, & app));

  // start output on glutwindow
  glutwindow::instance().run();

  // wait on thread
  thr.join();

  return 0;
}
