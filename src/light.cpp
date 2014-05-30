#include <light.hpp>

Light::Light(std::string const& n, math3d::point const& p, Color const& a, Color const& d):
  name(n),
  pos(p),
  la(a),
  ld(d)
{}

Light::~Light()
{}

std::ostream& operator<<(std::ostream& out, Light const& light) {

  return out << "Name: " << light.name <<
                " Pos: " << light.pos << 
                " Ambient Light: " << light.la << 
                " Diffuse Light: " << light.ld;
}
