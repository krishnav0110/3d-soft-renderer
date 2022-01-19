#pragma once

#include "Vertex.h"
#include "Render.h"

void renderTriangle(Vertex* v1, Vertex* v2, Vertex* v3, RenderBuffer* renderBuffer);
void clipTriangle_Plane(Vertex* vertices, int* verticesCount, Vector3 planePoint, Vector3 planeNormal);
int clipTriangle(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* vertices);