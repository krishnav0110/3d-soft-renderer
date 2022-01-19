#pragma once

#include <windows.h>

typedef struct {
    void* memory;
    int width;
    int height;
} RenderBuffer;

BITMAPINFO bitmapInfo;
RenderBuffer renderBuffer;

void initRenderer(HWND hwnd);

void clearBuffer();
void render(HWND hwnd);

void clearMemory();