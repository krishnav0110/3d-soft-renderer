#pragma once

#include "settings.h"
#include "EngineBase.h"

float getZ0(){
    return (WIDTH / 2) / (tanf(FOV / 2 * PI / 180));
}

Vector3 getProjectedPoint(Vector3* vec){
    Vector3 projectedPoint;
    float z = getZ0() / (getZ0() + vec -> z);
    projectedPoint.x = vec -> x * z;
    projectedPoint.y = vec -> y * z;
    projectedPoint.z = vec -> z;
    return projectedPoint;
}

Vector3 translateOrigin(Vector3* vec){
    float tx = WIDTH / 2;
    float ty = HEIGHT / 2;
    Vector3 toReturn;
    toReturn.x = vec -> x + tx;
    toReturn.y = vec -> y + ty;
    toReturn.z = vec -> z;
    return toReturn;
}

Vector3 applyPerspective(Vector3* vec){
    Vector3 toReturn;
    toReturn = getProjectedPoint(vec);
    toReturn = translateOrigin(&toReturn);
    return toReturn;
}