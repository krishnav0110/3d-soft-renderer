#pragma once
#include <windows.h>

#include "settings.h"
#include "Render.c"
#include "Model.c"
#include "Camera.c"
#include "EngineBase.c"

typedef struct {
    Camera camera;
    int noModels;
    Model* models[5];
    int noLights;
    Light* lights[5];
} Engine;

void initEngine(Engine* engine){
    initCamera(&engine -> camera);
    engine -> noModels = 0;
    engine -> noLights = 0;
}

void handleKeyDown(Engine* engine, WPARAM wParam){
    if(wParam == 0x57)    engine -> camera.W_KeyPressed    = 1; 
    if(wParam == 0x41)    engine -> camera.A_KeyPressed    = 1; 
    if(wParam == 0x53)    engine -> camera.S_KeyPressed    = 1; 
    if(wParam == 0x44)    engine -> camera.D_KeyPressed    = 1; 
    if(wParam == VK_UP)   engine -> camera.up_KeyPressed   = 1;
    if(wParam == VK_DOWN) engine -> camera.down_KeyPressed = 1;
}

void handleKeyUp(Engine* engine, WPARAM wParam){
    if(wParam == 0x57)    engine -> camera.W_KeyPressed    = 0;
    if(wParam == 0x41)    engine -> camera.A_KeyPressed    = 0;
    if(wParam == 0x53)    engine -> camera.S_KeyPressed    = 0;
    if(wParam == 0x44)    engine -> camera.D_KeyPressed    = 0;
    if(wParam == VK_UP)   engine -> camera.up_KeyPressed   = 0;
    if(wParam == VK_DOWN) engine -> camera.down_KeyPressed = 0;
}

void addModel(Engine* engine, Model* model){
    engine -> models[engine -> noModels] = model;
    engine -> noModels++;
}

void addLight(Engine* engine, Light* light){
    engine -> lights[engine -> noLights] = light;
    engine -> noLights++;
}

void updateModel(Model* model, Engine* engine){
    Vector3 point, position, normal;
    Camera* camera = &engine -> camera;
    Vector3 translateBy = (Vector3){-camera -> position.x, -camera -> position.y, -camera -> position.z};
    Vector3 rotateBy    = (Vector3){-camera -> rotation.x, -camera -> rotation.y, -camera -> rotation.z};

    for(int i = 0; i < model -> noVertices; i++){
        point = Rotate(&model -> vertices[i].position, &model -> rotation);
        point = Translate(&point, &model -> position);
        position = point;

        point = Translate(&point, &translateBy);
        point = Rotate(&point, &rotateBy);

        point = applyPerspective(&point, camera);
        model -> vertices[i].projectedPoint = point;

        normal = Rotate(&model -> vertices[i].normal, &model -> rotation);
        Color lightAmount = {0};
        for(int k = 0; k < engine -> noLights; k++)
            applyLight(&position, &normal, &lightAmount, engine -> lights[k]);
        
        Color color = {0xFFFFFFFF};
        color.RGBA.r = (unsigned char)(color.RGBA.r * lightAmount.RGBA.r / 255.0f);
        color.RGBA.g = (unsigned char)(color.RGBA.g * lightAmount.RGBA.g / 255.0f);
        color.RGBA.b = (unsigned char)(color.RGBA.b * lightAmount.RGBA.b / 255.0f);
        color.RGBA.a = (unsigned char)(color.RGBA.a * lightAmount.RGBA.a / 255.0f);
        model -> vertices[i].color = color;
    }
}

void renderModels(Engine* engine){
    Model* model;
    Vector3 points[3];
    Vertex vertices[12 * 3];

    for(int i = 0; i < engine -> noModels; i++){
        model = engine -> models[i];
        updateModel(model, engine);

        for(int j = 0; j < model -> noTriangles; j++){

            points[0] = model -> vertices[model -> index[j * 3    ]].projectedPoint;
            points[1] = model -> vertices[model -> index[j * 3 + 1]].projectedPoint;
            points[2] = model -> vertices[model -> index[j * 3 + 2]].projectedPoint;

            Vector3 vec1 = (Vector3){points[1].x - points[0].x, points[1].y - points[0].y};
            Vector3 vec2 = (Vector3){points[2].x - points[0].x, points[2].y - points[0].y};

            if((vec1.x * vec2.y - vec1.y * vec2.x) >= 0)
                continue;

            int verticesCount = clipTriangle(&model -> vertices[model -> index[j * 3    ]],
                                             &model -> vertices[model -> index[j * 3 + 1]], 
                                             &model -> vertices[model -> index[j * 3 + 2]],
                                             vertices);

            for(int k = 0; k < verticesCount; k += 3)
            renderTriangle(&vertices[k], &vertices[k + 1], &vertices[k + 2], &renderBuffer);
        }
    }
}