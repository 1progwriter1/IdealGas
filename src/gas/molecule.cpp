#include "coor_sys.hpp"
#include "vector.hpp"
#include <cassert>
#include <chrono>
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

    double new_x_0 = coord.x_0 + ( coord.x - coord.x_0) * elapsed;
    double new_y_0 = coord.y_0 + ( coord.y - coord.y_0) * elapsed;
    this->setCoordinates( new_x_0, new_y_0);

    last_draw_ = now;
}


long long getTime()
{
    auto now = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch()).count();
}


CenterCoord Molecule::getCenter() const
{
    VectorCoordinates coord = move_vec_.getCoordinates();

    return {coord.x_0, coord.y_0};
}


void Molecule::setCoordinates( double new_x_0, double new_y_0)
{
    PointCoordinates new_center = this->c_sys_->translateToPixels( {float( new_x_0),
                                                                    float( new_y_0)});

    move_vec_.move( new_x_0, new_y_0);

    sprite_->setPosition( new_center.x, new_center.y);
}
