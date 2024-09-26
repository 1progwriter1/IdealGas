#ifndef CONTROLLER_FUNCTIONS
#define CONTROLLER_FUNCTIONS


#include <view/view.hpp>
#include <math_model/gas_model.hpp>


class Controller
{
    View *view_;
    GasModel *model_;

public:
    Controller( View *init_view, GasModel *init_model);
    Controller() = default;
};


#endif // CONTROLLER_FUNCTIONS
