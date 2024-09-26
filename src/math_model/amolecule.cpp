#include <math_model/amolecule.hpp>
#include <chrono>
#include <cassert>


AMolecule::AMolecule( Vector init_move_vec, float init_radius, float init_weight)
    :   move_vec_( init_move_vec), last_draw_( getTime()), radius_( init_radius), weight_( init_weight) {}


void AMolecule::move( CoordinateSys *c_sys)
{
    assert( c_sys );

    auto now = getTime();
    auto elapsed = now - last_draw_;

    VectorCoordinates coord = move_vec_.getCoordinates();

    double new_x_0 = coord.x_0 + ( coord.x - coord.x_0) * elapsed / 1000;
    double new_y_0 = coord.y_0 + ( coord.y - coord.y_0) * elapsed / 1000;

    ReflectData data = { { (float) new_x_0, (float) new_y_0}, this->getCenter(), LocationNormal, c_sys};
    data.status = isOutOfTheWindow( data);
    if ( data.status != LocationNormal )
    {
        this->move_vec_ = reflectFromWall( data);
        VectorCoordinates vec = move_vec_.getCoordinates();
        new_x_0 = vec.x_0;
        new_y_0 = vec.y_0;
    }
    move_vec_.move( new_x_0, new_y_0);

    last_draw_ = now;
}


long long getTime()
{
    auto now = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch()).count();
}


LocationStatus AMolecule::isOutOfTheWindow(  ReflectData &data)
{
    PointCoordinates point = data.c_sys->translateToPixels( data.new_center);

    if ( point.x > data.c_sys->getWidth() )
        return LocationRightEscape;
    if ( point.y > data.c_sys->getHeight() )
        return LocationDownEscape;
    if ( point.x < 0 )
        return LocationLeftEscape;
    if ( point.y < 0 )
        return LocationUpEscape;
    return LocationNormal;
}


Vector AMolecule::reflectFromWall( ReflectData &data)
{
    PointCoordinates point = findReflectPoint( data);
    VectorCoordinates reflected = {};
    VectorCoordinates cur = this->move_vec_.getCoordinates();
    reflected.x_0 = point.x;
    reflected.y_0 = point.y;

    switch ( data.status )
    {
        case LocationNormal:
            return move_vec_;
        case LocationDownEscape:
        case LocationUpEscape:
            reflected.y = -(cur.y - cur.y_0) + cur.y_0;
            reflected.x = cur.x;
            break;
        case LocationRightEscape:
        case LocationLeftEscape:
            reflected.y = cur.y;
            reflected.x = -(cur.x - cur.x_0) + cur.x_0;
            break;
        default:
            assert( 0 );
    }
    return Vector( reflected.x, reflected.y, reflected.x_0, reflected.y_0);
}


PointCoordinates AMolecule::findReflectPoint( ReflectData &data)
{
    PointCoordinates coord_old = data.c_sys->translateToPixels( data.old_center);
    PointCoordinates coord_new = data.c_sys->translateToPixels( data.new_center);

    double x_0 = 0;
    double y_0 = 0;
    double scale = 0;

    switch ( data.status )
    {
        case LocationLeftEscape:
            x_0 = 0;
            scale = ( fabs( coord_old.x - coord_new.x) < 1e-8 ) ? 0 : fabs( (coord_old.x - x_0) / (coord_old.x - coord_new.x));
            y_0 = (coord_new.y - coord_old.y) * scale + coord_old.y;
            break;
        case LocationRightEscape:
            x_0 = data.c_sys->getWidth();
            scale = ( fabs( coord_old.x - coord_new.x) < 1e-8 ) ? 0 : fabs( (coord_old.x - x_0) / (coord_old.x - coord_new.x));
            y_0 = (coord_new.y - coord_old.y) * scale + coord_old.y;
            break;
        case LocationUpEscape:
            y_0 = 0;
            scale = ( fabs( coord_old.y - coord_new.y) < 1e-8 ) ? 0 : fabs( (coord_old.y - y_0) / (coord_old.y - coord_new.y));
            x_0 = (coord_new.x - coord_old.x) * scale + coord_old.x;
            break;
        case LocationDownEscape:
            y_0 = data.c_sys->getHeight();
            scale = ( fabs( coord_old.y - coord_new.y) < 1e-8 ) ? 0 : fabs( (coord_old.y - y_0) / (coord_old.y - coord_new.y));
            x_0 = (coord_new.x - coord_old.x) * scale + coord_old.x;
            break;
        case LocationNormal:
        default:
            assert( 0 );
    }

    return data.c_sys->translateFromPixels( {(float) x_0, (float) y_0});
}


PointCoordinates AMolecule::getCenter() const
{
    VectorCoordinates coord = move_vec_.getCoordinates();

    return { (float) coord.x_0, (float) coord.y_0};
}
