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

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// this method shows how to use the supplied classes for matrix, point and vector  
void example_math3d()
{
  // create some geometric objects
  math3d::point  origin;
  math3d::point  p0(1.0, 5.0, -3.0);
  math3d::vector v0(2.0, 2.0, 1.0);

  // some methods
  v0.normalize();

  // operator's
  math3d::vector v1 = origin - p0;  // difference between points is a vector
  double z_component = v0[2];       // random access into components of point/vector

  // you can create transformation matrices
  math3d::matrix rotate = math3d::make_rotation_x(M_PI / 4.0);    // rotation matrix: 45 deg about x axis
  math3d::matrix scale  = math3d::make_scale(1.0, 2.0, 1.0); // scale y axis
  math3d::matrix invrot = math3d::inverse(rotate);

  // concatenate transformations and transform points or vectors
  math3d::vector tv0 = rotate * scale * v0;
  math3d::point  tp0 = rotate * scale * p0;
}

class Renderer
{
public :

  /*
  Renderer(Scene const& scene)
    : m_scene(scene)
  {
  }
  */

  // raytracing is initiated from here
  void render() 
  {
    // get glutwindow instance
    glutwindow& window = glutwindow::instance();
    
    // create a ppmwriter
    ppmwriter image (window.width(), window.height(), "./checkerboard.ppm");

    const std::size_t checkersize = 20; // size of a tile in checkerboard
  
    // for all pixels of window
    for (std::size_t y = 0; y < window.height(); ++y) {
      for (std::size_t x = 0; x < window.width(); ++x) {
        Pixel p(x, y);

        // compute color for pixel
        if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
          p.color = Color(0.0, 1.0, float(x)/window.height());
        } else {
          p.color = Color(1.0, 0.0, float(y)/window.width());
        }

        window.write(p); // write pixel to output window
        image.write(p);  // write pixel to image writer
      }
    }

    // save final image
    image.save();
  }

private : // attributes

  // you may add your scene description here
  // Scene m_scene;

};

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
