#include <windows.h>

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hBox;
HWND hDrawingArea;
HWND hButton1, hButton2, hButton3, hButton4, hButton5;
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT startPoint2 = { 0 };
POINT endPoint2 = { 0 };

bool isMouseLButtonPressed = false;

int mode = 0;
int marginSize = 8;
int boxMargin = 16;
int buttonWidth = 140;
int buttonHeight = 64;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        //나중에 해볼 것
    //case WM_CREATE:
    //{
    //    // 박스 생성
    //    hBox = CreateWindow(
    //        L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
    //        marginSize1,
    //        marginSize1,
    //        800 - (marginSize1 * 2),
    //        480 - (marginSize1 * 2),
    //        hWnd,
    //        (HMENU)10,
    //        hInst,
    //        NULL);

       /* PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hBox, &ps);
        HBRUSH boxColorBrush = CreateSolidBrush(RGB(255, 0, 255));*/

    //    // 버튼 생성
    //    int buttonWidth = 138;
    //    int buttonHeight = 64;
    //    int marginSize = 16;

    //    hButton1 = CreateWindow(
    //        L"BUTTON", L"BOX",
    //        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    //        marginSize1, marginSize1,
    //        buttonWidth, buttonHeight,
    //        hBox, (HMENU)1, hInst, NULL);
    //    hButton2 = CreateWindow(
    //        L"BUTTON", L"Circle",
    //        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    //        buttonWidth + marginSize * 2, marginSize1,
    //        buttonWidth, buttonHeight,
    //        hBox, (HMENU)2, hInst, NULL);
    //    hButton3 = CreateWindow(
    //        L"BUTTON", L"Bonobono",
    //        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    //        buttonWidth * 2 + marginSize * 3, marginSize1,
    //        buttonWidth, buttonHeight,
    //        hBox, (HMENU)3, hInst, NULL);
    //    hButton4 = CreateWindow(
    //        L"BUTTON", L"Ryan",
    //        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    //        buttonWidth * 3 + marginSize * 4, marginSize1,
    //        buttonWidth, buttonHeight,
    //        hBox, (HMENU)4, hInst, NULL);
    //    hButton5 = CreateWindow(
    //        L"BUTTON", L"cube",
    //        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
    //        buttonWidth * 4 + marginSize * 5, marginSize1,
    //        buttonWidth, buttonHeight,
    //        hBox, (HMENU)5, hInst, NULL);

    //    RECT drawingArea = { marginSize1,
    //        buttonHeight + marginSize,
    //        800 - (marginSize * 2),
    //        480 - (buttonHeight + marginSize * 2 + marginSize1) };

    //    FillRect(hdc, &drawingArea, boxColorBrush);

    //    EndPaint(hBox, &ps);
    //}

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
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rectClient; // 클라이언트 영역의 사각형

        GetClientRect(hWnd, &rectClient);

        HBRUSH bgColorBrush = CreateSolidBrush(RGB(255, 240, 200));

        FillRect(hdc, &rectClient, bgColorBrush);

        HBRUSH boxColorBrush = CreateSolidBrush(RGB(255, 255, 255));

        RECT box = { marginSize,
            marginSize,
            800 - (marginSize),
            480 - (marginSize)
        };

        FillRect(hdc, &box, boxColorBrush);

        if (mode == 1) {

        }
        else if (mode == 2) {

        }
        else if (mode == 3) {
            HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 200, 90, 600, 460);
            DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
        }

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

    RECT rect = { 0, 0, 800, 480 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"곰돌이", WS_OVERLAPPEDWINDOW,
        0, 0, width, height, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, buttonWidth, buttonHeight, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        184, 16, buttonWidth, buttonHeight, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        352, 16, buttonWidth, buttonHeight, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        520, 16, buttonWidth, buttonHeight, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        688, 16, buttonWidth, buttonHeight, hWnd, (HMENU)5, hInstance, NULL);

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