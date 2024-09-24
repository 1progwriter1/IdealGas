#ifndef COORDINATE_SYSTEM_FUNCTIONS
#define COORDINATE_SYSTEM_FUNCTIONS

struct PointCoordinates
{
    float x;
    float y;
};

class CoordinateSys
{
    float x_center_;
    float y_center_;

    float w_width_;
    float w_height_;

public:
    CoordinateSys( float init_w_width, float init_w_height)
        : x_center_( init_w_width / 2), y_center_( init_w_height / 2), w_width_( init_w_width), w_height_( init_w_height) {};
    ~CoordinateSys() {};

    PointCoordinates translateToPixels( float x, float y);
    PointCoordinates translateToPixels( const PointCoordinates &point) const;
    PointCoordinates translateFromPixels( const PointCoordinates &point) const;

    float getWidth() const;
    float getHeight() const;
    float getXCenter() const;
    float getYCenter() const;
};

#endif // COORDINATE_SYSTEM_FUNCTIONS
