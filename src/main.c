#include <windows.h>
#include "tools.h"
#include "draw/draw.h"
#define IDI_MYICON 101  

extern HDC dc;

VOID OnSize(HWND hwnd, UINT wParam, int width, int height) {
    // will implement this later
}


int center_x;
int center_y;

HFONT CreateStandardFont() {
    return CreateFontW(
        -MulDiv(12, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72), 
        0,                          
        0,                         
        0,                         
        FW_NORMAL,                
        FALSE,                     
        FALSE,                     
        FALSE,                     
        DEFAULT_CHARSET,          
        OUT_DEFAULT_PRECIS,       
        CLIP_DEFAULT_PRECIS,     
        DEFAULT_QUALITY,          
        DEFAULT_PITCH | FF_DONTCARE,     
        L"Arial"                   
    );
}


SHORT state = 0;
static int first_id;
static int second_id;
HFONT hFont;
HBITMAP hBitmap;  



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {
        switch (state) {

        case 0:

        {
            hFont = CreateStandardFont(); 
            if (!hFont) {
                ShowFormattedMessageBox(GetLastError());
                DestroyWindow(hwnd);
            }
            SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
            hBitmap = (HBITMAP)LoadImageW(NULL, L"resources\\xicon.bmp", IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
            if (hBitmap == NULL) {
                ShowFormattedMessageBox(GetLastError());
                DestroyWindow(hwnd);
            }
            return 0;

        }
        case 1:
        {
            
            break;
        }
        }
          
    }
    case WM_COMMAND:
    {
        switch (state) {
        case 1:
        {
            if (LOWORD(wParam) == first_id) {
                MessageBox(hwnd, L"Button clicked!", L"Info", MB_OK);
            }
            if (LOWORD(wParam) == second_id) {
                MessageBox(hwnd, L"Button clicked!", L"No", MB_OK);
            }
        }
        }
        
    }
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
        if (hBitmap) {
            DeleteObject(hBitmap);
        }
        if (hFont) {
            DeleteObject(hFont);
        }
        PostQuitMessage(0);
        return 0;
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        switch (state) {
        case 0:
        {
            draw_background(dc, &ps, hwnd, RGB(0, 0, 0));
            int center_x = ((ps.rcPaint.left + ps.rcPaint.right) / 2);
            int center_y = ((ps.rcPaint.top + ps.rcPaint.bottom) / 2);
            if (hBitmap) {
                BITMAP bitmap;
                GetObject(hBitmap, sizeof(BITMAP), &bitmap);

                center_x -= bitmap.bmWidth / 2;
                center_y -= bitmap.bmHeight / 2;
                draw_image(dc, hBitmap, center_x, center_y);
            }
            Sleep(1000);
            state = 1;
            draw_background(dc, &ps, hwnd, RGB(0, 0, 0));
            if (hBitmap) {
                DeleteObject(hBitmap);
            }
            hBitmap = (HBITMAP)LoadImageW(NULL, L"resources\\xicon.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
            if (!hBitmap) {
                ShowFormattedMessageBox(GetLastError());
                DestroyWindow(hwnd);
            }
            InvalidateRect(hwnd, NULL, 0);
            // switch overflow on purpose
        }
        case 1:
            first_id = draw_button(hwnd, 120, 10, 100, 50, L"Debug1");
            second_id = draw_button(hwnd, 120, 120, 100, 50, L"Debug2");
            draw_text(dc, 900, 900, L"X Build (IDK DUDE)", RGB(255, 255, 255));
            draw_text(dc, 900, 90, L"Hello Elon Musk", RGB(255, 255, 255));
            draw_image(dc, hBitmap, 0, center_x);

            break;

        }


        EndPaint(hwnd, &ps);
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
