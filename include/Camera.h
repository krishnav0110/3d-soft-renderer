#pragma once

#ifndef _INC_CAMERA_
#define _INC_CAMERA_

#define CAMERA_VELOCITY       200
#define CAMERA_ROTATION_SPEED 1

#include "dllsupport.c"
#include "Vector.h"

typedef struct {
    float z0;
    Vector3 position;
    Vector3 rotation;
    unsigned char W_KeyPressed, A_KeyPressed, S_KeyPressed, D_KeyPressed, up_KeyPressed, down_KeyPressed;
} Camera;

void initCamera(Camera* camera);
void DLL updateCamera(Camera* camera, float delta);

#endif