#ifndef GAS_MOLECULE
#define GAS_MOLECULE


#include "coor_sys.hpp"
#include <vector.hpp>
#include <SFML/Graphics.hpp>


const float MOLECULE_SCALE = 1;


enum MoleculeType
{
    MoleculeLightGreenOctagon = 0,  // TODO blue
    MoleculeYellowSquare      = 1,  // TODO red
};


struct CenterCoord
{
    double x;
    double y;
};


class Molecule
{
    Vector move_vec_;
    MoleculeType type_;

    sf::Sprite *sprite_;
    sf::Texture *texture_;

    long long last_draw_;

    CoordinateSys *c_sys_;

public:
    Molecule( const Vector init_move_vec, MoleculeType init_type, CoordinateSys *c_sys);
    ~Molecule();

    void move();
    const sf::Sprite &getSprite() const;
    void setCoordinates( double new_x_0, double new_y_0);
    CenterCoord getCenter() const;
};

long long getTime();

#endif // GAS_MOLECULE
