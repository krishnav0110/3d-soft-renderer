#pragma once

#include "Vector.h"
#include "Color.h"

enum LightType { AMBIENT, DIRECTIONAL };

typedef struct {
    Vector3 position;
    Vector3 direction;
    Color color;
    enum LightType type;
    int length;
} Light;

void initLight(Light* light, enum LightType type, Color color, Vector3 direction, Vector3 position, int length);
void applyLight(Vector3* normal, Color* lightAmount, Light* light);