#pragma once

#include "Vertex.h"

typedef struct {
    Vector3 position;
    int noTriangles;
    int noVertices;
    Vertex* vertices;
    unsigned char* index;
    Vector3 rotation;
} Model;

void initModel(Model* model, int noTriangles, int noVertices);
void deleteModel(Model* model);