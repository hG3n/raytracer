#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

#include <sdf_loader.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <triangle.hpp>
#include <cylinder.hpp>

SDFloader::SDFloader():
    scene_()
{}

SDFloader::~SDFloader()
{}

Scene const& SDFloader::scene() const{
  return scene_;
}

void SDFloader::read(std::string file) {

  // delete eventually existing scene
  scene_.materials.clear();
  scene_.shapes.clear();
  scene_.cameras.clear();
  scene_.lights.clear();

  std::ifstream f;
  std::string s;

  f.open(file, std::ios::in);
  while (!f.eof()) {          // Solange noch Daten vorliegen
    getline(f, s);        // Lese eine Zeile

    std::istringstream iss(s);

    std::string sub;
    iss >> sub;

    if(sub == "define"){
      iss >> sub;
      if(sub == "material")
        add_material(iss);
      else if(sub == "shape")
        add_shape(iss);
      else if(sub == "camera")
        add_camera(iss);
      else if(sub == "light")
        add_light(iss);
    }
  }
  f.close();
}

void SDFloader::add_material(std::istringstream& iss) {
  std::string name;
  float r,g,b,m;

  iss >> name >> r >> g >> b;
  Color ka(r,g,b);

  iss >> r >> g >> b;
  Color kd(r,g,b);

  iss >> r >> g >> b >> m;
  Color ks(r,g,b);

  scene_.materials[name] = Material(name,ka,kd,ks,m);
}

void SDFloader::add_shape(std::istringstream& iss) {

  std::string name;
  iss >> name;
  if(name == "box") {
    double x1,y1,z1,x2,y2,z2;
    std::string mat;
    iss >> name >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> mat;
    scene_.shapes.push_back(new box(math3d::point(x1,y1,z1), 
                                    math3d::point(x2,y2,z2),
                                    name,
                                    &scene_.materials[mat]));
  }
  else if(name == "sphere") {
    double x,y,z,r;
    std::string mat;
    iss >> name >> x >> y >> z >> r >> mat;
    scene_.shapes.push_back(new sphere(math3d::point(x,y,z),
                                       r,
                                       name,
                                       &scene_.materials[mat]));
  }
  else if(name == "triangle") {
    double a0,a1,a2,b0,b1,b2,c0,c1,c2;
    std::string mat;
    iss >> name >> a0 >> a1 >> a2 >> b0 >> b1 >> b2 >> c0 >> c1 >> c2 >> mat;
    scene_.shapes.push_back(new triangle(math3d::point(a0,a1,a2),
                                         math3d::point(b0,b1,b2),
                                         math3d::point(c0,c1,c2),
                                         name,
                                         &scene_.materials[mat]));
  }
  else if(name == "cylinder") {
    double c0,c1,c2,radius,height;
    std::string mat;
    iss >> name >> c0 >> c1 >> c2 >> radius >> height >> mat;
    scene_.shapes.push_back(new cylinder(math3d::point(c0,c1,c2),
                                         radius,
                                         height,
                                         name,
                                         &scene_.materials[mat]));
  }
}

void SDFloader::add_camera(std::istringstream& iss) {
  std::string name;
  double alpha,pos_x, pos_y,pos_z, lookat_x, lookat_y, lookat_z, up_x, up_y, up_z;

  iss >> name >> alpha >> 
         pos_x >> pos_y >> pos_z >>
         lookat_x >> lookat_y >> lookat_z >>
         up_x >> up_y >> up_z;
  scene_.cameras.push_back( Camera(name,
                                   math3d::point(pos_x,pos_y,pos_z),
                                   alpha,
                                   math3d::point(lookat_x,lookat_y,lookat_z),
                                   math3d::vector(up_x,up_y,up_z)) );
}

void SDFloader::add_light(std::istringstream& iss) {
  std::string name;
  double x, y, z, la0, la1, la2, ld0, ld1, ld2;

  iss >> name >> x >> y >> z >>
         la0 >> la1 >> la2 >>
         ld0 >> ld1 >> ld2;
  scene_.lights.push_back( Light( name,
                                  math3d::point(x,y,z),
                                  Color(la0,la1,la2),
                                  Color(ld0,ld1,ld2)));
}

std::ostream& operator<<(std::ostream& output, SDFloader const& sdf) {
    output << sdf.scene();
    return output;
}

