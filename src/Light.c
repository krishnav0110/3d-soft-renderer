#pragma once

#include "Light.h"

void initLight(Light* light, enum LightType type, Color color, Vector3 direction, Vector3 position, int length){
    light -> position = position;
    light -> color = color;
    light -> direction = normalize(&direction);
    light -> type = type;
    light -> length = length;
}

void applyLight(Vector3* normal, Color* lightAmount, Light* light){
    Color lightToAdd = { 0xFFFFFFFF };
    lightToAdd.RGBA.r -= lightAmount -> RGBA.r;
    lightToAdd.RGBA.g -= lightAmount -> RGBA.g;
    lightToAdd.RGBA.b -= lightAmount -> RGBA.b;

    float brightness = 0;
    if(light -> type == AMBIENT)
        brightness = 1;
    else if(light -> type == DIRECTIONAL){
        brightness = -dotProduct(&light -> direction, normal);
        if(brightness < 0)
            brightness = 0;
    }
    lightAmount -> RGBA.r += (unsigned char)(lightToAdd.RGBA.r * brightness * light -> color.RGBA.r / 255.0f);
    lightAmount -> RGBA.g += (unsigned char)(lightToAdd.RGBA.g * brightness * light -> color.RGBA.g / 255.0f);
    lightAmount -> RGBA.b += (unsigned char)(lightToAdd.RGBA.b * brightness * light -> color.RGBA.b / 255.0f);
}