#pragma once

#ifndef _INC_COLOR_
#define _INC_COLOR_

#include "dllsupport.c"

typedef union {
    int color;
    struct {
        unsigned char b, g, r, a;
    } RGBA;
} Color;

Color DLL lerpColor(Color* c1, Color* c2, float t);

#endif