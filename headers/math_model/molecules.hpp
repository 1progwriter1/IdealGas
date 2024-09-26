#ifndef GAS_MOLECULE
#define GAS_MOLECULE


#include "coor_sys.hpp"
#include <vector.hpp>
#include <SFML/Graphics.hpp>


enum LocationStatus
{
    LocationNormal = 0,
    LocationRightEscape = 1,
    LocationLeftEscape = 2,
    LocationUpEscape = 3,
    LocationDownEscape = 4,
};


const float MOLECULE_SCALE = 1.0f;


enum MoleculeType
{
    MoleculeLightGreenOctagon = 0,  // TODO blue
    MoleculeYellowSquare      = 1,  // TODO red
};

class MoleculeSquare
{
    sf::CircleShape molecule_;
    sf::Color color_;
public:
    MoleculeSquare( sf::Color init_color = sf::Color( 255, 51, 51));
    ~MoleculeSquare() = default;
};


class MoleculeOctagon
{
    sf::CircleShape molecule_;
    sf::Color color_;
public:
    MoleculeOctagon( sf::Color init_color = sf::Color( 51, 153, 255, 255));
    ~MoleculeOctagon() = default;
};



class Molecule  // second class
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
    PointCoordinates getCenter() const;
    Vector reflectFromWall( const PointCoordinates &new_center, CoordinateSys *c_sys, LocationStatus status);
    void setNewMoveVec( const Vector &vec);
};

long long getTime();
LocationStatus isOutOfTheWindow( const PointCoordinates &new_center, CoordinateSys *c_sys);
PointCoordinates findReflectPoint( const PointCoordinates &old_center, const PointCoordinates &new_center, CoordinateSys *c_sys, LocationStatus status);

#endif // GAS_MOLECULE
