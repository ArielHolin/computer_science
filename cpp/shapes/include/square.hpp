/*********************************************************************
* Description: Square - Inherits from the Shape Abstract Class 
               This is leaf in the Composite Design pattern
* Name: Ariel
* Reviewer - Nisan
* Date: 20.12.21
* Versions: 1.0
* 1.0 - ready for review
* 1.1 - Approved By Itizik 
*********************************************************************/
#ifndef ILRD_HRD_20_SQUARE_HPP
#define ILRD_HRD_20_SQUARE_HPP

#include "glut_utils.h"

#include "point.hpp"
#include "shape.hpp"

namespace hrd20
{

class Square : public Shape 
{
public:
    explicit Square(double _edge = 150, 
                    const ilrd::Point& _center = ilrd::Point(500, 500), 
                    double _angle = 0.0, 
                    COLORS _color = COLOR_WHITE);

    // generated cctor , dtor 

    virtual Square& Draw();
    virtual Square* Clone();

private:
    // copy assignment is blocked for the user - use clone instead 
    double m_edge;
};

} //namespae hrd20

#endif //ILRD_HRD_20_SQUARE_HPP