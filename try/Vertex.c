#pragma once

#include "Vector.c"
#include "Color.c"

typedef struct {
    Vector3 position;
    //Vector3 tex;
    Vector3 projectedPoint;
    Vector3 normal;
    Color color;
} Vertex;

void initVertex(Vertex* vertex, Vector3 position){
    vertex -> position = position;
    //vertex -> tex = tex;
    vertex -> color = (Color){0xFFFFFFFF};
    vertex -> normal = (Vector3){0, 0, 0};
}