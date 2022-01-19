#pragma once

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include "settings.h"
#include "Render.h"

void initRenderer(HWND hwnd){
    renderBuffer.memory = VirtualAlloc(0, WIDTH * HEIGHT * 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    renderBuffer.width = WIDTH;
    renderBuffer.height = HEIGHT;

    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = WIDTH;
    bitmapInfo.bmiHeader.biHeight = -HEIGHT;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void clearBuffer(){
    int* pixel = (int*) renderBuffer.memory;
    for(int i = 0; i < renderBuffer.width * renderBuffer.height; i++)
        *pixel++ = 0;
}

void render(HWND hwnd){
    HDC hdc = GetDC(hwnd);
    StretchDIBits(hdc, 0, 0, renderBuffer.width, renderBuffer.height, 0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.memory, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
    ReleaseDC(hwnd, hdc);
}

void clearMemory(){
    VirtualFree(renderBuffer.memory, 0, MEM_RELEASE);
}