/*******************************************************************************
 * group.cpp
 * Author: Ariel
 * Reviewer: Nisan
 * ****************************************************************************/

#include <vector>
#include <cstddef>

#include "group.hpp"

namespace hrd20
{

Group::Group(const ilrd::Point& _center, 
                   double _angle, 
                   COLORS _color) : Shape(_center, _angle, _color)
{}

Group& Group::Move(double _xOffset, double _yOffset)
{
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->Move(_xOffset, _yOffset);
    }

    return *this;
}

Group& Group::Rotate(double _angle)
{
    ilrd::Point center(GetCenter());

    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->Rotate(_angle);
    }

    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->Revolve(center, _angle);
    }

    return *this;
}

Group& Group::Revolve(const ilrd::Point& _pivot, double _angle)
{
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->Revolve(_pivot, _angle);
    }

    return *this;
}

Group& Group::SetColor(COLORS _newColor)
{
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->SetColor(_newColor);
    }

    return *this;
}

Group& Group::Draw()
{
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->Draw();
    }

    return *this;
}

Group* Group::Clone()
{
    return new Group(*this);
}

Group& Group::Add(Shape* shape)
{
    m_shapes.push_back(shape);

    return *this;
}

Group& Group::Remove(Shape* shape)
{
    return *this;
}
}