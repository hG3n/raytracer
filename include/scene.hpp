#ifndef SCENE_HPP
#define SCENE_HPP

#include <set>
#include <map>
#include <list>

#include <material.hpp>
#include <shape.hpp>
//#include <light.hpp>
#include <camera.hpp>

struct Scene
{
    Scene();
    ~Scene();
    std::map<std::string, Material> materials;
    std::set<shape*> shapes;
    std::list<Camera> cameras;
    //std::list<Light> lights;
};

std::ostream& operator<<(std::ostream& output, Scene const& scene);

#endif
