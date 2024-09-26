#include <systemdata.h>
#include <view/view.hpp>
#include <controller/controller.hpp>
#include <math_model/gas_model.hpp>
#include <view/windows.hpp>

// TODO class diagram

int main()
{
    View view( 1400, 900);

    GasModel model( &dynamic_cast<WindowMolecules *>( view.getWindow())->getCSys());

    Controller ctrl( &view, &model);

//     while ( ctrl.isOver() )
//     {
//         ctrl.proceedButtons();
//         ctrl.proceedModel();
//
//         ctr.draw();
//     }

    return SUCCESS;
}
