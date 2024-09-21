#include "font.h"



HFONT create_standard_font(int fontsize) {
    return CreateFontW(
        -MulDiv(fontsize, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72),
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
