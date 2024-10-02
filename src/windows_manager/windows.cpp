#include <windows_manager/windows.hpp>
#include <cassert>
#include <windows_manager/buttons.hpp>


WindowMolecules::WindowMolecules( unsigned int init_width, unsigned int init_height, std::list<AMolecule *> *init_gas, Controller *ctrl)
    :   width_( init_width), height_( init_height), c_sys_( init_width, init_height),
        gas_( init_gas), ctrl_( ctrl)
{
    assert( init_gas     );

    this->createButtons();
}


void WindowMolecules::draw( sf::RenderWindow &window)
{
    for ( const auto &molecule : *gas_ )
    {
        molecule->draw( window, c_sys_);
    }
    for ( const auto &button : buttons_ )
    {
        button->draw( window);
    }
}


CoordinateSys &WindowMolecules::getCSys()
{
    return c_sys_;
}


void WindowMolecules::createButtons()
{
    Button *add_button = new Button( {0, 0, 64, 64}, ButtonAddMolecule, ctrl_);
    buttons_.push_back( add_button);

    Button *remove_button = new Button( {64, 0, 64, 64}, ButtonRemoveMolecule, ctrl_);
    buttons_.push_back( remove_button);
}


void WindowMolecules::proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key)
{
    size_t size = buttons_.size();
    if ( event.type == sf::Event::MouseButtonPressed )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            buttons_[i]->onClick( sf::Mouse::getPosition( window), event, key);
        }
    } else if ( event.type == sf::Event::MouseButtonReleased )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            buttons_[i]->onRelease( sf::Mouse::getPosition( window), event, key);
        }
    } else
    {
        for ( size_t i = 0; i < size; i++ )
        {
            buttons_[i]->onHover( sf::Mouse::getPosition( window), event, key);
        }
    }
}
