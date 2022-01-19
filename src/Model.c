#pragma once

#include <malloc.h>

#include "Model.h"

void initModel(Model* model, int noTriangles, int noVertices){
    model -> position    = (Vector3){0, 0, 0};
    model -> noTriangles = noTriangles;
    model -> noVertices  = noVertices;
    model -> vertices    = calloc(noVertices, sizeof(*model -> vertices));
    model -> index       = calloc(noTriangles * 3, sizeof(*model -> index));
    model -> rotation    = (Vector3){0, 0, 0};
}

void deleteModel(Model* model){
    free(model -> vertices);
    free(model -> index);
}