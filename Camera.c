#pragma once

typedef struct {
    float z0;
    Vector3 position;
    Vector3 rotation;
    unsigned char W_KeyPressed, A_KeyPressed, S_KeyPressed, D_KeyPressed, up_KeyPressed, down_KeyPressed;
} Camera;

void initCamera(Camera* camera){
    camera -> z0 = (WIDTH / 2) / (tanf(FOV / 2 * PI / 180));
    camera -> position = (Vector3){0, 0, 0};
    camera -> rotation = (Vector3){0, 0, 0};
    camera -> W_KeyPressed = camera -> A_KeyPressed =
    camera -> S_KeyPressed = camera -> D_KeyPressed = 0;
}

void updateCamera(Camera* camera, float delta){
    if(camera -> W_KeyPressed){
        camera -> position.x += sinf(camera -> rotation.y) * 200 * delta;
        camera -> position.z += cosf(camera -> rotation.y) * 200 * delta;
        //camera -> position.y -= 100 * delta;
    }
    if(camera -> S_KeyPressed){
        camera -> position.x -= sinf(camera -> rotation.y) * 200 * delta;
        camera -> position.z -= cosf(camera -> rotation.y) * 200 * delta;
        //camera -> position.y += 100 * delta;
    }
    if(camera -> A_KeyPressed)
        camera -> rotation.y -= delta;
    if(camera -> D_KeyPressed)
        camera -> rotation.y += delta;
    if(camera -> up_KeyPressed)
        camera -> position.y -= 200 * delta;
    if(camera -> down_KeyPressed)
        camera -> position.y += 200 * delta;
}