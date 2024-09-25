#include "coor_sys.hpp"
#include "molecule.hpp"
#include "vector.hpp"
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <gas_model.hpp>


void GasModel::addMolecule( const Vector init_move_vec, MoleculeType init_type)
{
    Molecule *molecule = new Molecule( init_move_vec, init_type, this->c_sys_);
    gas_.insert( gas_.end(), molecule);
}


void GasModel::addRandomMolecule()
{
    float x_0 = rand() % (int) this->c_sys_->getWidth();
    float y_0 = rand() % (int) this->c_sys_->getHeight();
    float x   = float( rand() % 2001 - 1000) + x_0;
    float y   = float( rand() % 2001 - 1000) + y_0;
    MoleculeType type = ( rand() % 2 == 0 ) ? MoleculeLightGreenOctagon : MoleculeYellowSquare;

    PointCoordinates start = c_sys_->translateFromPixels( {x_0, y_0});
    PointCoordinates end = c_sys_->translateFromPixels( {x, y});
    Molecule *molecule = new Molecule( Vector( end.x, end.y, start.x, start.y), type, this->c_sys_);
    gas_.insert( gas_.end(), molecule);
}


void GasModel::removeMolecule()
{
    if ( gas_.empty() ) return;

    Molecule *molecule = gas_.front();
    gas_.erase( gas_.begin());
    delete molecule;
}


void GasModel::drawMolecules( GraphWindow &window)
{
    for ( const auto &i : gas_ )
    {
        window.window_.draw( i->getSprite());
    }
}


void GasModel::moveMolecules()
{
    for ( auto &molecule : gas_ )
    {
        molecule->move();
    }
}


void addManyMolecules( size_t count, GasModel &model)
{
    for ( size_t i = 0; i < count; i++ )
    {
        model.addRandomMolecule();
    }
}
