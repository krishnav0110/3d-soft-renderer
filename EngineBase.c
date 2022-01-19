#pragma once

Vector3 getProjectedPoint(Vector3* vec, Camera* camera){
    Vector3 projectedPoint;
    float z = camera -> z0 / (camera -> z0 + vec -> z);
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

Vector3 applyPerspective(Vector3* vec, Camera* camera){
    Vector3 toReturn;
    toReturn = getProjectedPoint(vec, camera);
    toReturn = translateOrigin(&toReturn);
    return toReturn;
}