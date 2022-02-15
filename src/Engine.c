#pragma once

#include <windows.h>
#include "settings.h"
#include "Engine.h"

void initEngine(Engine* engine){
    initCamera(&engine -> camera);
    engine -> modelCount = 0;
    engine -> lightCount = 0;
    engine -> models = malloc(MAX_MODELS * sizeof(*engine -> models));
    engine -> lights = malloc(MAX_LIGHTS * sizeof(*engine -> lights));
}

void addModel(Engine* engine, Model* model){
    engine -> models[engine -> modelCount] = model;
    engine -> modelCount++;
}

void addLight(Engine* engine, Light* light){
    engine -> lights[engine -> lightCount] = light;
    engine -> lightCount++;
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

void updateModels(Engine* engine){
    for(int i = 0; i < engine -> modelCount; i++)
        updateModel(engine->models[i], engine);
}

void renderModels(Engine* engine, RenderBuffer* renderBuffer){
    for(int i = 0; i < engine -> modelCount; i++)
        renderModel(engine->models[i], engine, renderBuffer);
}

Vector3 applyPerspective(Vector3* vec, Camera* camera){
    float tx = WIDTH  / 2;
    float ty = HEIGHT / 2;
    float z = camera -> z0 / (camera -> z0 + vec -> z);

    Vector3 toReturn;
    toReturn.x = vec -> x * z + tx;
    toReturn.y = vec -> y * z + ty;
    toReturn.z = vec -> z;
    return toReturn;
}