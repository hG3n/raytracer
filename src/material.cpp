#include "material.hpp"
#include <iostream>

Material::Material():
  name("default"),
  ka(Color()),
  kd(Color()),
  ks(Color()),
  m(0.0)
{}

Material::Material(std::string const& name_val, Color const& ka_val, Color const& kd_val, Color const& ks_val, float m_val):
  name(name_val),
  ka(ka_val),
  kd(kd_val),
  ks(ks_val),
  m(m_val)
{}

Material::Material(Material const& material):
  name(material.name),
  ka(material.ka),
  kd(material.kd),
  ks(material.ks),
  m(material.m)
{}

Material::~Material()
{}

// ---------------
// --- methods ---
// ---------------

bool Material::operator==(Material rhs) {
  return (ka == rhs.ka && kd == rhs.kd && ks == rhs.ks && m == rhs.m);
}

bool Material::operator!=(Material rhs) {
  return !(*this == rhs);
}


std::ostream& operator<<(std::ostream& output, Material const& material) {
  output <<  "Materialname: " <<  material.name <<  "\n Ambient color: " << material.ka << " Diffuse color: " << material.kd << " Specular color: " << material.ks << " m-Value: " << material.m;
  return output;
}
