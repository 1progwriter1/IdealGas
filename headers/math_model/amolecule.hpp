#ifndef ABSTRACT_MOLECULE
#define ABSTRACT_MOLECULE


#include <sys/vector.hpp>
#include <sys/coor_sys.hpp>
#include <SFML/Graphics.hpp>


enum MoleculeType
{
    MoleculeTypeSquare = 0,
    MoleculeTypeOctagon = 1,
};


enum LocationStatus
{
    LocationNormal = 0,
    LocationRightEscape = 1,
    LocationLeftEscape = 2,
    LocationUpEscape = 3,
    LocationDownEscape = 4,
};


struct ReflectData
{
    PointCoordinates new_center;
    PointCoordinates old_center;
    LocationStatus status;
    CoordinateSys *c_sys;
};


class AMolecule
{
protected:
    Vector move_vec_;
    long long last_draw_;
    float radius_;
    float weight_;

public:
    AMolecule( Vector init_move_vec, float init_radius, float init_weight);
    virtual ~AMolecule() {};

    virtual void draw( sf::RenderWindow &window) {};

    void move( CoordinateSys *c_sys);
    PointCoordinates getCenter() const;

private:
    Vector reflectFromWall( ReflectData &data);
    LocationStatus isOutOfTheWindow( ReflectData &data);
    PointCoordinates findReflectPoint( ReflectData &data);
};


long long getTime();


#endif // ABSTRACT_MOLECULE
