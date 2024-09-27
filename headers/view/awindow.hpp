#ifndef ABSTRACT_WINDOW
#define ABSTRACT_WINDOW


#include <SFML/Graphics.hpp>


class AWindow
{
public:
    AWindow() = default;
    virtual ~AWindow() = default;

    virtual void draw( sf::RenderWindow &window) = 0;
};


#endif // ABSTRACT_WINDOW
