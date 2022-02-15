#pragma once

#ifndef _INC_TRIANGLE_
#define _INC_TRIANGLE_

#include "Render.h"
#include "Vertex.h"

void renderTriangle(Vertex* v1, Vertex* v2, Vertex* v3, RenderBuffer* renderBuffer);

int clipTriangleZ(Vertex* vertices);
int clipTriangle(Vertex* vertices, int verticesCount);

#endif