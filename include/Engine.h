#pragma once
#include <windows.h>

#include "Camera.h"
#include "Light.h"
#include "Model.h"

typedef struct {
    float z0;
    Camera camera;
    int noModels;
    Model* models[5];
    int noLights;
    Light* lights[5];
} Engine;

void initEngine(Engine* engine);

void handleKeyDown(Engine* engine, WPARAM wParam);
void handleKeyUp(Engine* engine, WPARAM wParam);

void addModel(Engine* engine, Model* model);
void addLight(Engine* engine, Light* light);

void updateModel(Model* model, Engine* engine);
void renderModels(Engine* engine);