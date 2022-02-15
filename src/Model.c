#pragma once

#include <malloc.h>
#include <math.h>
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
    Vector3 point, worldPosition, normal;
    Camera* camera = &engine -> camera;
    Vector3 translateBy = {-camera -> position.x, -camera -> position.y, -camera -> position.z};
    Vector3 rotateBy    = {-camera -> rotation.x, -camera -> rotation.y, -camera -> rotation.z};

    for(int i = 0; i < model -> vertexCount; ++i){
        point = Rotate(&model -> vertices[i].position, &model -> rotation);
        point = Translate(&point, &model -> position);
        worldPosition = point;

        point = Translate(&point, &translateBy);
        point = Rotate(&point, &rotateBy);

        model -> vertices[i].projectedPoint = point;
        normal = Rotate(&model -> vertices[i].normal, &model -> rotation);

        Color lightAmount = {0};  
        for(int k = 0; k < engine -> lightCount; ++k)
            applyLight(engine -> lights[k], &worldPosition, &normal, &lightAmount);
        
        Color color = {0xFFFFFFFF};
        color.RGBA.r = (unsigned char)(color.RGBA.r * lightAmount.RGBA.r / 255.0f);
        color.RGBA.g = (unsigned char)(color.RGBA.g * lightAmount.RGBA.g / 255.0f);
        color.RGBA.b = (unsigned char)(color.RGBA.b * lightAmount.RGBA.b / 255.0f);
        color.RGBA.a = (unsigned char)(color.RGBA.a * lightAmount.RGBA.a / 255.0f);
        model -> vertices[i].color = color;
    }
}

void renderModel(Model* model, Engine* engine, RenderBuffer* renderBuffer){
    Vector3 origin = {0, 0, 0};
    Vector3 points[3];
    Vertex vertices[12 * 3];
    float dist[3];
    Camera* camera = &engine -> camera;

    for(int i = 0; i < model -> triangleCount; ++i){

        vertices[0] = model -> vertices[model -> index[i * 3    ]];
        vertices[1] = model -> vertices[model -> index[i * 3 + 1]];
        vertices[2] = model -> vertices[model -> index[i * 3 + 2]];

        dist[0] = distance(&origin, &vertices[0].projectedPoint);
        dist[1] = distance(&origin, &vertices[1].projectedPoint);
        dist[2] = distance(&origin, &vertices[2].projectedPoint);

        if(dist[0] > VIEW_DISTANCE && dist[1] > VIEW_DISTANCE && dist[2] > VIEW_DISTANCE)
            continue;

        points[0] = applyPerspective(&vertices[0].projectedPoint, camera);
        points[1] = applyPerspective(&vertices[1].projectedPoint, camera);
        points[2] = applyPerspective(&vertices[2].projectedPoint, camera);

        //culling of hidden surface
        if(calcNormal(&points[0], &points[1], &points[2]).z >= 0)
            continue;

        Color skyColor = { SKY_COLOR };
        float visibility = (VIEW_DISTANCE - dist[0]) / FOG_DENSITY;
        vertices[0].color = lerpColor(&skyColor, &vertices[0].color, visibility);
        visibility = (VIEW_DISTANCE - dist[1]) / FOG_DENSITY;
        vertices[1].color = lerpColor(&skyColor, &vertices[1].color, visibility);
        visibility = (VIEW_DISTANCE - dist[2]) / FOG_DENSITY;
        vertices[2].color = lerpColor(&skyColor, &vertices[2].color, visibility);
        
        //clipping against Z near plane
        int verticesCount = clipTriangleZ(vertices);

        //applying perspective
        for(int j = 0; j < verticesCount; ++j)
            vertices[j].projectedPoint = applyPerspective(&vertices[j].projectedPoint, camera);

        //clipping around screen edges
        verticesCount = clipTriangle(vertices, verticesCount);

        for(int k = 0; k < verticesCount; k += 3)
        renderTriangle(&vertices[k], &vertices[k+1], &vertices[k+2], renderBuffer);
    }
}

void deleteModel(Model* model){
    free(model -> vertices);
    free(model -> index);
}