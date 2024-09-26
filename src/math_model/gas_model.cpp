#include <cstdlib>
#include <sys/vector.hpp>
#include <math_model/gas_model.hpp>
#include <cassert>


AMolecule *GasModel::addMolecule( const Vector init_move_vec, MoleculeType init_type)
{
    AMolecule *molecule = nullptr;
    switch ( init_type )
    {
        case MoleculeTypeSquare:
            molecule = new MoleculeSquare( init_move_vec);
            break;
        case MoleculeTypeOctagon:
            molecule = new MoleculeOctagon( init_move_vec);
            break;
        default:
            assert( 0 );
    }
    gas_.insert( gas_.end(), molecule);

    return molecule;
}


AMolecule *GasModel::addRandomMolecule()
{
    float x_0 = rand() % (int) this->c_sys_->getWidth();
    float y_0 = rand() % (int) this->c_sys_->getHeight();
    float x   = float( rand() % 2001 - 1000) + x_0;
    float y   = float( rand() % 2001 - 1000) + y_0;
    MoleculeType type = ( rand() % 2 == 0 ) ? MoleculeTypeSquare : MoleculeTypeOctagon;

    PointCoordinates start = c_sys_->translateFromPixels( {x_0, y_0});
    PointCoordinates end = c_sys_->translateFromPixels( {x, y});

    return addMolecule( Vector( x, y, x_0, y_0), type);
}


void GasModel::removeMolecule()
{
    if ( gas_.empty() ) return;

    AMolecule *molecule = gas_.front();
    gas_.erase( gas_.begin());
    delete molecule;
}


void GasModel::moveMolecules()
{
    for ( auto &molecule : gas_ )
    {
        molecule->move( c_sys_);
    }
}
