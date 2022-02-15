#pragma once

#include <math.h>
#include "Light.h"

void initLight(Light* light, enum LightType type, Color color, Vector3 position, Vector3 direction, Vector3 attenuation){
    light -> position = position;
    light -> color = color;
    light -> direction = normalize(&direction);
    light -> type = type;
    light -> attenuaton = attenuation;
}

void applyLight(Light* light, Vector3* position, Vector3* normal, Color* lightAmount){
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
    else if(light -> type == POINT_LIGHT){
        Vector3 toLightVector = {light->position.x - position->x, light->position.y - position->y, light->position.z - position->z};
        toLightVector = normalize(&toLightVector);
        
        float dist = distance(position, &light->position);
        brightness = -dotProduct(&toLightVector, normal);
        float attenuationFactor = light->attenuaton.x + light->attenuaton.y * dist + light->attenuaton.z * dist * dist;
        brightness = brightness / attenuationFactor;
        
        if(brightness < 0)
            brightness = 0;
    }
    lightAmount -> RGBA.r += (unsigned char)(lightToAdd.RGBA.r * brightness * light -> color.RGBA.r / 255.0f);
    lightAmount -> RGBA.g += (unsigned char)(lightToAdd.RGBA.g * brightness * light -> color.RGBA.g / 255.0f);
    lightAmount -> RGBA.b += (unsigned char)(lightToAdd.RGBA.b * brightness * light -> color.RGBA.b / 255.0f);
}