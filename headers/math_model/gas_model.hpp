#ifndef IDEAL_GAS_MODEL
#define IDEAL_GAS_MODEL


#include <list>
#include <math_model/amolecule.hpp>
#include <math_model/molecules.hpp>


class GasModel
{
    std::list<AMolecule *> gas_;

public:
    GasModel( CoordinateSys *c_sys)
        :   c_sys_( c_sys) {};
    ~GasModel() = default;

    CoordinateSys *c_sys_;

    void moveMolecules();
    AMolecule *addMolecule( const Vector init_move_vec, MoleculeType init_type);

    AMolecule *addRandomMolecule();
    void removeMolecule();
};


void addManyMolecules( size_t count, GasModel &model);

#endif // IDEAL_GAS_MODEL
