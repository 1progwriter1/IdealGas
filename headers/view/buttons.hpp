#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS

#include "abutton.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include "buttons_manager.hpp"
#include "math_model/gas_model.hpp"


enum ButtonId
{
    ButtonAddMolecule = 0,
    ButtonRemoveMolecule = 1,
};

enum States
{
    Normal_   = 0,
    OnHover_  = 1,
    Clicked_  = 2,
    Released_ = 3,
};


class Button;


class Animation
{
    float transp_c_;
    States animation_type_;

public:
    Animation( float init_transp_c, States init_anim_type)
        :   transp_c_( init_transp_c), animation_type_( init_anim_type) {};
    ~Animation() = default;

    void animOnHover( Button &button, sf::RenderWindow &window);
    void animOnClick( Button &button, sf::RenderWindow &window);
    void animNormal( Button &button, sf::RenderWindow &window);
    void animReleased( Button &button, sf::RenderWindow &window);
};


struct ButtonData
{
    int pos_x;
    int pos_y;
    float width;
    float height;
};

class Button : public AButton
{
protected:
    States state_;
    ButtonId id_;

    size_t light_ind;

    sf::Sprite *sprites_;
    sf::Texture *textures_;

    GasModel *model_;
    ButtonData data_;
    sf::RectangleShape clearShape_;

public:
    Button( const ButtonData &init_data, ButtonId init_id, GasModel *model);
    ~Button();


    sf::Sprite &getCurSprite();
    States getState() const;
    void setState( States new_state);

    bool isOnFocus( sf::Vector2i mouse_pos);

    void setChangeStatus( bool new_status);
    bool isSphereChanged();

    sf::RectangleShape &getClearShape();

    void onClick  ( sf::Vector2i mouse_pos, const sf::Event &event, const sf::Keyboard &key);
    void onHover  ( sf::Vector2i mouse_pos, const sf::Event &event, const sf::Keyboard &key);
    void onRelease( sf::Vector2i mouse_pos, const sf::Event &event, const sf::Keyboard &key);
    void draw( sf::RenderWindow &window);

    void setLightInd( size_t ind);

    class Animation animation;

private:
    void setSprites();
};


void createButtons( ButtonsManager &manager, GasModel *model);


#endif // BUTTONS_FUNCTIONS
