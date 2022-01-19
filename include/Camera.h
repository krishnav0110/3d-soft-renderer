#pragma once

#include "Vector.h"

typedef struct {
    Vector3 position;
    Vector3 rotation;
    unsigned char upKeyPressed, leftKeyPressed, rightKeyPressed, downKeyPressed;
} Camera;

void initCamera(Camera* camera);
void updateCamera(Camera* camera, float delta);