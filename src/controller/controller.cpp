#include <cassert>
#include <controller/controller.hpp>


Controller::Controller( View *init_view, GasModel *init_model)
    :   view_( init_view), model_( init_model)
{
    assert( init_view );
    assert( init_model );
}
