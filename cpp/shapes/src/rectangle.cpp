/*******************************************************************************
 * rectangle.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include "rectangle.hpp"

namespace hrd20
{
Rectangle::Rectangle(double _width, double _height,
                    const ilrd::Point& _center, 
                    double _angle, 
                    COLORS _color) : Shape(_center, _angle, _color), 
                                     m_width(_width), m_height(_height)
{}

Rectangle& Rectangle::Draw()
{
    const double HALF = 1.0 / 2.0;
    const int NUM_OF_VERTX = 4;

    ilrd::Point newP1(GetCenter().GetX() + (HALF * m_width), 
                                        GetCenter().GetY() + (HALF * m_height));
    ilrd::Point newP2(GetCenter().GetX() + (HALF * m_width), 
                                        GetCenter().GetY() - (HALF * m_height));
    ilrd::Point newP3(GetCenter().GetX() - (HALF * m_width), 
                                        GetCenter().GetY() + (HALF * m_height));
    ilrd::Point newP4(GetCenter().GetX() - (HALF * m_width), 
                                        GetCenter().GetY() - (HALF * m_height));

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

Rectangle* Rectangle::Clone()
{
    return new Rectangle(*this);
}

}