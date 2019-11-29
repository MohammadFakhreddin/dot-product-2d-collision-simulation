#pragma once

#include <math.h>

template<typename T>
T constexpr _piTemplate = (T)3.14159265358979323846264338327950288419;

float PI_FLOAT = _piTemplate<float>;
double PI_DOUBLE = _piTemplate<double>;
