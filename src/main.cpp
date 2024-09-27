#include <systemdata.h>
#include <view/view.hpp>
#include <controller/controller.hpp>
#include <math_model/gas_model.hpp>
#include <view/windows.hpp>
#include <view/buttons.hpp>

// TODO class diagram

int main()
{
    View view( 1400, 900, "IdealGas");

    GasModel model( nullptr);

    createWindows( view, model.getGas());
    model.c_sys_ = &dynamic_cast<WindowMolecules *>( view.getWindow())->getCSys();
    addManyMolecules( 10, model);

    createButtons( view.getButtonsManager(), &model);

    Controller ctrl( &view, &model);

    while ( !ctrl.isOver() )
    {
        sf::Event event;
        sf::Keyboard key;
        while ( view.getMainWindow().pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                view.getMainWindow().close();
            }
        }
        view.clear();

        view.getButtonsManager().proceedButtons( view.getMainWindow(), event, key, &model);
        view.getButtonsManager().drawButtons( view.getMainWindow());

        for ( const auto &window : view.getWindows() )
        {
            window->draw( view.getMainWindow());
        }
        model.moveMolecules();

        view.display();
    }

    return SUCCESS;
}
