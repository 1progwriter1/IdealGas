#ifndef IDEAL_GAS_MODEL
#define IDEAL_GAS_MODEL

#include <molecule.hpp>
#include <list>
#include <vector.hpp>
#include <graphlib.hpp>

class GasModel
{
    std::list<Molecule *> gas_;
public:
    GasModel() = default;
    ~GasModel() = default;

    void moveMolecules();
    void addMolecule( const Vector init_move_vec, MoleculeType init_type);
    void drawMolecules( GraphWindow &window);
};

#endif // IDEAL_GAS_MODEL
