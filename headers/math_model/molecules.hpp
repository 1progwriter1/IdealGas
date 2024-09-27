#ifndef GAS_MOLECULE
#define GAS_MOLECULE


#include <sys/coor_sys.hpp>
#include <sys/vector.hpp>
#include <SFML/Graphics.hpp>
#include <math_model/amolecule.hpp>


class MoleculeSquare : public AMolecule
{
    sf::CircleShape molecule_;
    sf::Color color_;
    MoleculeType type_;

public:
    MoleculeSquare( Vector init_move_vec, sf::Color init_color = sf::Color( 255, 51, 51));
    ~MoleculeSquare() = default;

    void draw( sf::RenderWindow &window);
};


class MoleculeOctagon : public AMolecule
{
    sf::CircleShape molecule_;
    sf::Color color_;
    MoleculeType type_;

public:
    MoleculeOctagon( Vector init_move_vec, sf::Color init_color = sf::Color( 51, 153, 255, 255));
    ~MoleculeOctagon() = default;

    void draw( sf::RenderWindow &window);
};


#endif // GAS_MOLECULE
