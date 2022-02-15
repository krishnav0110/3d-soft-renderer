#pragma once

#include <stdio.h>

#include "settings.h"
#include "Render.h"

void initRenderer(HWND hwnd, RenderBuffer* renderBuffer){
    renderBuffer -> memory = VirtualAlloc(0, WIDTH * HEIGHT * 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    renderBuffer -> bitmapInfo.bmiHeader.biSize        = sizeof(renderBuffer->bitmapInfo.bmiHeader);
    renderBuffer -> bitmapInfo.bmiHeader.biWidth       = WIDTH;
    renderBuffer -> bitmapInfo.bmiHeader.biHeight      = -HEIGHT;
    renderBuffer -> bitmapInfo.bmiHeader.biPlanes      = 1;
    renderBuffer -> bitmapInfo.bmiHeader.biBitCount    = 32;
    renderBuffer -> bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void clearBuffer(RenderBuffer* renderBuffer, Color color){
    int* pixel = (int*) renderBuffer -> memory;
    for(int i = 0; i < WIDTH * HEIGHT; ++i)
        *pixel++ = color.color;
}

void render(HWND hwnd, RenderBuffer* renderBuffer, int FPS){
    char text[8];
    snprintf(text, 8, "fps:%d", FPS);

    HDC hdc = GetDC(hwnd);
    StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, renderBuffer->memory, &renderBuffer->bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

    RECT rect;
    GetWindowRect(hwnd, &rect);
    TextOut(hdc, 0, 0, text, strlen(text));
    ReleaseDC(hwnd, hdc);
}

void free_RenderBuffer(RenderBuffer* renderBuffer){
    VirtualFree(renderBuffer -> memory, 0, MEM_RELEASE);
}