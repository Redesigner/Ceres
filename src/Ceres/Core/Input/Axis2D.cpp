#include "Axis2D.h"

namespace Ceres
{
    Axis2D::Axis2D(Button up, Button down, Button left, Button right)
        :Up(up), Left(left), Down(down), Right(right)
    {}

    Axis2D::~Axis2D()
    {}
}