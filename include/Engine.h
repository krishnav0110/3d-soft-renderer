#pragma once

#ifndef _INC_ENGINE_
#define _INC_ENGINE_

#include "dllsupport.c"

#include <windows.h>
#include "Camera.h"
#include "Model.h"

typedef struct {
    Camera camera;
    int modelCount;
    Model* models[5];
} Engine;

void DLL initEngine(Engine* engine);
void DLL addModel(Engine* engine, Model* model);

void DLL handleKeyDown(Engine* engine, WPARAM wParam);
void DLL handleKeyUp(Engine* engine, WPARAM wParam);

void updateModel(Model* model, Engine* engine);
void renderModel(Model* model, Engine* engine, RenderBuffer* renderBuffer);

void DLL updateModels(Engine* engine);
void DLL renderModels(Engine* engine, RenderBuffer* renderBuffer);

Vector3 applyPerspective(Vector3* vec, Camera* camera);

#endif