#include <windows.h>
#include <cmath>

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hButton1, hButton2, hButton3, hButton4;
HBRUSH hBrush_red = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스
HBRUSH hBrush_blue = CreateSolidBrush(RGB(0, 0, 255)); // 파랑색 박스
HBRUSH hBrush_green = CreateSolidBrush(RGB(0, 255, 0)); // 초록색 박스
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startPoint2 = { 0 };
POINT endPoint2 = { 0 };

// 박스를 나타내는 변수
bool isBoxVisible = false;
bool isEllipseVisible = false;
bool isMouseLButtonPressed = false;

int mode = 0;
int colorMode = 0;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_LBUTTONDOWN:
    {
        isMouseLButtonPressed = true;
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
    }
    break;
    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
    }
    break;
    case WM_LBUTTONUP:
        isMouseLButtonPressed = false;
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            mode = 1;
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            mode = 2;
        }
        else if (LOWORD(wParam) == 3) {
            // 세 번째 버튼 클릭
            mode = 3;
        }
        else if (LOWORD(wParam) == 4) {
            // 네 번째 버튼 클릭
            colorMode = 1;
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        GetClientRect(hWnd, &rect);
        HBRUSH whiteBrush = (HBRUSH)(COLOR_WINDOW + 1);
        FillRect(hdc, &rect, whiteBrush);

        HBRUSH hBrush;
        if (colorMode == 1) {
            hBrush = CreateSolidBrush(RGB(0, 0, 255));
        }
        else {
            hBrush = CreateSolidBrush(RGB(28, 219, 241));
        }
        SelectObject(hdc, hBrush);

        if (mode == 1) {
            startPoint2.x = startPoint.x + 30;
            startPoint2.y = startPoint.y - 30;
            endPoint2.x = endPoint.x + 30;
            endPoint2.y = endPoint.y - 30;
            /*POINT vertices1[4] = {
                {endPoint.x,startPoint.y},
                {endPoint.x,endPoint.y},
                {endPoint2.x,endPoint2.y},
                {endPoint2.x,startPoint2.y}
            };
            POINT vertices2[4] = {
                {startPoint.x, startPoint.y},
                {startPoint2.x,startPoint2.y},
                {endPoint2.x,startPoint2.y},
                {endPoint.x,startPoint.y}
            };
            POINT vertices3[4] = {
                {startPoint.x, startPoint.y},
                {startPoint2.x,startPoint2.y},
                {startPoint2.x,endPoint2.y},
                {startPoint.x,endPoint.y}
            };
            POINT vertices4[4] = {
                {startPoint.x,endPoint.y},
                {startPoint2.x,endPoint2.y},
                {endPoint2.x,endPoint2.y},
                {endPoint.x,endPoint.y}
            };
            Rectangle(hdc, startPoint2.x, startPoint2.y, endPoint2.x, endPoint2.y);
            Polygon(hdc, vertices4, 4);
            Polygon(hdc, vertices3, 4);
            Polygon(hdc, vertices2, 4);
            Polygon(hdc, vertices1, 4);
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);*/
            POINT vertices[6][4] = {
            {{startPoint2.x,startPoint2.y},
             {startPoint2.x,endPoint2.y},
             {endPoint2.x,endPoint2.y},
             {endPoint2.x,startPoint2.y}},

            {{startPoint.x,endPoint.y},
             {startPoint2.x,endPoint2.y},
             {endPoint2.x,endPoint2.y},
             {endPoint.x,endPoint.y}},

            {{startPoint.x, startPoint.y},
             {startPoint2.x,startPoint2.y},
             {startPoint2.x,endPoint2.y},
             {startPoint.x,endPoint.y}},

            {{startPoint.x, startPoint.y},
             {startPoint2.x,startPoint2.y},
             {endPoint2.x,startPoint2.y},
             {endPoint.x,startPoint.y}},

            {{endPoint.x,startPoint.y},
             {endPoint.x,endPoint.y},
             {endPoint2.x,endPoint2.y},
             {endPoint2.x,startPoint2.y}},

            {{startPoint.x,startPoint.y},
             {startPoint.x,endPoint.y},
             {endPoint.x,endPoint.y},
             {endPoint.x,startPoint.y}}
            };
            for (int i = 0; i < 6; i++) {
                Polygon(hdc, vertices[i], 4);
            }
        }
        else if (mode == 2) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (mode == 3) {
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        DeleteObject(hBrush);
        EndPaint(hWnd, &ps);
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 윈도우 초기화 함수
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Add Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 60, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"rectangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 100, 60, 60, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"ellipse", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 180, 60, 60, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"blue", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 260, 60, 60, hWnd, (HMENU)4, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

// 프로그램 진입점
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    if (!InitInstance(hInstance, nCmdShow)) {
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}