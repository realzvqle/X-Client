#include <windows.h>
#include "tools.h"
#include "draw.h"

#define IDI_MYICON 101  

void OnSize(HWND hwnd, UINT wParam, int width, int height) {
    // will implement this later
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        OnSize(hwnd, (UINT)wParam, width, height);
        return 0; 
    }
    break;
    case WM_CLOSE:
    {
        int result = MessageBoxW(hwnd, L"Are you sure you want to close the window?", L"X", MB_YESNO | MB_ICONQUESTION);
        if (result == IDYES) {
            DestroyWindow(hwnd);
            break;
        }
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
        break;
    }
    case WM_PAINT:
    {
        draw_background(hwnd);
        break;
    }


    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    const WCHAR CLASS_NAME[] = L"X Client";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));

    if (!RegisterClass(&wc)) {
        ShowFormattedMessageBox(GetLastError());
        return -1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"X Client",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == NULL) {
        ShowFormattedMessageBox(GetLastError());
        return -1;
    }

    ShowWindow(hwnd, nShowCmd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
