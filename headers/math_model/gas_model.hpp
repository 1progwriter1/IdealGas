#ifndef IDEAL_GAS_MODEL
#define IDEAL_GAS_MODEL

#include "coor_sys.hpp"
#include <cstddef>
#include <molecules.hpp>
#include <list>
#include <vector.hpp>
#include <graphlib.hpp>

class GasModel
{
    std::list<Molecule *> gas_;
public:
    GasModel( CoordinateSys *c_sys)
        :   c_sys_( c_sys) {};
    ~GasModel() = default;

    CoordinateSys *c_sys_;

    void moveMolecules();
    void addMolecule( const Vector init_move_vec, MoleculeType init_type);
    void drawMolecules( GraphWindow &window);

    void addRandomMolecule();
    void removeMolecule();
};


void addManyMolecules( size_t count, GasModel &model);

#endif // IDEAL_GAS_MODEL
