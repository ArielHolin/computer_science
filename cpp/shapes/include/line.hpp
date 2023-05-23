/*********************************************************************
* Description: Line - inherits from the Shape abstract Class. 
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_LINE_HPP
#define ILRD_HRD_20_LINE_HPP

#include "glut_utils.h"
#include "point.hpp"

#include "shape.hpp"


namespace hrd20
{

class Line : public Shape 
{
public:
    explicit Line(double _length = 150, 
                  const ilrd::Point& _center = ilrd::Point(500, 500), 
                  double _angle = 0.0, 
                  COLORS _color = COLOR_WHITE);
    
    virtual Line& Draw();
    virtual Line* Clone();

private:
    // copy assignment is blocked for the user - use clone instead 
    double m_length;
};

} //namespae hrd20

#endif // ILRD_HRD_20_LINE_HPP