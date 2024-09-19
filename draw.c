#include "draw.h"






void draw_background(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(dc, &ps.rcPaint, brush);
    EndPaint(hwnd, &ps);
}

