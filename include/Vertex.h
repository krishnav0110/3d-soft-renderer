#pragma once

#include "Vector.h"
#include "Color.h"

typedef struct {
    Vector3 position;
    //Vector3 tex;
    Vector3 projectedPoint;
    Vector3 normal;
    Color color;
} Vertex;

void initVertex(Vertex* vertex, Vector3 position);