#ifndef GAS_MOLECULE
#define GAS_MOLECULE


#include <vector.hpp>
#include <SFML/Graphics.hpp>


const float MOLECULE_SCALE = 1;


enum MoleculeType
{
    MoleculeLightGreenOctagon = 0,
    MoleculeYellowSquare      = 1,
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

public:
    Molecule( const Vector init_move_vec, MoleculeType init_type);
    ~Molecule();

    void move();
    const sf::Sprite &getSprite() const;

    CenterCoord getCenter() const;
};

long long getTime();

#endif // GAS_MOLECULE
