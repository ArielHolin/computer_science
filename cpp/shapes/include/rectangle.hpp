/*********************************************************************
* Description: Rectangle - inherits from the Shape abstract Class 
                This is leaf in the Composite Design pattern
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_RECTANGLE_HPP
#define ILRD_HRD_20_RECTANGLE_HPP

#include "glut_utils.h"
#include "point.hpp"
#include "shape.hpp"


namespace hrd20
{

class Rectangle : public Shape 
{
public:
    explicit Rectangle(double _width = 100, double _height = 200 ,
                       const ilrd::Point& _center = ilrd::Point(500, 500), 
                       double _angle = 0.0, 
                       COLORS _color = COLOR_WHITE);
    //generated ~, cctor
    
    virtual Rectangle& Draw();
    virtual Rectangle* Clone();
    
    
private:
    // copy assignment is blocked for the user - use clone instead 
    
    double m_width;
    double m_height;
};

} //namespae hrd20

#endif // ILRD_HRD_20_RECTANGLE_HPP


