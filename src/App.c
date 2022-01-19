//taskkill /F /IM ApplicationName.exe
#pragma once

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
//#pragma comment(lib, "comdlg32.lib")

#include <stdio.h>
#include <time.h>

#include "App.h"

 
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { 
    hinst = hinstance;
 
    if(InitApplication(hinst)){
        
        if(InitInstance(hinst, nCmdShow))
        
            RunMessageLoop();
        
        clearMemory();
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

    initRenderer(m_hwnd);

    double FPS_CAP = 1.0 / 60;
    clock_t currentTime = clock();
    clock_t previousTime = clock();
    double delta = 0;

    initEngine(&engine);
    Model model;
    initCube(&model, 0, 0, 300, 200);
    addModel(&engine, &model);
    Light light1;
    Color lightColor;   lightColor.RGBA.r = 80;    lightColor.RGBA.g = 80;    lightColor.RGBA.b = 80;
    initLight(&light1, AMBIENT, lightColor, (Vector3){0, 0, 0}, (Vector3){0, 0, 0}, 0);
    addLight(&engine, &light1);
    Light light2;
    lightColor.RGBA.r = 255;    lightColor.RGBA.g = 255;    lightColor.RGBA.b = 255;
    initLight(&light2, DIRECTIONAL, lightColor, (Vector3){1, 0, 1}, (Vector3){0, 0, 0}, 0);
    addLight(&engine, &light2);

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
            model.rotation.y += 30 * delta;
            updateCamera(&engine.camera, delta);
            delta -= FPS_CAP;
        }

        clearBuffer();
        renderModels(&engine);
        render(m_hwnd);
    }
}