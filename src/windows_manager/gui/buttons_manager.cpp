#include "windows_manager/buttons_manager.hpp"
#include "windows_manager/abutton.hpp"
#include <cassert>
#include <cstddef>


ButtonsManager::ButtonsManager()
{

}


ButtonsManager::~ButtonsManager()
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        delete buttons_[i];
    }
}


void ButtonsManager::addButton( AButton *new_button)
{
    assert( new_button );

    buttons_.push_back( new_button);
}


void ButtonsManager::drawButtons( sf::RenderWindow &window)
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        buttons_[i]->draw( window);
    }
}


void ButtonsManager::proceedButtons( const sf::RenderWindow &window, const sf::Event &event, const sf::Keyboard &key, GasModel *model)
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
