/*******************************************************************************
 * line.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include "line.hpp"

namespace hrd20
{

Line::Line(double _length, const ilrd::Point& _center, double _angle, 
           COLORS _color) : Shape(_center, _angle, _color), m_length(_length) {}


Line& Line::Draw()
{
    const int NUM_OF_VERTX = 2;
    
    ilrd::Point newP1(GetCenter().GetX() + 0.5*m_length, GetCenter().GetY());
    ilrd::Point newP2(GetCenter().GetX() - 0.5*m_length, GetCenter().GetY());
    newP1.Revolve(GetCenter(), GetAngle());
    newP2.Revolve(GetCenter(), GetAngle());
    
    DrawPolygon(GetColor(), NUM_OF_VERTX, static_cast<int>(newP1.GetX()), 
                static_cast<int>(newP1.GetY()), static_cast<int>(newP2.GetX()), 
                static_cast<int>(newP2.GetY()));

    return *this;
}

Line* Line::Clone()
{
    return new Line(*this);
}
}