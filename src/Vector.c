#pragma once

#include <math.h>
#include "Vector.h"

Vector3 Translate(Vector3* vec, Vector3* translate){
    Vector3 toReturn;
    toReturn.x = vec -> x + translate -> x;
    toReturn.y = vec -> y + translate -> y;
    toReturn.z = vec -> z + translate -> z;
    return toReturn;
}

Vector3 Rotate(Vector3* vec, Vector3* rotation){
    Vector3 toReturn;
    toReturn.x = vec->x * (cos(rotation->z) * cos(rotation->y)) + 
				 vec->y * (cos(rotation->z) * sin(rotation->y) * sin(rotation->x) - sin(rotation->z) * cos(rotation->x)) +
				 vec->z * (cos(rotation->z) * sin(rotation->y) * cos(rotation->x) + sin(rotation->z) * sin(rotation->x));

	toReturn.y = vec->x * (sin(rotation->z) * cos(rotation->y)) +
				 vec->y * (sin(rotation->z) * sin(rotation->y) * sin(rotation->x) + cos(rotation->z) * cos(rotation->x)) +
				 vec->z * (sin(rotation->z) * sin(rotation->y) * cos(rotation->x) - cos(rotation->z) * sin(rotation->x));

	toReturn.z = vec->x * (-sin(rotation->y)) +
				 vec->y * (cos(rotation->y) * sin(rotation->x)) +
				 vec->z * (cos(rotation->y) * cos(rotation->x));
    return toReturn;
}

float distance(Vector3* vec1, Vector3* vec2){
    Vector3 dist = {vec2->x - vec1->x, vec2->y - vec1->y, vec2->z - vec1->z};
    return sqrtf(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
}

Vector3 normalize(Vector3* vec){
    float magnitude = sqrtf(vec -> x * vec -> x + vec -> y * vec -> y + vec -> z * vec -> z);
    Vector3 toReturn;
    toReturn.x = vec -> x / magnitude;
    toReturn.y = vec -> y / magnitude;
    toReturn.z = vec -> z / magnitude;
    return toReturn;
}

float dotProduct(Vector3* vec1, Vector3* vec2){
    return vec1 -> x * vec2 -> x + vec1 -> y * vec2 -> y + vec1 -> z * vec2 -> z;
}

Vector3 calcNormal(Vector3* a, Vector3* b, Vector3* c){
    Vector3 vec1 = {b->x - a->x, b->y - a->y, b->z - a->z};
    Vector3 vec2 = {c->x - a->x, c->y - a->y, c->z - a->z};

    Vector3 normal;
    normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
    normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
    normal.z = vec1.x * vec2.y - vec1.y * vec2.x;

    //normalizing the vector
    float magnitude = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= magnitude;
    normal.y /= magnitude;
    normal.z /= magnitude;
    return normal;
}

Vector3 planeLineIntersection(Vector3* point1, Vector3* point2, Vector3* planePoint, Vector3* planeNormal){
    Vector3 lineVector = {point2->x - point1->x, point2->y - point1->y, point2->z - point1->z};
    lineVector = normalize(&lineVector);
    Vector3 planeToLineVector = {planePoint->x - point1->x, planePoint->y - point1->y, planePoint->z - point1->z};

    float scalar_k = dotProduct(&planeToLineVector, planeNormal) / dotProduct(&lineVector, planeNormal);

    Vector3 toReturn = {point1->x + scalar_k * lineVector.x, point1->y + scalar_k * lineVector.y, point1->z + scalar_k * lineVector.z};
    return toReturn;
}