#include <systemdata.h>
#include <windows_manager/windows_manager.hpp>
#include <controller/controller.hpp>
#include <math_model/gas_model.hpp>
#include <windows_manager/windows.hpp>
#include <windows_manager/buttons.hpp>
#include <my_exceptions/my_exceptions.hpp>


int main()
{
    try
    {
        View view( 1400, 900, "IdealGas");
        GasModel model( nullptr);

        Controller ctrl( &view, &model);
        ctrl.createButtons();
        ctrl.createWindows();

        model.setCoordSys( &dynamic_cast<WindowMolecules *>( view.getWindow())->getCSys());
        addManyMolecules( 10, model);

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

            ctrl.proceedModel();
            ctrl.proceedWindows( event, key);
            ctrl.drawWindows();

            view.display();
        }
    } catch ( my_std::my_exception *exc)
    {
        exc->dumpInfo();
        delete exc;
        return ERROR;
    }

    return SUCCESS;
}
