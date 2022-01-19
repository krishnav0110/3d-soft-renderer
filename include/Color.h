#pragma once

typedef union {
    int color;
    struct {
        unsigned char b, g, r, a;
    } RGBA;
} Color;

Color lerpColor(Color* c1, Color* c2, float t);