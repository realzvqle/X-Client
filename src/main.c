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




SHORT state = 0;
static int first_id;
static int second_id;
HBITMAP hBitmap;  



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {
        switch (state) {

        case 0:

        { 
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
        break;
          
    }
    case WM_COMMAND:
    {
        switch (state) {
        case 1:
        {
            if (LOWORD(wParam) == first_id) {
                state = 2;
                RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_VALIDATE | RDW_UPDATENOW);
                InvalidateRect(hwnd, NULL, 0);
                UpdateWindow(hwnd);
                HWND button = GetDlgItem(hwnd, first_id);
                if (button) {
                    DestroyWindow(button);
                }
                if (hBitmap) {
                    DeleteObject(hBitmap);
                }
                break;

            }
            
        }
        }
        break;
        
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        OnSize(hwnd, (UINT)wParam, width, height);
        break;
    }
    break;
    case WM_CLOSE:
    {
        int result = MessageBoxW(hwnd, L"Are you sure you want to close the window?", L"X", MB_YESNO | MB_ICONQUESTION);
        if (result == IDYES) {
            DestroyWindow(hwnd);
            break;
        }
        break;
        
    }
    case WM_DESTROY:
    {
        if (hBitmap) {
            DeleteObject(hBitmap);
        }
        PostQuitMessage(0);
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
            //MessageBoxW(hwnd, "Hi C Lads", "Hello!", MB_OK);
            Sleep(1000);
            state = 1;
            draw_background(dc, &ps, hwnd, RGB(0, 0, 0));
            if (hBitmap) {
                DeleteObject(hBitmap);
            }
            hBitmap = (HBITMAP)LoadImageW(NULL, L"resources\\xicon-gray.bmp", IMAGE_BITMAP, 800, 800, LR_LOADFROMFILE);
            if (!hBitmap) {
                ShowFormattedMessageBox(GetLastError());
                DestroyWindow(hwnd);
            }
            InvalidateRect(hwnd, NULL, 0);
            // switch overflow on purpose
        }
        case 1:
        {


            SIZE textSize;
            GetTextExtentPoint32(dc, L"Login to X Client", lstrlen(L"Login to X Client"), &textSize);

            int x = (ps.rcPaint.left + ps.rcPaint.right) / 2 - (textSize.cx / 2);
            int y = (ps.rcPaint.top + ps.rcPaint.bottom) / 2 - (textSize.cy / 2);
            draw_text(dc, x - 20, y - 20, 20, L"Login to X client", RGB(255, 255, 255));
            first_id = draw_button(hwnd, x, y + 100, 140, 40, L"Login");
            draw_image(dc, hBitmap, -300, -200);

            break;
        }
        case 2:
        {
            draw_background(dc, &ps, hwnd, RGB(0, 0, 0));
            InvalidateRect(hwnd, NULL, 0);
            draw_text(dc,20, 20, 20, L"You're Logged In", RGB(255, 255, 255));
            break;
        }

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
