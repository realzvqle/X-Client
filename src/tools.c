#include "tools.h"








VOID ShowFormattedMessageBox(DWORD errorCode)
{
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    MessageBox(
        NULL,
        (LPCTSTR)lpMsgBuf,
        TEXT("Error"),
        MB_OK | MB_ICONERROR);

    LocalFree(lpMsgBuf);
}