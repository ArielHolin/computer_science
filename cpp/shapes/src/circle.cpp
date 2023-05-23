

#include "circle.hpp"

namespace hrd20
{
Circle::Circle(double _radius, 
               const ilrd::Point& _center, 
               double _angle, 
               COLORS _color): Shape(_center, _angle, _color), m_radius(_radius)
{}

Circle& Circle::Draw()
{
    DrawCircle(GetColor(), GetCenter().GetX(), GetCenter().GetY(), m_radius);
    
    return *this;
}

Circle* Circle::Clone()
{
    return new Circle(*this);
}
}