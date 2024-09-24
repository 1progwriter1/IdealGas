#include "molecule.hpp"
#include <gas_model.hpp>


void GasModel::addMolecule( const Vector init_move_vec, MoleculeType init_type)
{
    Molecule *molecule = new Molecule( init_move_vec, init_type);
    gas_.insert( gas_.end(), molecule);
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
    for ( auto &i : gas_ )
    {
        i->move();
    }
}
