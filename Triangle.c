#pragma once

#include "Vertex.c"

void renderTriangle(Vertex* v1, Vertex* v2, Vertex* v3, RenderBuffer* renderBuffer){
    unsigned int* pixel = (unsigned int*) renderBuffer -> memory;

    /*
     * sorting of vertices from top to bottom
     */
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

    /* storing the projected points in vector structure to be easily
     * accessible for further calculations.
     */
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
        /* sorting the intersection points in ascending order
         * 
         * lerping the color along the y-axis
         */
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
            //just in case safe measure
            if(WIDTH * (y + points[0].y) + x >= WIDTH * HEIGHT)
                continue;

            //rendering the pixel
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
        /* sorting the intersection points in ascending order
         * 
         * lerping the color along the y-axis
         */
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
            //just in case safe measure
            if(WIDTH * (y + points[1].y) + x >= WIDTH * HEIGHT)
                continue;

            //rendering the pixel
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

        /* checking the vertices of the triangle are whether in front or 
         * behing the plane and storting them in respective list.
         */
        for(int j = 0; j < 3; j++){
            Vector3 planeToPointVector = (Vector3){vertices[j].projectedPoint.x - planePoint.x, vertices[j].projectedPoint.y - planePoint.y, vertices[j].projectedPoint.z - planePoint.z};
            if(dotProduct(&planeToPointVector, &planeNormal) <= 0)
                outsideVertices[outsideVerticesCount++] = vertices[j];
            else
                insideVertices[insideVerticesCount++] = vertices[j];
        }

        if(insideVerticesCount == 3)
            continue;

        //form clipped triangle
        else if(insideVerticesCount == 1){
            Vertex v1, v2;
            v1.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            v2.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[1].projectedPoint, &planePoint, &planeNormal);

            float k1 = (v1.projectedPoint.y - outsideVertices[0].projectedPoint.y) / (insideVertices[0].projectedPoint.y - outsideVertices[0].projectedPoint.y);
            float k2 = (v2.projectedPoint.y - outsideVertices[1].projectedPoint.y) / (insideVertices[0].projectedPoint.y - outsideVertices[1].projectedPoint.y);
            v1.color = lerpColor(&outsideVertices[0].color, &insideVertices[0].color, k1);
            v2.color = lerpColor(&outsideVertices[1].color, &insideVertices[0].color, k2);

            //adding the clipped triangle
            vertices[(*verticesCount)++] = insideVertices[0];
            vertices[(*verticesCount)++] = v1;
            vertices[(*verticesCount)++] = v2;
        }
        
        //form clipped quad
        else if(insideVerticesCount == 2){
            Vertex v1, v2;
            v1.projectedPoint = planeLineIntersection(&insideVertices[0].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            v2.projectedPoint = planeLineIntersection(&insideVertices[1].projectedPoint, &outsideVertices[0].projectedPoint, &planePoint, &planeNormal);
            
            float k1 = (v1.projectedPoint.y - outsideVertices[0].projectedPoint.y) / (insideVertices[0].projectedPoint.y - outsideVertices[0].projectedPoint.y);
            float k2 = (v2.projectedPoint.y - outsideVertices[0].projectedPoint.y) / (insideVertices[1].projectedPoint.y - outsideVertices[0].projectedPoint.y);
            v1.color = lerpColor(&outsideVertices[0].color, &insideVertices[0].color, k1);
            v2.color = lerpColor(&outsideVertices[0].color, &insideVertices[1].color, k2);

            //adding the first triangle from clipped quad
            vertices[(*verticesCount)++] = insideVertices[0];
            vertices[(*verticesCount)++] = insideVertices[1];
            vertices[(*verticesCount)++] = v1;

            //adding the second triangle from clipped quad
            vertices[(*verticesCount)++] = insideVertices[1];
            vertices[(*verticesCount)++] = v1;
            vertices[(*verticesCount)++] = v2;
        }

        /*
         * if any vertex is behind the clipping plane, the triangle that needs to be clipped,
         * is removed by shifting all the triangles in the queue to the front by one position.
         */
        *verticesCount -= 3;
        for(int j = 0; j < *verticesCount; j += 3){
            vertices[j    ] = vertices[j + 3];
            vertices[j + 1] = vertices[j + 4];
            vertices[j + 2] = vertices[j + 5];
        }
    }
}

int clipTriangle(Vertex* v1, Vertex* v2, Vertex* v3, Vertex* vertices){
    vertices[0] = *v1;  vertices[1] = *v2;  vertices[2] = *v3;
    int verticesCount = 3;

    //LEFT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){1, 0, 0}, (Vector3){1, 0, 0});
    //RIGHT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){WIDTH - 1, 0, 0}, (Vector3){-1, 0, 0});
    //TOP
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, 1, 0}, (Vector3){0, 1, 0});
    //BOTTOM
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, HEIGHT - 1, 0}, (Vector3){0, -1, 0});
    //Z FRONT
    clipTriangle_Plane(vertices, &verticesCount, (Vector3){0, 0, 0}, (Vector3){0, 0, 1});

    return verticesCount;
}