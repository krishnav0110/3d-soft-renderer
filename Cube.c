#pragma once

void initCube(Model* model, float x, float y, float z, float length){
    
    length /= 2;
    initModel(model, 12, 8);
    model -> position = (Vector3){x, y, z};
    initVertex(&model -> vertices[0], (Vector3){ length,  length, -length});
    initVertex(&model -> vertices[1], (Vector3){ length, -length, -length});
    initVertex(&model -> vertices[2], (Vector3){-length, -length, -length});
    initVertex(&model -> vertices[3], (Vector3){-length,  length, -length});
    initVertex(&model -> vertices[4], (Vector3){ length,  length,  length});
    initVertex(&model -> vertices[5], (Vector3){ length, -length,  length});
    initVertex(&model -> vertices[6], (Vector3){-length, -length,  length});
    initVertex(&model -> vertices[7], (Vector3){-length,  length,  length});

    //RIGHT
    model -> index[0] = 0;  model -> index[1] = 5;  model -> index[2] = 1;
    model -> index[3] = 0;  model -> index[4] = 4;  model -> index[5] = 5;

    //LEFT
    model -> index[6] = 2;  model -> index[7] = 6;  model -> index[8] = 7;
    model -> index[9] = 2;  model -> index[10] = 7;  model -> index[11] = 3;

    //TOP
    model -> index[12] = 1;  model -> index[13] = 5;  model -> index[14] = 2;
    model -> index[15] = 2;  model -> index[16] = 5;  model -> index[17] = 6;

    //BOTTOM
    model -> index[18] = 0;  model -> index[19] = 7;  model -> index[20] = 4;
    model -> index[21] = 0;  model -> index[22] = 3;  model -> index[23] = 7;

    //FRONT
    model -> index[24] = 0;  model -> index[25] = 1;  model -> index[26] = 2;
    model -> index[27] = 0;  model -> index[28] = 2;  model -> index[29] = 3;

    //BACK
    model -> index[30] = 4;  model -> index[31] = 7;  model -> index[32] = 5;
    model -> index[33] = 7;  model -> index[34] = 6;  model -> index[35] = 5;

    model -> vertices[0].normal = normalize(&((Vector3){ 1,  1, -1}));
    model -> vertices[1].normal = normalize(&((Vector3){ 1, -1, -1}));
    model -> vertices[2].normal = normalize(&((Vector3){-1, -1, -1}));
    model -> vertices[3].normal = normalize(&((Vector3){-1,  1, -1}));
    model -> vertices[4].normal = normalize(&((Vector3){ 1,  1,  1}));
    model -> vertices[5].normal = normalize(&((Vector3){ 1, -1,  1}));
    model -> vertices[6].normal = normalize(&((Vector3){-1, -1,  1}));
    model -> vertices[7].normal = normalize(&((Vector3){-1,  1,  1}));
}

/*void initCube(Model* model, float x, float y, float z, float length){
    initModel(model, 2, 4);
    model->position = (Vector3){0, 0, 5};
    initVertex(&model -> vertices[0], (Vector3){-100, -100, 0});
    initVertex(&model -> vertices[1], (Vector3){ 100, -100, 0});
    initVertex(&model -> vertices[2], (Vector3){ 100,  100, 0});
    initVertex(&model -> vertices[3], (Vector3){-100,  100, 0});

    model->vertices[0].color = (Color){0xFFFF0000};
    model->vertices[1].color = (Color){0xFF00FF00};
    model->vertices[2].color = (Color){0xFF0000FF};
    model->vertices[3].color = (Color){0xFFFF0000};

    model->index[0] = 0;    model->index[1] = 2;    model->index[2] = 1;
    model->index[3] = 0;    model->index[4] = 3;    model->index[5] = 2;
}*/