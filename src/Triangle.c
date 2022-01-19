#pragma once

#include "settings.h"
#include "Triangle.h"

void renderTriangle(Vertex* v1, Vertex* v2, Vertex* v3, RenderBuffer* renderBuffer){
    unsigned int* pixel = (unsigned int*) renderBuffer -> memory;

    //sorting of vertices from top to bottom
    if(v1->projectedPoint.y > v2->projectedPoint.y){
        Vertex* temp = v1;
        v1 = v2;
        v2 = temp;
    }
    if(v1->projectedPoint.y > v3->projectedPoint.y){
        Vertex* temp = v3;
        v3 = v1;
        v1 = temp;
    }
    if(v2->projectedPoint.y > v3->projectedPoint.y){
        Vertex* temp = v2;
        v2 = v3;
        v3 = temp;
    }
    Vector3 points[3];
    points[0] = v1->projectedPoint;
    points[1] = v2->projectedPoint;
    points[2] = v3->projectedPoint;

    //filling upper half of triangle
    float slope1 = (points[1].x - points[0].x) / (points[1].y - points[0].y);
    float slope2 = (points[2].x - points[0].x) / (points[2].y - points[0].y);
    float lerpAmt_y1 = 0, lerpStep_y1 = 1.0f / (points[1].y - points[0].y);
    float lerpAmt_y2 = 0, lerpStep_y2 = 1.0f / (points[2].y - points[0].y);

    for(int y = 0; y < points[1].y - points[0].y; y++){
        int start_x = points[0].x + y * slope1;
        int end_x = points[0].x + y * slope2;

        Color color_x1, color_x2;

        if(start_x > end_x){
            int t = start_x;    start_x = end_x;    end_x = t;
            color_x1 = lerpColor(&v1 -> color, &v3 -> color, lerpAmt_y2);
            color_x2 = lerpColor(&v1 -> color, &v2 -> color, lerpAmt_y1);
        }
        else{
            color_x1 = lerpColor(&v1 -> color, &v2 -> color, lerpAmt_y1);
            color_x2 = lerpColor(&v1 -> color, &v3 -> color, lerpAmt_y2);
        }
        float lerpAmt_x = 0;
        float lerpStep_x = 1.0f / (end_x - start_x);

        for(int x = start_x; x <= end_x; x++){
            Color color = lerpColor(&color_x1, &color_x2, lerpAmt_x);
            pixel[renderBuffer -> width * (int)(y + points[0].y) + x] = color.color;
            lerpAmt_x += lerpStep_x;
        }
        lerpAmt_y1 += lerpStep_y1;
        lerpAmt_y2 += lerpStep_y2;
    }

    //filling lower half of triangle
    slope1 = (points[2].x - points[1].x) / (points[2].y - points[1].y);
    int off_x = points[0].x + (points[1].y - points[0].y) * slope2;
    lerpAmt_y1 = 0; lerpStep_y1 = 1.0f / (points[2].y - points[1].y);

    for(int y = 0; y < points[2].y - points[1].y; y++){
        int start_x = points[1].x + y * slope1;
        int end_x = off_x + y * slope2;

        Color color_x1, color_x2;

        if(start_x > end_x){
            int t = start_x;    start_x = end_x;    end_x = t;
            color_x1 = lerpColor(&v1 -> color, &v3 -> color, lerpAmt_y2);
            color_x2 = lerpColor(&v2 -> color, &v3 -> color, lerpAmt_y1);
        }
        else{
            color_x1 = lerpColor(&v2 -> color, &v3 -> color, lerpAmt_y1);
            color_x2 = lerpColor(&v1 -> color, &v3 -> color, lerpAmt_y2);
        }    
        
        float lerpAmt_x = 0;
        float lerpStep_x = 1.0f / (end_x - start_x);

        for(int x = start_x; x <= end_x; x++){
            Color color = lerpColor(&color_x1, &color_x2, lerpAmt_x);
            pixel[renderBuffer -> width * (int)(y + points[1].y) + x] = color.color;
            lerpAmt_x += lerpStep_x;
        }
        lerpAmt_y1 += lerpStep_y1;
        lerpAmt_y2 += lerpStep_y2;
    }
}

void clipTriangle_Plane(Vertex* vertices, int* verticesCount, Vector3 planePoint, Vector3 planeNormal){
    Vertex insideVertices[3], outsideVertices[3];
    int insideVerticesCount, outsideVerticesCount, noVertices = *verticesCount;

    for(int i = 0; i < noVertices; i += 3){
        insideVerticesCount = outsideVerticesCount = 0;

        for(int j = 0; j < 3; j++){
            Vector3 normalToPointVector = (Vector3){vertices[i+j].projectedPoint.x - planePoint.x, vertices[i+j].projectedPoint.y - planePoint.y, vertices[i+j].projectedPoint.z - planePoint.z};
            if(dotProduct(&normalToPointVector, &planeNormal) < 0)
                outsideVertices[outsideVerticesCount++] = vertices[i + j];
            else
                insideVertices[insideVerticesCount++] = vertices[i + j];
        }

        if(insideVerticesCount == 3)
            continue;

        else if(insideVerticesCount == 1){
            Vertex v1, v2;
            v1.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            v2.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[1].projectedPoint, &planePoint, &planeNormal);

            float k1 = (v1.projectedPoint.x - outsideVertices[0].projectedPoint.x) / (insideVertices[0].projectedPoint.x - outsideVertices[0].projectedPoint.x);
            float k2 = (v2.projectedPoint.x - outsideVertices[1].projectedPoint.x) / (insideVertices[0].projectedPoint.x - outsideVertices[1].projectedPoint.x);
            v1.color = lerpColor(&outsideVertices[0].color, &insideVertices[0].color, k1);
            v2.color = lerpColor(&outsideVertices[1].color, &insideVertices[0].color, k2);

            vertices[(*verticesCount)++] = insideVertices[0];
            vertices[(*verticesCount)++] = v1;
            vertices[(*verticesCount)++] = v2;
        }
        else if(insideVerticesCount == 2){
            Vertex v1, v2;
            v1.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            v2.projectedPoint = planeLineIntersection(&insideVertices[1].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            
            float k1 = (v1.projectedPoint.x - outsideVertices[0].projectedPoint.x) / (insideVertices[0].projectedPoint.x - outsideVertices[0].projectedPoint.x);
            float k2 = (v2.projectedPoint.x - outsideVertices[0].projectedPoint.x) / (insideVertices[1].projectedPoint.x - outsideVertices[0].projectedPoint.x);
            v1.color = lerpColor(&outsideVertices[0].color, &insideVertices[0].color, k1);
            v2.color = lerpColor(&outsideVertices[0].color, &insideVertices[1].color, k2);

            vertices[(*verticesCount)++] = insideVertices[0];
            vertices[(*verticesCount)++] = insideVertices[1];
            vertices[(*verticesCount)++] = v1;

            vertices[(*verticesCount)++] = insideVertices[1];
            vertices[(*verticesCount)++] = v1;
            vertices[(*verticesCount)++] = v2;
        }

        *verticesCount -= 3;
        for(int j = i; j < *verticesCount; j += 3){
            vertices[j    ] = vertices[j + 3];
            vertices[j + 1] = vertices[j + 4];
            vertices[j + 2] = vertices[j + 5];
        }
    }
}

int clipTriangle(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* vertices){
    vertices[0] = *v1;  vertices[1] = *v2;  vertices[2] = *v3;
    int verticesCount = 3;

    //Z FRONT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, 0, 0}, (Vector3){0, 0, 1});
    //LEFT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, 0, 0}, (Vector3){1, 0, 0});
    //TOP
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, 0, 0}, (Vector3){0, 1, 0});
    //RIGHT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){WIDTH - 1, 0, 0}, (Vector3){-1, 0, 0});
    //BOTTOM
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, HEIGHT - 1, 0}, (Vector3){0, -1, 0});

    return verticesCount;
}