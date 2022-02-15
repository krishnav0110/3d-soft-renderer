#pragma once

#include "settings.h"
#include "Terrain.h"

void generateTerrain(Model* model, float size, int verticesCount){
    initModel(model, (verticesCount - 1) * (verticesCount - 1) * 2, verticesCount * verticesCount);
    model->position = (Vector3){0, 200, 0};
    model->rotation = (Vector3){0, 0, 0};
    
    //float tileSize = size / verticesCount;
    float tileSize = UNIT_DISTANCE;
    float x = 0, z = 0;

    int index = 0;
    for(int i = 0; i < verticesCount; i++){
        for(int j = 0; j < verticesCount; j++){
            initVertex(&model->vertices[index], (Vector3){j * tileSize, 0, i * tileSize});
            model->vertices[index++].normal = (Vector3){0, 1, 0};
        }
    }

    index = 0;
    for(int i = 0; i < (verticesCount - 1); i++){
        for(int j = 0; j < (verticesCount - 1); j++){
            model->index[index++] = i       * verticesCount + j;
            model->index[index++] = i       * verticesCount + j + 1;
            model->index[index++] = (i + 1) * verticesCount + j;

            model->index[index++] = i       * verticesCount + j + 1;
            model->index[index++] = (i + 1) * verticesCount + j + 1;
            model->index[index++] = (i + 1) * verticesCount + j;
        }
    }
}