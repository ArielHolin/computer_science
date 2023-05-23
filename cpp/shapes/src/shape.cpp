/*******************************************************************************
 * shape.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include "shape.hpp"

namespace hrd20
{

Shape::Shape(const ilrd::Point& _center, double _angle, COLORS _color) : 
                          m_center(_center), m_angle(_angle), m_color(_color) {}

Shape::~Shape() {}

Shape* Shape::Clone()
{}

Shape& Shape::Move(double _xOffset, double _yOffset)
{
    m_center.Move(m_center.GetX() + _xOffset, m_center.GetY() + _yOffset);

    return *this;
}

Shape& Shape::Rotate(double _angle)
{
    m_angle += _angle;

    return *this;
}

Shape& Shape::Revolve(const ilrd::Point& _pivot, double _angle)
{
    m_center.Revolve(_pivot, _angle);

    return *this;
}

Shape& Shape::SetColor(COLORS _color)
{
    m_color = _color;
}

ilrd::Point Shape::GetCenter() const
{
    return m_center;
}

double Shape::GetAngle() const
{
    return m_angle;
}

COLORS Shape::GetColor() const
{
    return m_color;
}

Shape& Shape::operator=(const Shape& _other)
{
    m_center = _other.m_center;
    m_angle = _other.m_angle;
    m_color = _other.m_color;

    return *this;
}

}