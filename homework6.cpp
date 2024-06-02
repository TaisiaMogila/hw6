#include    "Windows.h" 
#include    "lab5.h"
#include    "ShapeEditor.h"

#define     OBJECTRECTANGLE 1 
#define     OBJECTELLIPSE   2 
#define     OBJECTLINE      3 
#define     OBJECTPOINT     4

ShapeObjectsEditor soe; 

void mainMenu(HWND hwnd)
{
    HMENU hMenu = CreateMenu(); 
    HMENU hObjects = CreateMenu(); 

    AppendMenuW(hObjects, MF_UNCHECKED, OBJECTRECTANGLE, L"Прямокутник");
    AppendMenuW(hObjects, MF_UNCHECKED, OBJECTELLIPSE, L"Еліпс");
    AppendMenuW(hObjects, MF_UNCHECKED, OBJECTLINE, L"Лінія");
    AppendMenuW(hObjects, MF_UNCHECKED, OBJECTPOINT, L"Точка"); 

    AppendMenuW(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hObjects), L"Фігури");

    SetMenu(hwnd, hMenu);
}

LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
            soe.OnPaint(hwnd); 
            break; 
        case WM_LBUTTONUP:
            soe.OnLBup(hwnd, lParam); 
            break; 
        case WM_MOUSEMOVE:
            soe.OnMouseMove(hwnd, lParam); 
            break; 
        case WM_LBUTTONDOWN:
            soe.OnLBDown(hwnd, lParam); 
            break; 
        case WM_CREATE:
            mainMenu(hwnd); 
            break;
        case WM_COMMAND:
            switch (wParam)
            {
                case OBJECTRECTANGLE:
                {
                    soe.StartRectEditor(hwnd, OBJECTRECTANGLE); 
                    break; 
                }
                case OBJECTELLIPSE: 
                {
                    soe.StartEllipseEditor(hwnd, OBJECTELLIPSE);
                    break;
                }
                case OBJECTLINE:
                {
                    soe.StartLineEditor(hwnd, OBJECTLINE);
                    break;
                }
                case OBJECTPOINT: 
                    soe.StartPointEditor(hwnd, OBJECTPOINT);
                    break; 
            }
            break; 
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"mainWindow";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(WS_EX_LEFT, L"mainWindow", L"homework5", WS_OVERLAPPEDWINDOW, 200, 200, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}