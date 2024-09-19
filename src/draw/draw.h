#pragma once




#include <windows.h>



void draw_background(HDC dc, PPAINTSTRUCT ps, HWND hwnd);

void draw_image(HDC dc, HBITMAP hBitmap, int x, int y);
INT draw_button(HWND hwnd, float x, float y, float width, float height, WCHAR* text);
VOID draw_text(HDC dc, float x, float y, WCHAR* text, COLORREF color);
VOID draw_background(HDC dc, PPAINTSTRUCT ps, HWND hwnd, COLORREF color);