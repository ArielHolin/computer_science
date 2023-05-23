/*********************************************************************
* Description: Circle - inherits from The abstract class Shape 
               This is leaf as part of the composite design pattern. 
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_CIRCLE_HPP
#define ILRD_HRD_20_CIRCLE_HPP

#include "glut_utils.h"
#include "point.hpp"
#include "shape.hpp"


namespace hrd20
{

class Circle : public Shape 
{
public:
    explicit Circle(double _radius = 150, 
                    const ilrd::Point& _center = ilrd::Point(500, 500), 
                    double _angle = 0.0, 
                    COLORS _color = COLOR_WHITE);

    // generated cctor, dtor 

    virtual Circle& Draw();
    virtual Circle* Clone();
private:
    // copy assignment is blocked for the user - use clone instead 
    double m_radius;
};

} //namespae hrd20

#endif // ILRD_HRD_20_CIRCLE_HPP
