#pragma once

#include <malloc.h>
#include "settings.h"
#include "Triangle.h"
#include "Engine.h"

void initModel(Model* model, int triangleCount, int vertexCount){
    model -> position      = (Vector3){0, 0, 0};
    model -> rotation      = (Vector3){0, 0, 0};
    model -> triangleCount = triangleCount;
    model -> vertexCount   = vertexCount;
    model -> vertices      = calloc(vertexCount      , sizeof(*model -> vertices));
    model -> index         = calloc(triangleCount * 3, sizeof(*model -> index));
}

void updateModel(Model* model, Engine* engine){
    Vector3 point, position, normal;
    Camera* camera = &engine -> camera;
    Vector3 translateBy = {-camera -> position.x, -camera -> position.y, -camera -> position.z};
    Vector3 rotateBy    = {-camera -> rotation.x, -camera -> rotation.y, -camera -> rotation.z};

    for(int i = 0; i < model -> vertexCount; i++){
        point = Rotate(&model -> vertices[i].position, &model -> rotation);
        point = Translate(&point, &model -> position);
        position = point;

        point = Translate(&point, &translateBy);
        point = Rotate(&point, &rotateBy);

        point = applyPerspective(&point, camera);
        model -> vertices[i].projectedPoint = point;

        /*normal = Rotate(&model -> vertices[i].normal, &model -> rotation);
        Color lightAmount = {0};
        for(int k = 0; k < engine -> noLights; k++)
            applyLight(&position, &normal, &lightAmount, engine -> lights[k]);
        
        Color color = {0xFFFFFFFF};
        color.RGBA.r = (unsigned char)(color.RGBA.r * lightAmount.RGBA.r / 255.0f);
        color.RGBA.g = (unsigned char)(color.RGBA.g * lightAmount.RGBA.g / 255.0f);
        color.RGBA.b = (unsigned char)(color.RGBA.b * lightAmount.RGBA.b / 255.0f);
        color.RGBA.a = (unsigned char)(color.RGBA.a * lightAmount.RGBA.a / 255.0f);
        model -> vertices[i].color = color;
        */
    }
}

void renderModel(Model* model, RenderBuffer* renderBuffer){
    Vector3 points[3];
    Vertex vertices[12 * 3];

    for(int i = 0; i < model -> triangleCount; i++){

        points[0] = model -> vertices[model -> index[i * 3    ]].projectedPoint;
        points[1] = model -> vertices[model -> index[i * 3 + 1]].projectedPoint;
        points[2] = model -> vertices[model -> index[i * 3 + 2]].projectedPoint;

        if(points[0].z > VIEW_DISTANCE || points[1].z > VIEW_DISTANCE || points[2].z > VIEW_DISTANCE)
            continue;

        if(calcNormal(points, points + 1, points + 2).z >= 0)
            continue;

        int verticesCount = clipTriangle(&model -> vertices[model -> index[i * 3    ]],
                                         &model -> vertices[model -> index[i * 3 + 1]], 
                                         &model -> vertices[model -> index[i * 3 + 2]],
                                         vertices);

        for(int k = 0; k < verticesCount; k += 3)
        renderTriangle(&vertices[k], &vertices[k + 1], &vertices[k + 2], renderBuffer);
    }
}

void deleteModel(Model* model){
    free(model -> vertices);
    free(model -> index);
}