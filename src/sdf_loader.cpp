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
    //loeschen einer evt. vorhandenen scene
    scene_.materials.clear();
    scene_.shapes.clear();
    //scene_.cameras.clear();
    //scene_.lights.clear();

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
            else if(sub == "light")
                add_light(iss);
            else if(sub == "camera")
                add_camera(iss);
        }
        else if(sub == "transform") {
            apply_transformation(iss);
        }
    }
    f.close();
}
/*
void SDFloader::animation_description() const
{

}
*/

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
      scene_.shapes.insert(new box(point(x1,y1,z1), 
                                   point(x2,y2,z2),
                                   name,
                                   &scene_.materials[mat]));
    }
    else if(name == "sphere") {
      double x,y,z,r;
      std::string mat;
      iss >> name >> x >> y >> z >> r >> mat;
      scene_.shapes.insert(new sphere(point(x,y,z),
                                      r,
                                      name,
                                      &scene_.materials[mat]));
    }
    else if(name == "triangle") {
      double a0,a1,a2,b0,b1,b2,c0,c1,c2;
      std::string mat;
      iss >> name >> a0 >> a1 >> a2 >> b0 >> b1 >> b2 >> c0 >> c1 >> c2 >> mat;
      scene_.shapes.insert(new triangle(point(a0,a1,a2),
                                        point(b0,b1,b2),
                                        point(c0,c1,c2),
                                        name,
                                        &scene_.materials[mat]));
    }
    else if(name == "cylinder") {
      double c0,c1,c2,radius,height;
      std::string mat;
      iss >> name >> c0 >> c1 >> c2 >> radius >> height >> mat;
      scene_.shapes.insert(new cylinder(point(c0,c1,c2),
                                        radius,
                                        height,
                                        name,
                                        &scene_.materials[mat]));
    }
}

/*
void SDFloader::add_light(std::istringstream& iss) {
  std::string name;
  double x,y,z;
  double la0,la1,la2;
  double ld0,ld1,ld2;
  iss >> name >> x >> y >> z >> la0 >> la1 >> la2 >> ld0 >> ld1 >> ld2;
  scene_.lights.push_back( Light(name, point(x,y,z), Color(la0,la1,la2), color(ld0,ld1,ld2)) );
}

void SDFloader::add_camera(std::istringstream& iss)
{
  std::string name;
  double alpha,pos_x,pos_y,pos_z,lookat_x,lookat_y,lookat_z,up_x,up_y,up_z;
  iss >> name >> alpha >> pos_x >> pos_y >> pos_z >> lookat_x >> lookat_y >> lookat_z >> up_x >> up_y >> up_z;
  scene_.cameras.push_back( Camera(name, point(pos_x,pos_y,pos_z), alpha, point(lookat_x,lookat_y,lookat_z), vector(up_x,up_y,up_z)) );
}
*/

void SDFloader::apply_transformation(std::istringstream& iss) {

    std::string name, type_of_trans;
    iss >> name >> type_of_trans;
    if(type_of_trans == "rotate") {
        double angle,x,y,z;
        iss >> angle >> x >> y >> z;
        for(auto i : scene_.shapes)
        {
            if(i->name() == name)
            {
                if(x > 0)
                    i->rotate_x(angle);
                if(y > 0)
                    i->rotate_y(angle);
                if(z > 0)
                    i->rotate_z(angle);
            }
        }
    }
    else if(type_of_trans == "translate") {
        double x,y,z;
        iss >> x >> y >> z;
        for(auto i : scene_.shapes)
            if(i->name() == name)
                i->translate(x,y,z);
    }
    else if(type_of_trans == "scale") {
        double x,y,z;
        iss >> x >> y >> z;
        for(auto i : scene_.shapes)
            if(i->name() == name)
                i->scale(x,y,z);
    }
}

std::ostream& operator<<(std::ostream& output, SDFloader const& sdf) {
    output << sdf.scene();
    return output;
}

size_t CountWords( std::string s )
  {
  // If the string contains only whitespace, then there are no words.
  //
  // Otherwise:
  //   number of words := number of whitespace sequences - leading whitespace + trailing whitespace
  //
  return ((size_t)std::count_if( s.begin(), s.end(), std::ptr_fun <int, int> ( std::isspace ) ) == s.length())
       ? 0
       : std::count_if(
           std::find_if(
             s.begin(),
             s.end(),
             std::not1( std::ptr_fun <int, int> ( std::isspace ) )
             ),
           std::unique(
             s.begin(),
             std::replace_copy_if(
               s.begin(),
               s.end(),
               s.begin(),
               std::ptr_fun <int, int> ( std::isspace ),
               ' '
               )
             ),
           std::ptr_fun <int, int> ( std::isspace )
           )
         + !std::isspace( *s.rbegin() );
  }



