#include "Axis.h"

namespace Ceres
{
    Axis::Axis(Button up, Button down, Button left, Button right)
        :Up(up), Left(left), Down(down), Right(right)
    {}

    Axis::~Axis()
    {}
}