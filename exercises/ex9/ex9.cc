/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <cstdlib>   // for EXIT_FAILURE, EXIT_SUCCESS
#include "Vector.h"  // for Vector objects

using namespace vector333;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    cout << endl << "Beginning tests" << endl << endl;

    // constructor tests
    cout << "Constructor tests" << endl << endl;
    cout << "  Default constructor" << endl;
    Vector x = Vector();  // default constructor test
    cout << "    result of: Vector z = Vector();" << endl;
    cout << "    x = " << x << endl;

    cout << "  Overloaded constructor" << endl;
    Vector y = Vector(1.0, 2.0, 3.0);  // overloaded constructor test
    cout << "    result of: Vector y = Vector(1.0, 2.0, 3.0);" << endl;
    cout << "    y = " << y << endl;

    cout << "  Copy constructor" << endl;
    Vector z = y;  // copy constructor test
    cout << "    result of: Vector z = y;" << endl;
    cout << "    z = " << z << endl;

    // accessor operator tests
    cout << endl << "Accessor tests" << endl << endl;
    z = Vector(-3.0, 0, 4.2);
    cout << "z = " << z << endl << endl;

    cout << "  get_x()" << endl;
    double i = z.get_x();
    cout << "    result of: i = z.get_x();" << endl;
    cout << "    i = " << i << endl;

    cout << "  get_y()" << endl;
    i = z.get_y();
    cout << "    result of: i = z.get_y();" << endl;
    cout << "    i = " << i << endl;

    cout << "  get_z()" << endl;
    i = z.get_z();
    cout << "    result of: i = z.get_z();" << endl;
    cout << "    i = " << i << endl;

    // assignment operator tests
    cout << endl << "Assignment tests" << endl << endl;

    cout << "  operator=:" << endl;
    z = x;  // assignment operator= test (also uses copy constructor)
    cout << "    result of: Vector z = x;" << endl;
    cout << "    z = " << z << endl;

    cout << "  operator+=:" << endl;
    y += Vector(1, 1, 1);  // assignment operator+= test
    cout << "    result of: Vector y += Vector(1,1,1);" << endl;
    cout << "    y = " << y << endl;

    cout << "  operator-=:" << endl;
    y -= Vector(1, 1, 1);  // assignment operator-= test
    cout << "    result of: y -= Vector(1,1,1);" << endl;
    cout << "    y = " << y << endl;

    // non-member functions tests
    cout << endl << "Non-member function tests" << endl << endl;

    cout << "  operator+:" << endl;
    Vector a = (Vector(1, 1, 1) + Vector(1, 1, 1));  // operator+ test
    cout << "    result of: a = (Vector(1,1,1) + Vector(1,1,1));" << endl;
    cout << "    a = " << a << endl;

    cout << "  operator-:" << endl;
    Vector b = (Vector(3, 0, 2) - Vector(6, -5, 1));  // operator- test
    cout << "    result of: b = (Vector(3,0,2) - Vector(6,-5,1));" << endl;
    cout << "    b = " << b << endl;

    cout << "  operator*, dot product:" << endl;
    double c = (Vector(1, 1, 1) * Vector(2, 2, 2));  // operator* test
    cout << "    result of: c = (Vector(1,1,1) * Vector(2,2,2));" << endl;
    cout << "    c = " << c << endl;

    cout << "  operator*, scalar multiplication:" << endl;
    Vector d = (Vector(2, -3, 0) * 2);  // operator* test
    cout << "    result of: d = (Vector(2,-3,0) * 2);" << endl;
    cout << "    d = " << d << endl;

    cout << endl << "End of tests" << endl << endl;

    return EXIT_SUCCESS;
}
