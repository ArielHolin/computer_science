/*********************************************************************
* Description: Triangle Class - inherits from the Shape abstract class
               note that we only support Equilateral triangle.  
* Name: Ariel 
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_TRIANGLE_HPP
#define ILRD_HRD_20_TRIANGLE_HPP

#include "point.hpp" // ilrd::Point
#include "shape.hpp" // Shape
#include "glut_utils.h" // Colors

namespace hrd20 
{


class Triangle:public Shape
{
public:
    explicit Triangle(double _edge = 150, 
                      const ilrd::Point& _center = ilrd::Point(500, 500), 
                      double _angle = 0.0, 
                      COLORS _color = COLOR_WHITE);
    
    // genereted cctor, dtor 
    
    virtual Triangle& Draw();
    virtual Triangle* Clone();

private:
    // copy assignment is blocked for the user - use clone instead 
    double m_edge;
    double GetPerp() const;

};

}//end of hdr20 namespace
#endif // ILRD_HRD_20_TRIANGLE_HPP