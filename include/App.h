#pragma once

#include <windows.h> 
#include "Engine.h"
  
HINSTANCE hinst; 
HWND m_hwnd;
Engine engine;
 
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow); 
 
BOOL InitApplication(HINSTANCE hinstance);
BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) ;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void RunMessageLoop();