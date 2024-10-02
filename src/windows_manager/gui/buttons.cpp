#include "windows_manager/buttons.hpp"
#include "windows_manager/abutton.hpp"
#include <cstddef>
#include <cstdio>
#include <cassert>
#include "windows_manager/buttons_img.hpp"


Button::Button( const ButtonData &init_data, ButtonId init_id, Controller *ctrl)
    :   AButton( init_data.pos_x, init_data.pos_y),
        state_( Normal_), id_( init_id), data_( init_data),
        clearShape_( sf::Vector2f( float( init_data.width), float( init_data.height))),
        ctrl_( ctrl),
        animation( 0, Normal_)
{
    assert( ctrl );

    sprites_  = new sf::Sprite[NUMBER_OF_ICONS];
    textures_ = new sf::Texture[NUMBER_OF_ICONS];

    clearShape_.setPosition( float( init_data.pos_x), float( init_data.pos_y));
    clearShape_.setFillColor( sf::Color::Black);
    setSprites();
}


Button::~Button()
{
    delete [] sprites_;
    delete [] textures_;
}

void Button::setSprites()
{
    const char **icons = nullptr;
    switch ( this->id_ )
    {
        case ButtonAddMolecule:
            icons = ICONS_ADD;
            break;
        case ButtonRemoveMolecule:
            icons = ICONS_REMOVE;
            break;
        default:
            assert( 0 && "This case is unreachable");
    }
    for ( size_t i = 0; i < NUMBER_OF_ICONS; i++ )
    {
        textures_[i].loadFromFile( icons[i]);
        sprites_ [i].setTexture  ( textures_[i]);
        sprites_ [i].setPosition( this->data_.pos_x, this->data_.pos_y);
    }
}


sf::Sprite &Button::getCurSprite()
{
    return sprites_[state_];
}


void Button::setState( States new_state)
{
    state_ = new_state;
}

bool Button::isOnFocus( sf::Vector2i mouse_pos)
{
    return data_.pos_x <= mouse_pos.x && mouse_pos.x <= data_.pos_x + data_.width &&
            data_.pos_y <= mouse_pos.y && mouse_pos.y <= data_.pos_y + data_.height;
}

void Button::onHover( sf::Vector2i mouse_pos, const sf::Event &/*event*/, const sf::Keyboard &/*key*/)
{
    if ( this->isOnFocus( mouse_pos) )
    {
        this->setState( OnHover_);
    }
    else
    {
        this->setState( Normal_);
    }
}

void Button::onClick( sf::Vector2i mouse_pos, const sf::Event &/*event*/, const sf::Keyboard &key)
{
    if ( !this->isOnFocus( mouse_pos) )
    {
        this->setState( Normal_);
        return;
    }
    this->setState( Clicked_);

    switch ( this->id_ )
    {
        case ButtonAddMolecule:
            ctrl_->addButtonCmd( CmdAddMolecule);
            break;

        case ButtonRemoveMolecule:
            ctrl_->addButtonCmd( CmdRemoveMolecule);
            break;

        default:
            assert( 0 && "This case is unreachable" );
    }
}

void Button::onRelease( sf::Vector2i mouse_pos, const sf::Event &/*event*/, const sf::Keyboard &/*key*/)
{
    if ( this->isOnFocus( mouse_pos) )
    {
        this->setState( Released_);
    } else
    {
        this->setState( Normal_);
    }
}


sf::RectangleShape &Button::getClearShape()
{
    return clearShape_;
}


void Button::draw( sf::RenderWindow &window)
{
    window.draw( this->getCurSprite());
    return;
//     switch ( state_ )
//     {
//         case Clicked_:
//             animation.animOnClick( *this, window);
//             break;
//
//         case Released_:
//             animation.animReleased( *this, window);
//             break;
//
//         case OnHover_:
//             animation.animOnHover( *this, window);
//             break;
//
//         case Normal_:
//             animation.animNormal( *this, window);
//             break;
//
//         default:
//             assert( 0 );
//     }

}

// TODO common actions to private function

void Animation::animNormal( Button &/*button*/, sf::RenderWindow &/*window*/)
{

}


void Animation::animOnClick( Button &button, sf::RenderWindow &window)
{
    animation_type_ = Clicked_;
    transp_c_ = 0;
    window.draw( button.getCurSprite());
}


void Animation::animOnHover( Button &/*button*/, sf::RenderWindow &/*window*/)
{
    if ( animation_type_ != OnHover_ )
    {
        transp_c_ = 0;
        animation_type_ = OnHover_;
    }
}


void Animation::animReleased( Button &/*button*/, sf::RenderWindow &/*window*/)
{

}
