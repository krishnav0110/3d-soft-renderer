#pragma once

#include <math.h>

#define PI 3.142857

typedef struct {
    float x, y, z;
} Vector3;

Vector3 normalize(Vector3* vec){
    float mag = sqrtf(vec -> x * vec -> x + vec -> y * vec -> y + vec -> z * vec -> z);
    Vector3 toReturn;
    toReturn.x = vec -> x / mag;
    toReturn.y = vec -> y / mag;
    toReturn.z = vec -> z / mag;
    return toReturn;
}

float dotProduct(Vector3* vec1, Vector3* vec2){
    return vec1 -> x * vec2 -> x + vec1 -> y * vec2 -> y + vec1 -> z * vec2 -> z;
}

Vector3 calcNormal(Vector3* a, Vector3* b, Vector3* c){
    Vector3 normal, vec1, vec2;
    vec1.x = b -> x - a -> x;
    vec1.y = b -> y - a -> y;
    vec1.z = b -> z - a -> z;

    vec2.x = c -> x - a -> x;
    vec2.y = c -> y - a -> y;
    vec2.z = c -> z - a -> z;

    normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
    normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
    normal.z = vec1.x * vec2.y - vec1.y * vec2.x;

    //normalizing the vector
    float mag = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= mag;
    normal.y /= mag;
    normal.z /= mag;
    return normal;
}

Vector3 Translate(Vector3* vec, Vector3* translate){
    Vector3 toReturn;
    toReturn.x = vec -> x + translate -> x;
    toReturn.y = vec -> y + translate -> y;
    toReturn.z = vec -> z + translate -> z;
    return toReturn;
}

Vector3 rotateX(Vector3* vec3, float angle){
    Vector3 toReturn;
    angle *= PI / 180;
    toReturn.x = vec3 -> x;
    toReturn.y = vec3 -> y * cosf(angle) - vec3 -> z * sinf(angle);
    toReturn.z = vec3 -> y * sinf(angle) + vec3 -> z * cosf(angle);
    return toReturn;
}

Vector3 rotateY(Vector3* vec3, float angle){
    Vector3 toReturn;
    angle *= PI / 180;
    toReturn.x = vec3 -> x * cosf(angle) - vec3 -> z * sinf(angle);
    toReturn.y = vec3 -> y;
    toReturn.z = vec3 -> x * sinf(angle) + vec3 -> z * cosf(angle);
    return toReturn;
}

Vector3 rotateZ(Vector3* vec3, float angle){
    Vector3 toReturn;
    angle *= PI / 180;
    toReturn.x = vec3 -> x * cosf(angle) - vec3 -> y * sinf(angle);
    toReturn.y = vec3 -> x * sinf(angle) + vec3 -> y * cosf(angle);
    toReturn.z = vec3 -> z;
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
	toReturn.z = vec->x * (- sin(rotation->y)) +
				 vec->y * (cos(rotation->y) * sin(rotation->x)) +
				 vec->z * (cos(rotation->y) * cos(rotation->x));
    return toReturn;
}

Vector3 planeLineIntersection(Vector3* point1, Vector3* point2, Vector3* planePoint, Vector3* planeNormal){
    Vector3 lineVector = (Vector3){point2->x - point1->x, point2->y - point1->y, point2->z - point1->z};
    lineVector = normalize(&lineVector);
    Vector3 planeToLineVector = (Vector3){planePoint->x - point1->x, planePoint->y - point1->y, planePoint->z - point1->z};

    float scalar_k = dotProduct(&planeToLineVector, planeNormal) / dotProduct(&lineVector, planeNormal);

    Vector3 toReturn = (Vector3){point1->x + scalar_k * lineVector.x, point1->y + scalar_k * lineVector.y, point1->z + scalar_k * lineVector.z};
    return toReturn;
}