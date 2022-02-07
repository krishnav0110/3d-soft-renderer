#pragma once

#include "Vertex.h"

void initVertex(Vertex* vertex, Vector3 position){
    vertex -> position = position;
    vertex -> projectedPoint = position;
    //vertex -> tex = tex;
    vertex -> color = (Color){0xFFFFFFFF};
    vertex -> normal = (Vector3){0, 0, 0};
}