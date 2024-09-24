#include "coor_sys.hpp"
#include <type_traits>

PointCoordinates CoordinateSys::translateToPixels( const PointCoordinates &point) const
{
    float x = point.x + x_center_;
    float y = y_center_ - point.y;

    return {x, y};
}

PointCoordinates CoordinateSys::translateFromPixels( const PointCoordinates &point) const
{
    float x = point.x - x_center_;
    float y = -(point.y - y_center_);

    return {x, y};
}


PointCoordinates CoordinateSys::translateToPixels( float x, float y)
{
    float w_x = x + x_center_;
    float w_y = y_center_ - y;

    return {w_x, w_y};
}


float CoordinateSys::getWidth() const
{
    return w_width_;
}


float CoordinateSys::getHeight() const
{
    return w_height_;
}


float CoordinateSys::getXCenter() const
{
    return x_center_;
}


float CoordinateSys::getYCenter() const
{
    return y_center_;
}
