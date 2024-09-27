#ifndef VIEW_WINDOWS_FUNCTIONS
#define VIEW_WINDOWS_FUNCTIONS


#include <view/awindow.hpp>
#include <list>
#include <math_model/amolecule.hpp>
#include <view/buttons_manager.hpp>


class WindowMolecules : public AWindow
{
    unsigned int width_;
    unsigned int height_;
    std::list<AMolecule *> *gas_;

    CoordinateSys c_sys_;

public:
    WindowMolecules( unsigned int init_width, unsigned int init_height, std::list<AMolecule *> *init_gas);
    ~WindowMolecules() = default;

    CoordinateSys &getCSys();
    void draw( sf::RenderWindow &window);
};


#endif // VIEW_WINDOWS_FUNCTIONS
