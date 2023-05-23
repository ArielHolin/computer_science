/*********************************************************************
* Description: Shape - This is the abstract class that is used as part of 
                       the composite design pattern. 
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_SHAPE_HPP
#define ILRD_HRD_20_SHAPE_HPP

#include "point.hpp"
#include "glut_utils.h"

namespace hrd20
{

class Shape 
{
public:
    explicit Shape(const ilrd::Point& _center = ilrd::Point(500, 500), 
                   double _angle = 0.0, \
                   COLORS _color = COLOR_WHITE);
    
    //generated cctor
    virtual ~Shape() = 0;
    
    virtual Shape* Clone() = 0; 

    virtual Shape& Move(double _xOffset, double _yOffset); 
    virtual Shape& Rotate(double _angle);
    virtual Shape& Revolve(const ilrd::Point& _pivot, double _angle);
    virtual Shape& SetColor(COLORS _color);
    virtual Shape& Draw() = 0;
    
protected:
    ilrd::Point GetCenter() const;
    double GetAngle() const;
    COLORS GetColor() const;

private:
    // copy assignment is blocked for the user - use clone instead 
    Shape& operator=(const Shape& _other);
   
    // members
    ilrd::Point m_center;
    double m_angle;
    COLORS m_color;
};

} //namespae hrd20

#endif //ILRD_HRD_20_SHAPE_HPP
