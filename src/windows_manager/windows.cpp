#include <windows_manager/windows.hpp>
#include <cassert>
#include <windows_manager/buttons.hpp>
#include <my_exceptions/my_exceptions.hpp>


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


WindowTemp::WindowTemp( unsigned int init_width, unsigned int init_height, unsigned int init_pos_x, unsigned int init_pos_y)
    :   width_( init_width), height_( init_height), pos_x_( init_pos_x), pos_y_( init_pos_y),
        rectangle_( sf::Vector2f( init_width, init_height))
{
    rectangle_.setFillColor( sf::Color::White);
    rectangle_.setPosition( pos_x_, pos_y_ - init_height);
    fillInfoToDraw();
}


WindowTemp::~WindowTemp()
{
    delete font_;
}


void WindowTemp::draw( sf::RenderWindow &window)
{
    window.draw( rectangle_);
    window.draw( base_lines_.data(), base_lines_.size(), sf::Lines);
    for ( const auto &mark: marks_ )
    {
        window.draw( mark);
    }
    for ( const auto &line: lines_ )
    {
        window.draw( &line, 1, sf::Lines);
    }
}


void WindowTemp::fillInfoToDraw()
{
    try
    {
        fillBaseLines();
        fillMarks();
    }
    catch ( my_std::my_exception *exc)
    {
        throw new MY_EXCEPTION( "failed to fill data for temperature window", exc);
    }
}


void WindowTemp::fillBaseLines()
{
    base_lines_.push_back( sf::Vertex( sf::Vector2f( pos_x_ + 15, pos_y_ - 15), sf::Color::Red));
    base_lines_.push_back( sf::Vertex( sf::Vector2f( pos_x_ + width_ - 15, pos_y_ - 15), sf::Color::Red));

    base_lines_.push_back( sf::Vertex( sf::Vector2f( pos_x_ + 15, pos_y_ - 15), sf::Color::Red));
    base_lines_.push_back( sf::Vertex( sf::Vector2f( pos_x_ + 15, pos_y_ - height_ + 15), sf::Color::Red));
}

// WindowTemp( 100, 50, view_->getHeight(), 0);


void WindowTemp::fillMarks()
{
    font_ = new sf::Font;
    if ( !font_->loadFromFile( "fonts/Avenir Next Condensed.ttc") )
    {
        throw new MY_EXCEPTION( "failed to load font", nullptr);
    }
    int temp_cur = 0;
    for ( int i = pos_y_ - 15; i > pos_y_ - height_ + 15; i -= 20 )
    {
        sf::Text text;
        text.setCharacterSize( 10);
        text.setFont( *font_);
        text.setString(std::to_string( temp_cur));
        text.setFillColor(sf::Color::Black);
        text.setPosition( pos_x_ + 1, i - 10);
        marks_.push_back( text);
        temp_cur += STEP_TEMP;
    }
}
