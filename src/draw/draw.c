#include "draw.h"




static INT current_id = 0;
extern HFONT hFont;

VOID draw_background(HDC dc, PPAINTSTRUCT ps, HWND hwnd, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &ps->rcPaint, brush);
}


VOID draw_image(HDC dc, HBITMAP hBitmap, int x, int y) {
    HDC hdcMem = CreateCompatibleDC(dc);

    SelectObject(hdcMem, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);


    BitBlt(dc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

    DeleteDC(hdcMem);
}


INT draw_button(HWND hwnd, float x, float y, float width, float height, WCHAR* text) {
    current_id++;
    HWND hButton = CreateWindowW(L"BUTTON", text, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, width, height,
        hwnd, current_id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    return current_id;
}

VOID draw_text(HDC dc, float x, float y, WCHAR* text, COLORREF color) {
    SetTextColor(dc, color);
    SetBkMode(dc, TRANSPARENT);
    SelectObject(dc, hFont);
    TextOut(dc, x, y, text, lstrlen(text));
}


