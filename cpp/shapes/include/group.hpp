/*********************************************************************
* Description: Group - Inherits from the abstract class Shape. 
               This is the composite of the composite design pattern 
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21 
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_GROUP_HPP
#define ILRD_HRD_20_GROUP_HPP

#include <vector>

#include "glut_utils.h"
#include "point.hpp"

#include "shape.hpp"

namespace hrd20
{

class Group : public Shape 
{
public:
    explicit Group(const ilrd::Point& _center = ilrd::Point(500, 500), 
                   double _angle = 0.0, 
                   COLORS _color = COLOR_WHITE);
  
    // generated cctor, dtor 
     
    virtual Group& Move(double _xOffset, double _yOffset);
    virtual Group& Rotate(double _angle);
    virtual Group& Revolve(const ilrd::Point& _pivot, double _angle);
    virtual Group& SetColor(COLORS _newColor);
    virtual Group& Draw();
    virtual Group* Clone(); 
    
    Group& Add(Shape* shape);
    Group& Remove(Shape* shape);

private:
    // copy assignment is blocked for the user - use clone instead 
    std::vector<Shape*> m_shapes;
};

} //namespae hrd20

#endif // ILRD_HRD_20_GROUP_HPP
