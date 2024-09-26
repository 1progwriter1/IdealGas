#include "systemdata.h"
#include <SFML/Graphics.hpp>
// #include "view/buttons.hpp"
// #include "gas_model.hpp"
// #include "graphlib.hpp"
// #include <buttons_manager.hpp>

// TODO class diagram

int main()
{
    sf::RenderWindow window( sf::VideoMode( 800, 600), "hello");

    while ( window.isOpen() )
    {
        sf::Event event;
        sf::Keyboard key;
        while ( window.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
        }

        window.display();
    }

    return SUCCESS;
}
