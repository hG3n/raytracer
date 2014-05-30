#ifndef SCENE_HPP
#define SCENE_HPP

#include <set>
#include <map>
#include <list>
#include <vector>

#include <material.hpp>
#include <shape.hpp>
#include <camera.hpp>
#include <light.hpp>

#include <memory>

// shape* <-> std::shared_ptr<shape>

struct Scene {
  Scene();
  ~Scene();

  std::map<std::string, Material> materials;
  std::vector<shape*> shapes;
  //std::vector<std::shared_ptr<shape>> shapes;
  std::vector<Camera> cameras;
  std::vector<Light> lights;
};

std::ostream& operator<<(std::ostream& , Scene const&);

#endif
