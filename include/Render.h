#pragma once

#ifndef _INC_RENDER_
#define _INC_RENDER_

#include <windows.h>
#include "Color.h"
#include "dllsupport.c"

typedef struct {
    void* memory;
    //void* zBuffer;
    BITMAPINFO bitmapInfo;
} RenderBuffer;

void DLL initRenderer(HWND hwnd, RenderBuffer* renderBuffer);

void DLL clearBuffer(RenderBuffer* renderBuffer, Color color);
void DLL render(HWND hwnd, RenderBuffer* renderBuffer, int FPS);

void DLL free_RenderBuffer(RenderBuffer* renderBuffer);

#endif