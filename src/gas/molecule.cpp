#include "coor_sys.hpp"
#include "vector.hpp"
#include <cassert>
#include <chrono>
#include <cstdio>
#include <molecule.hpp>


Molecule::Molecule( const Vector init_move_vec, MoleculeType init_type, CoordinateSys *init_c_sys)
    :   move_vec_( init_move_vec), type_( init_type), last_draw_( getTime()), c_sys_( init_c_sys)
{
    assert( init_c_sys );

    texture_ = new sf::Texture;
    sprite_ = new sf::Sprite;
    switch ( type_ )
    {
        case MoleculeLightGreenOctagon:
            texture_->loadFromFile( "images/lightGreenOctagon16_16.png");
            break;
        case MoleculeYellowSquare:
            texture_->loadFromFile( "images/yellowSquare16_16.png");
            break;
        default:
            assert( 0 );
    }
    sprite_->setTexture( *texture_);
    sprite_->setScale( MOLECULE_SCALE, MOLECULE_SCALE);

    PointCoordinates point = c_sys_->translateToPixels( {(float) move_vec_.getCoordinates().x_0, (float) move_vec_.getCoordinates().y_0});

    sprite_->setPosition( point.x, point.y);
}


Molecule::~Molecule()
{
    delete sprite_;
    delete texture_;
}


const sf::Sprite &Molecule::getSprite() const
{
    return *sprite_;
}


void Molecule::move()
{
    auto now = getTime();
    auto elapsed = now - last_draw_;

    VectorCoordinates coord = move_vec_.getCoordinates();

    double new_x_0 = coord.x_0 + ( coord.x - coord.x_0) * elapsed / 1000;
    double new_y_0 = coord.y_0 + ( coord.y - coord.y_0) * elapsed / 1000;

    LocationStatus status = isOutOfTheWindow( { (float) new_x_0, (float) new_y_0}, c_sys_);
    if ( status != LocationNormal )
    {
        this->move_vec_ = reflectFromWall( { (float) new_x_0, (float) new_y_0}, c_sys_, status);
        VectorCoordinates vec = move_vec_.getCoordinates();
        new_x_0 = vec.x_0;
        new_y_0 = vec.y_0;
    }
    this->setCoordinates( new_x_0, new_y_0);

    last_draw_ = now;
}


long long getTime()
{
    auto now = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch()).count();
}


PointCoordinates Molecule::getCenter() const
{
    VectorCoordinates coord = move_vec_.getCoordinates();

    return { (float) coord.x_0, (float) coord.y_0};
}


void Molecule::setCoordinates( double new_x_0, double new_y_0)
{
    PointCoordinates new_center = this->c_sys_->translateToPixels( {float( new_x_0),
                                                                    float( new_y_0)});

    move_vec_.move( new_x_0, new_y_0);

    sprite_->setPosition( new_center.x, new_center.y);
}


LocationStatus isOutOfTheWindow( const PointCoordinates &new_center, CoordinateSys *c_sys)
{
    assert( c_sys );

    PointCoordinates point = c_sys->translateToPixels( new_center);

    if ( point.x > c_sys->getWidth() )
        return LocationRightEscape;
    if ( point.y > c_sys->getHeight() )
        return LocationDownEscape;
    if ( point.x < 0 )
        return LocationLeftEscape;
    if ( point.y < 0 )
        return LocationUpEscape;
    return LocationNormal;
}


Vector Molecule::reflectFromWall( const PointCoordinates &new_center, CoordinateSys *c_sys, LocationStatus status)
{
    assert( c_sys );

    PointCoordinates point = findReflectPoint( this->getCenter(), new_center, c_sys, status);
    VectorCoordinates reflected = {};
    VectorCoordinates cur = this->move_vec_.getCoordinates();
    reflected.x_0 = point.x;
    reflected.y_0 = point.y;
    // printf( "reflect point: %f %f\n", point.x, point.y);

    switch ( status )
    {
        case LocationNormal:
            return move_vec_;
        case LocationDownEscape:
        case LocationUpEscape:
            reflected.y = -(cur.y - cur.y_0) + cur.y_0;
            reflected.x = cur.x;
            break;
        case LocationRightEscape:
        case LocationLeftEscape:
            reflected.y = cur.y;
            reflected.x = -(cur.x - cur.x_0) + cur.x_0;
            break;
        default:
            assert( 0 );
    }
    return Vector( reflected.x, reflected.y, reflected.x_0, reflected.y_0);
}


PointCoordinates findReflectPoint( const PointCoordinates &old_center, const PointCoordinates &new_center, CoordinateSys *c_sys, LocationStatus status)
{
    assert( c_sys );

    PointCoordinates coord_old = c_sys->translateToPixels( old_center);
    PointCoordinates coord_new = c_sys->translateToPixels( new_center);

    double x_0 = 0;
    double y_0 = 0;
    double scale = 0;

    switch ( status )
    {
        case LocationLeftEscape:
            x_0 = 0;
            scale = ( fabs( coord_old.x - coord_new.x) < 1e-8 ) ? 0 : fabs( (coord_old.x - x_0) / (coord_old.x - coord_new.x));
            y_0 = (coord_new.y - coord_old.y) * scale + coord_old.y;
            break;
        case LocationRightEscape:
            x_0 = c_sys->getWidth();
            scale = ( fabs( coord_old.x - coord_new.x) < 1e-8 ) ? 0 : fabs( (coord_old.x - x_0) / (coord_old.x - coord_new.x));
            y_0 = (coord_new.y - coord_old.y) * scale + coord_old.y;
            break;
        case LocationUpEscape:
            y_0 = 0;
            scale = ( fabs( coord_old.y - coord_new.y) < 1e-8 ) ? 0 : fabs( (coord_old.y - y_0) / (coord_old.y - coord_new.y));
            x_0 = (coord_new.x - coord_old.x) * scale + coord_old.x;
            break;
        case LocationDownEscape:
            y_0 = c_sys->getHeight();
            scale = ( fabs( coord_old.y - coord_new.y) < 1e-8 ) ? 0 : fabs( (coord_old.y - y_0) / (coord_old.y - coord_new.y));
            x_0 = (coord_new.x - coord_old.x) * scale + coord_old.x;
            break;
        case LocationNormal:
        default:
            assert( 0 );
    }

    return c_sys->translateFromPixels( {(float) x_0, (float) y_0});
}


void Molecule::setNewMoveVec( const Vector &vec)
{
    this->move_vec_ = vec;
}
