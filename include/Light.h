#pragma once

#ifndef _INC_LIGHT_
#define _INC_LIGHT_

#include "dllsupport.c"

#include "Color.h"
#include "Vector.h"

enum LightType { AMBIENT, DIRECTIONAL, POINT_LIGHT };

typedef struct {
    Vector3 position;
    Vector3 direction;
    Color color;
    enum LightType type;
    Vector3 attenuaton;
} Light;

void DLL initLight(Light* light, enum LightType type, Color color, Vector3 position, Vector3 direction, Vector3 attenuation);
void applyLight(Light* light, Vector3* pointPosition, Vector3* pointNormal, Color* lightAmount);

#endif