#pragma once

#ifndef _INC_MODEL_
#define _INC_MODEL_

#include "dllsupport.c"

#include <malloc.h>
#include "Render.h"
#include "Vertex.h"

typedef struct {
    Vector3 position;
    Vector3 rotation;
    int triangleCount;
    int vertexCount;
    Vertex* vertices;
    unsigned char* index;
} Model;

void DLL initModel(Model* model, int triangleCount, int vertexCount);
void DLL deleteModel(Model* model);

#endif