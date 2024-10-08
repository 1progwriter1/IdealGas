#include "math_model/molecules.hpp"
#include <cstdlib>
#include <sys/vector.hpp>
#include <math_model/gas_model.hpp>
#include <cassert>
#include <cstdio>


AMolecule *GasModel::addMolecule( AMolecule *new_molecule)
{
    assert( new_molecule );

    gas_.insert( gas_.end(), new_molecule);

    return new_molecule;
}


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
    float x_0 = rand() % (int) c_sys_->getWidth();
    float y_0 = rand() % (int) c_sys_->getHeight();
    float x   = float( rand() % 2001 - 1000) + x_0;
    float y   = float( rand() % 2001 - 1000) + y_0;
    MoleculeType type = ( rand() % 2 == 0 ) ? MoleculeTypeSquare : MoleculeTypeOctagon;

    PointCoordinates start = c_sys_->translateFromPixels( {x_0, y_0});
    PointCoordinates end = c_sys_->translateFromPixels( {x, y});

    return addMolecule( Vector( end.x, end.y, start.x, start.y), type);
}


void addManyMolecules( size_t count, GasModel &model)
{
    for ( size_t i = 0; i < count; i++ )
    {
        model.addRandomMolecule();
    }
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


std::list<AMolecule *> *GasModel::getGas()
{
    return &gas_;
}


void GasModel::setCoordSys( CoordinateSys *c_sys)
{
    c_sys_ = c_sys;
}



void GasModel::proceedCmd( ButtonCommands cmd)
{
    switch ( cmd )
    {
        case CmdAddMolecule:
            this->addRandomMolecule();
            break;
        case CmdRemoveMolecule:
            this->removeMolecule();
            break;
        default:
            assert( 0 );
    }
}
