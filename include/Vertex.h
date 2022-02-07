#pragma once

#ifndef _INC_VERTEX_
#define _INC_VERTEX_

#include "dllsupport.c"
#include "Vector.h"
#include "Color.h"

typedef struct {
    Vector3 position;
    //Vector3 tex;
    Vector3 projectedPoint;
    Vector3 normal;
    Color color;
} Vertex;

void DLL initVertex(Vertex* vertex, Vector3 position);

#endif