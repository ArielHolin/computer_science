/*******************************************************************************
 * triangle.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include <cmath>

#include "triangle.hpp"

namespace hrd20
{
Triangle::Triangle(double _edge, const ilrd::Point& _center, double _angle, 
                   COLORS _color) : Shape(_center, _angle, _color), m_edge(_edge) 
{}

double Triangle::GetPerp() const
{
    return sqrt(pow(m_edge, 2) - pow(m_edge / 2, 2));
}

Triangle& Triangle::Draw()
{
    const double PERP = GetPerp();
    const double TWO_THIRDS = 2.0 / 3.0;
    const double ONE_THIRD = 1.0 / 3.0;
    
    const int NUM_OF_VERTX = 3;
    
    ilrd::Point newP1(GetCenter().GetX(), GetCenter().GetY() - TWO_THIRDS * PERP);
    ilrd::Point newP2(GetCenter().GetX() + (m_edge / 2), GetCenter().GetY() + 
                                                              ONE_THIRD * PERP);
    ilrd::Point newP3(GetCenter().GetX() - (m_edge / 2), GetCenter().GetY() + 
                                                              ONE_THIRD * PERP);

    newP1.Revolve(GetCenter(), GetAngle());
    newP2.Revolve(GetCenter(), GetAngle());
    newP3.Revolve(GetCenter(), GetAngle());
    
    DrawPolygon(GetColor(), NUM_OF_VERTX, static_cast<int>(newP1.GetX()), 
                static_cast<int>(newP1.GetY()), static_cast<int>(newP2.GetX()), 
                static_cast<int>(newP2.GetY()), static_cast<int>(newP3.GetX()),
                static_cast<int>(newP3.GetY()));

    return *this;
}

Triangle* Triangle::Clone()
{
    return new Triangle(*this);
}
}