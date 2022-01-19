#pragma once

#include "Color.h"

Color lerpColor(Color* c1, Color* c2, float t){
    Color toReturn;
    toReturn.RGBA.r = (unsigned char)((c2->RGBA.r - c1->RGBA.r) * t + c1->RGBA.r);
    toReturn.RGBA.g = (unsigned char)((c2->RGBA.g - c1->RGBA.g) * t + c1->RGBA.g);
    toReturn.RGBA.b = (unsigned char)((c2->RGBA.b - c1->RGBA.b) * t + c1->RGBA.b);
    toReturn.RGBA.a = (unsigned char)((c2->RGBA.a - c1->RGBA.a) * t + c1->RGBA.a);
    return toReturn;
}