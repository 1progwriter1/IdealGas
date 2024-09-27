#include "sys/vector.hpp"
#include <cassert>
#include <math_model/molecules.hpp>


const float MOLECULE_OCTAGON_R = 8.f;
const float MOLECULE_SQUARE_R = 12.f;
const float MOLECULE_OCTAGON_W = 1;
const float MOLECULE_SQUARE_W = 2;


MoleculeOctagon::MoleculeOctagon( Vector init_move_vec, sf::Color init_color/*sf::Color( 255, 51, 51)*/)
    :   molecule_( MOLECULE_OCTAGON_R, 8), color_( init_color), AMolecule( init_move_vec, MOLECULE_OCTAGON_R, MOLECULE_OCTAGON_W)
{
    VectorCoordinates coord = init_move_vec.getCoordinates();
    molecule_.setFillColor( init_color);
}


MoleculeSquare::MoleculeSquare( Vector init_move_vec, sf::Color init_color/*sf::Color( 51, 153, 255, 255)*/)
    :   molecule_( MOLECULE_SQUARE_R, 4), color_( init_color), AMolecule( init_move_vec, MOLECULE_SQUARE_R, MOLECULE_SQUARE_W)
{
    VectorCoordinates coord = init_move_vec.getCoordinates();
    molecule_.setFillColor( init_color);
}


void MoleculeOctagon::draw( sf::RenderWindow &window, CoordinateSys &c_sys)
{
    PointCoordinates center = c_sys.translateToPixels( getCenter());
    molecule_.setPosition( center.x, center.y);
    window.draw( molecule_);
}


void MoleculeSquare::draw( sf::RenderWindow &window, CoordinateSys &c_sys)
{
    PointCoordinates center = c_sys.translateToPixels( getCenter());
    molecule_.setPosition( center.x, center.y);
    window.draw( molecule_);
}
