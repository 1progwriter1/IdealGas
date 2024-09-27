#ifndef CONTROLLER_FUNCTIONS
#define CONTROLLER_FUNCTIONS


#include <view/view.hpp>
#include <math_model/gas_model.hpp>
#include <view/buttons_manager.hpp>


class Controller
{
    View *view_;
    GasModel *model_;

public:
    Controller( View *init_view, GasModel *init_model);
    Controller() = default;

    bool isOver();
    void proceedButtons();
    void proceedModel();

};


#endif // CONTROLLER_FUNCTIONS
