#include "windows_manager/abutton.hpp"

AButton::AButton( int init_x, int init_y)
    :   x_( init_x), y_( init_y)
{

}

AButton::~AButton()
{

}

int AButton::getX() const
{
    return x_;
}

int AButton::getY() const
{
    return y_;
}
