/*******************************************************************************
 * square.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include "square.hpp"

namespace hrd20
{
Square::Square(double _edge, 
               const ilrd::Point& _center, 
               double _angle, 
               COLORS _color) : Shape(_center, _angle, _color), m_edge(_edge)
{}

Square& Square::Draw()
{
    const double HALF_EDGE = (1.0 / 2.0) * m_edge;
    const int NUM_OF_VERTX = 4;

    ilrd::Point newP1(GetCenter().GetX() + HALF_EDGE, 
                                                GetCenter().GetY() + HALF_EDGE);
    ilrd::Point newP2(GetCenter().GetX() + HALF_EDGE, 
                                                GetCenter().GetY() - HALF_EDGE);
    ilrd::Point newP3(GetCenter().GetX() - HALF_EDGE, 
                                                GetCenter().GetY() + HALF_EDGE);
    ilrd::Point newP4(GetCenter().GetX() - HALF_EDGE, 
                                                GetCenter().GetY() - HALF_EDGE);

    newP1.Revolve(GetCenter(), GetAngle());
    newP2.Revolve(GetCenter(), GetAngle());
    newP3.Revolve(GetCenter(), GetAngle());
    newP4.Revolve(GetCenter(), GetAngle());

    DrawPolygon(GetColor(), NUM_OF_VERTX, static_cast<int>(newP1.GetX()), 
                static_cast<int>(newP1.GetY()), static_cast<int>(newP2.GetX()), 
                static_cast<int>(newP2.GetY()), static_cast<int>(newP4.GetX()),
                static_cast<int>(newP4.GetY()), static_cast<int>(newP3.GetX()),
                static_cast<int>(newP3.GetY()));

    return *this;
}

Square* Square::Clone()
{
    return new Square(*this);
}
}

