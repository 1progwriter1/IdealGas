#include "../../MyLibraries/headers/systemdata.h"
#include <SFML/Graphics.hpp>
#include "gas_model.hpp"
#include "graphlib.hpp"
#include "molecule.hpp"
#include "vector.hpp"


int main()
{
    GraphWindow window( 1400, 900);
    GasModel model;

    model.addMolecule( Vector( 100.1, 100.1, 100, 100), MoleculeLightGreenOctagon);     // TODO blue
    model.addMolecule( Vector( 200.2, 200, 200, 200), MoleculeYellowSquare);            // TODO red

    while ( window.window_.isOpen() )
    {
        sf::Event event;
        while ( window.window_.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.window_.close();
            }
        }
        window.clear();
        model.moveMolecules();
        model.drawMolecules( window);
        window.display();
    }

    return SUCCESS;
}
