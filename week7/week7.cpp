#include <windows.h>
#include <cmath>

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButtonc1, hButtonc2, hButtonc3;
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startPoint2 = { 0 };
POINT endPoint2 = { 0 };

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
        //도형변경
        if (LOWORD(wParam) == 1) {
            mode = 1;
        }
        else if (LOWORD(wParam) == 2) {
            mode = 2;
        }
        else if (LOWORD(wParam) == 3) {
            mode = 3;
        }
        else if (LOWORD(wParam) == 4) {
            mode = 4;
        }
        else if (LOWORD(wParam) == 5) {
            mode = 5;
        }
        //색깔변경
        if (LOWORD(wParam) == 31) {
            colorMode = 1;
        }
        else if (LOWORD(wParam) == 32) {
            colorMode = 2;
        }
        else if (LOWORD(wParam) == 33) {
            colorMode = 3;
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
        else if (colorMode == 2) {
            hBrush = CreateSolidBrush(RGB(244, 238, 221));
        }
        else if (colorMode == 3) {
            hBrush = CreateSolidBrush(RGB(225, 167, 250));
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

            POINT vertices[6][4] = {
            //뒷면
            {{startPoint2.x, startPoint2.y},
             {startPoint2.x, endPoint2.y},
             {endPoint2.x, endPoint2.y},
             {endPoint2.x, startPoint2.y}},
            //아랫면
            {{startPoint.x, endPoint.y},
             {startPoint2.x, endPoint2.y},
             {endPoint2.x, endPoint2.y},
             {endPoint.x, endPoint.y}},
            //왼쪽면
            {{startPoint.x, startPoint.y},
             {startPoint2.x, startPoint2.y},
             {startPoint2.x, endPoint2.y},
             {startPoint.x, endPoint.y}},
            //오른쪽면
             {{endPoint.x, startPoint.y},
             {endPoint.x, endPoint.y},
             {endPoint2.x, endPoint2.y},
             {endPoint2.x, startPoint2.y}},
            //윗면
            {{startPoint.x, startPoint.y},
             {startPoint2.x, startPoint2.y},
             {endPoint2.x, startPoint2.y},
             {endPoint.x, startPoint.y}},
            //앞면
            {{startPoint.x, startPoint.y},
             {startPoint.x, endPoint.y},
             {endPoint.x, endPoint.y},
             {endPoint.x, startPoint.y}}
            };

            if (startPoint.y > endPoint.y) {
                POINT temp[4];
                for (int i = 0; i < 4; i++) {
                    temp[i] = vertices[1][i];
                    vertices[1][i] = vertices[4][i];
                    vertices[4][i] = temp[i];
                }
                for (int j = 0; j < 6; j++) {
                    Polygon(hdc, vertices[j], 4);
                }
            }
            else {
                for (int i = 0; i < 6; i++) {
                    Polygon(hdc, vertices[i], 4);
                }
            }
        }
        else if (mode == 2) {
            Rectangle(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (mode == 3) {
            Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (mode == 4) {
            POINT tri1[3] = {
                {(endPoint.x + startPoint.x) / 2, startPoint.y},
                {startPoint.x, endPoint.y},
                {endPoint.x, endPoint.y}
            };
            POINT tri2[3] = {
                {(startPoint.x + endPoint.x) / 2, endPoint.y},
                {startPoint.x, startPoint.y},
                {endPoint.x, startPoint.y}
            };
            if (startPoint.y > endPoint.y) {
                Polygon(hdc, tri2, 3);
            }
            else {
                Polygon(hdc, tri1, 3);
            }
        }
        /* // 폐기작 ???????????????
        else if (mode == 5) {
            long dx = (startPoint.x + endPoint.x);
            long dy = (startPoint.y + endPoint.y);
            POINT star[10] = {
                //맨 위부터 시작 오른쪽으로 진행
                {dx / 2, startPoint.y},
                {dx / 3 * 2, dy / 5 * 2},
                {endPoint.x, dy / 5 * 2 + 5},
                {dx / 7 * 5, dy / 3 * 2},
                {dx / 4 * 3, endPoint.y},
                {dx / 2, dy / 4 * 3},
                {dx / 4, endPoint.y},
                {dx / 7 * 2, dy / 3 * 2},
                {startPoint.x, dy / 5 * 2 + 5},
                {dx / 3, dy / 5 * 2}
            };
            Polygon(hdc, star, 10);
        }
        */
        else if (mode == 5) {
            
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
        L"BUTTON", L"hexahedron", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 80, 80, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"rectangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 120, 80, 80, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"ellipse", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 220, 80, 80, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"triangle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 320, 80, 80, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"star", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 420, 80, 80, hWnd, (HMENU)5, hInstance, NULL);

    hButtonc1 = CreateWindow(
        L"BUTTON", L"blue", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        120, 20, 80, 80, hWnd, (HMENU)31, hInstance, NULL);

    hButtonc2 = CreateWindow(
        L"BUTTON", L"ivory", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        120, 120, 80, 80, hWnd, (HMENU)32, hInstance, NULL);

    hButtonc3 = CreateWindow(
        L"BUTTON", L"lightpurple", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        120, 220, 80, 80, hWnd, (HMENU)33, hInstance, NULL);

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