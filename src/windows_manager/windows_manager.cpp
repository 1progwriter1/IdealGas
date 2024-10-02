#include <windows_manager/windows_manager.hpp>
#include <cassert>
#include <windows_manager/windows.hpp>


View::View( unsigned int init_width, unsigned int init_height, const char *label /*"hello"*/)
    :   main_window_( sf::VideoMode( init_width, init_height), label),
        width_( init_width), height_( init_height)
{}


View::~View()
{
    for ( const auto window : windows_ )
    {
        delete window;
    }
}


unsigned int View::getWidth() const
{
    return width_;
}


unsigned int View::getHeight() const
{
    return height_;
}


void View::display()
{
    main_window_.display();
}


void View::clear( sf::Color color /*sf::Color::Black*/)
{
    main_window_.clear( color);
}


void View::draw()
{
    for ( const auto &window : windows_ )
    {
        window->draw( main_window_);
    }
}


void View::addWindow( AWindow *new_window)
{
    assert( new_window );

    windows_.insert( windows_.end(), new_window);
}


sf::RenderWindow &View::getMainWindow()
{
    return main_window_;
}


AWindow *View::getWindow()
{
    return windows_.front();
}


const std::list<AWindow *> &View::getWindows() const
{
    return windows_;
}


ButtonsManager &View::getButtonsManager()
{
    return manager_;
}
