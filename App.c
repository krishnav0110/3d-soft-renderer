#pragma once

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "settings.h"
#include "Render.h"
#include "Engine.h"

HINSTANCE hinst; 
HWND m_hwnd;
RenderBuffer renderBuffer;
Engine engine;




int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow); 
BOOL InitApplication(HINSTANCE hinstance);
BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) ;
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RunMessageLoop();

 
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { 
    hinst = hinstance;
 
    if(InitApplication(hinst)){
        
        if(InitInstance(hinst, nCmdShow))
        
            RunMessageLoop();
        
        free_RenderBuffer(&renderBuffer);
    }
    return 0;
} 
 
BOOL InitApplication(HINSTANCE hinstance) { 
    WNDCLASSEX wcx; 
 
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = 0;                    // redraw if size changes 
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = LoadIcon(NULL, 
        IDI_APPLICATION);              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL, 
        IDC_ARROW);                    // predefined arrow        
    wcx.lpszMenuName =  "MainMenu";    // name of menu resource 
    wcx.lpszClassName = "MainWClass";  // name of window class 
    wcx.hIconSm = LoadImage(hinstance, // small class icon 
        MAKEINTRESOURCE(5),
        IMAGE_ICON, 
        GetSystemMetrics(SM_CXSMICON), 
        GetSystemMetrics(SM_CYSMICON), 
        LR_DEFAULTCOLOR); 
    
    return RegisterClassEx(&wcx); 
} 
 
BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) {   
 
    m_hwnd = CreateWindow( 
        "MainWClass",        // name of window class 
        "Sample",            // title-bar string 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // top-level window and no resizing
        CW_USEDEFAULT,       // default horizontal position 
        CW_USEDEFAULT,       // default vertical position 
        WIDTH,          // default width 
        HEIGHT,         // default height 
        (HWND) NULL,         // no owner window 
        (HMENU) NULL,        // use class menu 
        hinstance,           // handle to application instance 
        (LPVOID) NULL);      // no window-creation data 
 
    if (!m_hwnd) 
        return FALSE; 
 
    ShowWindow(m_hwnd, nCmdShow); 
    UpdateWindow(m_hwnd); 
    return TRUE; 
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
    switch (uMsg) { 
        case WM_KEYDOWN:
            handleKeyDown(&engine, wParam);
        break;
        case WM_KEYUP:
            handleKeyUp(&engine, wParam);
        break;

        case WM_CLOSE: 
            DestroyWindow(m_hwnd);
            return 0;
        break;
        case WM_DESTROY: 
            PostQuitMessage(0);
            return 0; 
 
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    } 
    return 0;
}

void RunMessageLoop() {

    initRenderer(m_hwnd, &renderBuffer);
    initEngine(&engine);
    char a[16];
    snprintf(a, 16, "z0:%f", engine.camera.z0);
    OutputDebugString(a);

    Model model;
    initModel(&model, 1, 3);
    model.position.z = 10;
    initVertex(&model.vertices[0], (Vector3){   0, -100, 0});
    initVertex(&model.vertices[1], (Vector3){-100,  100, 0});
    initVertex(&model.vertices[2], (Vector3){ 100,  100, 0});
    model.index[0] = 0;     model.index[1] = 1;     model.index[2] = 2;
    model.vertices[0].color = (Color){0xFFFF0000};
    model.vertices[1].color = (Color){0xFF00FF00};
    model.vertices[2].color = (Color){0xFF0000FF};

    addModel(&engine, &model);

    double FPS_CAP       = 1.0 / 60;
    clock_t currentTime  = clock();
    clock_t previousTime = clock();
    double delta         = 0;
    clock_t timer        = clock();
    int frames = 0, FPS = 0;

    while (1) {
        // Messages and user input
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if(msg.message == WM_QUIT)
            break;

        currentTime = clock();
        delta += (double)(currentTime - previousTime) / CLOCKS_PER_SEC;
        previousTime = currentTime;

        if(delta >= FPS_CAP){
            updateCamera(&engine.camera, delta);
            updateModels(&engine);
            delta -= FPS_CAP;
        }
        frames++;

        clearBuffer(&renderBuffer);
        renderModels(&engine, &renderBuffer);
        render(m_hwnd, &renderBuffer, FPS);

        if((double)(clock() - timer) >= CLOCKS_PER_SEC){
            FPS = frames;
            frames = 0;
            timer = clock();
        }
    }
}