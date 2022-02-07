#pragma once

#ifndef _INC_VECTOR_
#define _INC_VECTOR_

#define PI 3.142857

typedef struct {
    float x, y, z;
} Vector3;

Vector3 Translate(Vector3* vec, Vector3* translate);
Vector3 Rotate(Vector3* vec, Vector3* rotation);

Vector3 normalize(Vector3* vec);
float dotProduct(Vector3* vec1, Vector3* vec2);

Vector3 calcNormal(Vector3* a, Vector3* b, Vector3* c);
Vector3 planeLineIntersection(Vector3* point1, Vector3* point2, Vector3* planePoint, Vector3* planeNormal);

#endif