/*********************************************************************
* Description: Shape - test
* Name: HRD20 - Ariel
* Reviewer - Nisan
* Date: 22.12.21
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cmath>

#include "point.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "group.hpp"

#include "glut_utils.h"

using namespace hrd20;


int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

ilrd::Point pivot1(0,0);
ilrd::Point pivot2(200,200);
ilrd::Point pivot3(400,400);
ilrd::Point pivot7(800,800);
ilrd::Point pivot4(600,600);
ilrd::Point pivot5(1000,1000);
ilrd::Point pivot6(500,500);

Square square(100, pivot7);
Square square1(100, ilrd::Point(750,750), 0, COLOR_BLUE);
Square square2(100, ilrd::Point(700,700), 0 , COLOR_MAGENTA);
Square square3(100, ilrd::Point(650,650), 0, COLOR_GREEN);

Square squareup(200, pivot5);
Square squaredown(200, pivot1);
Triangle triangle1(100, pivot3);
Triangle triangle2(50, pivot6);
Triangle triangle3(50, pivot6);
Triangle triangle4(25, ilrd::Point(500,500));

Rectangle rectangle1(50, 75, ilrd::Point(700,250));
Triangle triangle5(50, ilrd::Point(800,250));

// Rectangle rectangle2(100, 200, ilrd::Point(750,200));
// Rectangle rectangle3(100, 200, ilrd::Point(800,300));

Circle circle0(50, pivot6, 0, COLOR_GREEN);
Circle circle1(50, pivot6, 0, COLOR_RED);
Circle circle2(100, pivot6, 0, COLOR_YELLOW);
Circle circle3(150, pivot6, 0, COLOR_BLUE);
Circle circle4(200, pivot6, 0, COLOR_RED);
Circle circle5(250, pivot6, 0, COLOR_YELLOW);
Circle circle6(300, pivot6, 0, COLOR_BLUE);

Group group;
Group group0;
Group group1;
Group group2;
Group group3(ilrd::Point(750,250));

Line lineup(1000, ilrd::Point(500,900), 0, COLOR_MAGENTA);
Line linedown(1000, ilrd::Point(500,100), 0, COLOR_MAGENTA);


static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop();

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{

    squareup.Draw();
    squaredown.Draw();

    lineup.Draw();
    linedown.Draw();

    group0.Add(&circle0);
    group0.Draw();
    
    group.Add(&circle1);
    group.Draw();

    group1.Add(&circle2);
    group1.Draw();

    group2.Add(&circle3);
    group2.Draw();
    
    group3.Add(&rectangle1);
    group3.Add(&triangle5);
    group3.Draw();
    group3.Rotate(0.01);

    triangle3.Draw();
    triangle2.Draw();
    triangle4.Draw();

    square.Draw();
    square1.Draw();
    square2.Draw();
    square3.Draw();
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static int TimerFunction()
{
    xCircle += 1;
    yCircle += 1;

    triangle4.Move(0,-10);
    squareup.Move(-1,-1);
    squaredown.Move(1,1);
    
    group0.Rotate(M_PI);
    group.Rotate(M_PI_2);
    group1.Rotate(M_PI_2);
    group2.Rotate(M_PI);

    triangle3.Rotate(M_PI);
    triangle2.Rotate(M_PI_2);

    square.Revolve(pivot6, 0.01);
    square1.Revolve(pivot6, 0.01);
    square2.Revolve(pivot6, 0.01);
    square3.Revolve(pivot6, 0.01);

    return 1;  /* draw */
}