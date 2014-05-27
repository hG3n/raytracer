#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <sstream>
#include <string>

#include <scene.hpp>

class SDFloader
{
    public:
        SDFloader();
        ~SDFloader();

        Scene const& scene() const;
        void read(std::string file);
        //void animation_description() const;

    private:
        void add_material(std::istringstream&);
        void add_shape(std::istringstream&);
        void add_camera(std::istringstream&);

    private:
        Scene scene_;
};

std::ostream& operator<<(std::ostream&, SDFloader const&);

#endif
