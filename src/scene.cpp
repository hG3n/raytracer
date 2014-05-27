#include <scene.hpp>

Scene::Scene():
    materials(),
    shapes()
    //cameras(),
    //lights()
{}

Scene::~Scene()
{}

std::ostream& operator<<(std::ostream& output, Scene const& scene)
{
    for(auto i : scene.materials)
        output << i.second << std::endl << std::endl;
    for(auto i : scene.shapes)
        output << *i << std::endl << std::endl;
    /*
    for(auto i : scene.lights)
        output << i << std::endl << std::endl;
    */
    for(auto i : scene.cameras)
        output << i << std::endl << std::endl;
    return output;
}

