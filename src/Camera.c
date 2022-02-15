#pragma once

#include <math.h>
#include "settings.h"
#include "Camera.h"

void initCamera(Camera* camera){
    camera -> z0           = (WIDTH / 2) / (tanf(FOV / 2 * PI / 180));
    camera -> position     = (Vector3){0, 0, 0};
    camera -> rotation     = (Vector3){0, 0, 0};
    camera -> W_KeyPressed = camera -> A_KeyPressed =
    camera -> S_KeyPressed = camera -> D_KeyPressed = 0;
}

void updateCamera(Camera* camera, float delta){
    if(camera -> W_KeyPressed){
        camera -> position.x += CAMERA_VELOCITY * sinf(camera -> rotation.y) * delta;
        camera -> position.z += CAMERA_VELOCITY * cosf(camera -> rotation.y) * delta;
    }
    if(camera -> S_KeyPressed){
        camera -> position.x -= CAMERA_VELOCITY * sinf(camera -> rotation.y) * delta;
        camera -> position.z -= CAMERA_VELOCITY * cosf(camera -> rotation.y) * delta;
    }
    if(camera -> A_KeyPressed)
        camera -> rotation.y -= CAMERA_ROTATION_SPEED * delta;
    if(camera -> D_KeyPressed)
        camera -> rotation.y += CAMERA_ROTATION_SPEED * delta;
    if(camera -> up_KeyPressed){
        camera -> position.y -= CAMERA_VELOCITY * delta;
    }
    if(camera -> down_KeyPressed){
        camera -> position.y += CAMERA_VELOCITY * delta;
    }
}