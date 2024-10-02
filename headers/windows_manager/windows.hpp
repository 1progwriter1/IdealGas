#ifndef VIEW_WINDOWS_FUNCTIONS
#define VIEW_WINDOWS_FUNCTIONS


#include <windows_manager/awindow.hpp>
#include <list>
#include <math_model/amolecule.hpp>
#include <windows_manager/buttons_manager.hpp>
#include <controller/controller.hpp>


class WindowMolecules : public AWindow
{
    unsigned int width_;
    unsigned int height_;
    CoordinateSys c_sys_;

    std::list<AMolecule *> *gas_;
    std::vector<AButton *> buttons_;

    Controller *ctrl_;

public:
    WindowMolecules( unsigned int init_width, unsigned int init_height, std::list<AMolecule *> *init_gas, Controller *ctrl);
    ~WindowMolecules() = default;

    CoordinateSys &getCSys();
    void draw( sf::RenderWindow &window);
    void createButtons();
    void proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key);

private:
    void drawButtons( sf::RenderWindow &window);
};


#endif // VIEW_WINDOWS_FUNCTIONS
