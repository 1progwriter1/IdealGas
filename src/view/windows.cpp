#include <view/windows.hpp>
#include <cassert>


WindowMolecules::WindowMolecules( unsigned int init_width, unsigned int init_height, std::list<AMolecule *> *init_gas)
    :   width_( init_width), height_( init_height), gas_( init_gas),
        c_sys_( init_width, init_height)
{
    assert( init_gas );
}


void WindowMolecules::draw( View *view)
{
    assert( view );

    for ( const auto molecule : *gas_ )
    {
        molecule->draw( view);
    }
}


CoordinateSys &WindowMolecules::getCSys()
{
    return c_sys_;
}
