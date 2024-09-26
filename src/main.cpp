#include "../../MyLibraries/headers/systemdata.h"
#include <SFML/Graphics.hpp>
#include "buttons.hpp"
#include "gas_model.hpp"
#include "graphlib.hpp"
#include <time.h>
#include <buttons_manager.hpp>


// TODO class diagram


int main()
{
    srand( (unsigned int)time( NULL));

    GraphWindow window( 1400, 900);
    GasModel model( &window.c_sys_);

    ButtonsManager manager;
    createButtons( manager, &model);

    addManyMolecules( 10, model);
    // model.addMolecule( Vector( 100, 100, 0, 0), MoleculeLightGreenOctagon);

    while ( window.window_.isOpen() )
    {
        sf::Event event;
        sf::Keyboard key;
        while ( window.window_.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.window_.close();
            }
        }
        window.clear();

        manager.proceedButtons( &window, &event, &key);
        manager.drawButtons( window);

        model.moveMolecules();
        model.drawMolecules( window);

        window.display();
    }

    return SUCCESS;
}
