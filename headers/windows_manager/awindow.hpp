#ifndef ABSTRACT_WINDOW
#define ABSTRACT_WINDOW


#include <SFML/Graphics.hpp>


class AWindow
{
public:
    AWindow() = default;
    virtual ~AWindow() = default;

    virtual void draw( sf::RenderWindow &window) = 0;
    virtual void proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key) {};
    virtual void createButtons() {};
};


#endif // ABSTRACT_WINDOW
