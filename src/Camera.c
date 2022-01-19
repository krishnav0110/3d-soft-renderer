#pragma once

#include "Camera.h"

void initCamera(Camera* camera){
    camera -> position = (Vector3){0, 0, 0};
    camera -> rotation = (Vector3){0, 0, 0};
    camera -> upKeyPressed = camera -> leftKeyPressed =
    camera -> rightKeyPressed = camera -> downKeyPressed = 0;
}

void updateCamera(Camera* camera, float delta){
    if(camera -> upKeyPressed){
        camera -> position.x -= sinf(camera -> rotation.y * PI / 180) * 200 * delta;
        camera -> position.z += cosf(camera -> rotation.y * PI / 180) * 200 * delta;
        //camera -> position.y -= 100 * delta;
    }
    if(camera -> downKeyPressed){
        camera -> position.x += sinf(camera -> rotation.y * PI / 180) * 200 * delta;
        camera -> position.z -= cosf(camera -> rotation.y * PI / 180) * 200 * delta;
        //camera -> position.y += 100 * delta;
    }
    if(camera -> leftKeyPressed)
        camera -> rotation.y += 50 * delta;
    if(camera -> rightKeyPressed)
        camera -> rotation.y -= 50 * delta;
}