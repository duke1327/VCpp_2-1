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
int colorMode = 0;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
    {
        int marginSize1 = 8;
        // 박스 생성
        hBox = CreateWindow(
            L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            marginSize1 + 16,
            marginSize1 + 16,
            (800 - (marginSize1 * 4)) - (2 * 16),
            (480 - (marginSize1 * 7)) - (2 * 16),
            hWnd,
            NULL,
            hInst,
            NULL);

        // 버튼 생성
        int buttonWidth = 120;
        int buttonHeight = 64;
        int marginSize = 16;

        hButton1 = CreateWindow(
            L"BUTTON", L"버튼1",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            marginSize, marginSize,
            buttonWidth, buttonHeight,
            hBox, (HMENU)1, hInst, NULL);
        hButton2 = CreateWindow(
            L"BUTTON", L"버튼2",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            buttonWidth + marginSize * 2, marginSize,
            buttonWidth, buttonHeight,
            hBox, (HMENU)2, hInst, NULL);
        hButton3 = CreateWindow(
            L"BUTTON", L"버튼3",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            buttonWidth * 2 + marginSize * 3, marginSize,
            buttonWidth, buttonHeight,
            hBox, (HMENU)2, hInst, NULL);
        hButton4 = CreateWindow(
            L"BUTTON", L"버튼4",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            buttonWidth * 3 + marginSize * 4, marginSize,
            buttonWidth, buttonHeight,
            hBox, (HMENU)4, hInst, NULL);
        hButton5 = CreateWindow(
            L"BUTTON", L"버튼5",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            buttonWidth * 4 + marginSize * 5, marginSize,
            buttonWidth, buttonHeight,
            hBox, (HMENU)5, hInst, NULL);

        // 드로잉 영역 생성
        RECT rectDrawingArea;
        GetClientRect(hBox, &rectDrawingArea);

        int drawingAreaWidth = rectDrawingArea.right - rectDrawingArea.left;
        int drawingAreaHeight = rectDrawingArea.bottom - rectDrawingArea.top;

        hDrawingArea = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            0, 80,
            drawingAreaWidth, drawingAreaHeight,
            hBox, (HMENU)20, hInst, NULL);

        HBRUSH drawingAreaBgBrush = CreateSolidBrush(RGB(255, 255, 255));
        SendMessage(hDrawingArea, WM_SETTEXT, (WPARAM)NULL, (LPARAM)L"");
        SendMessage(hDrawingArea, WM_CTLCOLORSTATIC, (WPARAM)GetDC(hDrawingArea), (LPARAM)drawingAreaBgBrush);
    }
    case WM_SETCURSOR:
    {
        if ((HWND)wParam == GetDlgItem(hWnd, 20))
        {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            return TRUE;
        }

        break;
    }
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
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rectClient; // 클라이언트 영역의 사각형

        GetClientRect(hWnd, &rectClient);

        HBRUSH bgColorBrush = CreateSolidBrush(RGB(255, 240, 200));

        FillRect(hdc, &rectClient, bgColorBrush);

        HBRUSH hBrush = CreateSolidBrush(RGB(28, 219, 241));
        SelectObject(hdc, hBrush);

        if (mode == 1) {
            
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
        L"ButtonWindowClass", L"곰돌이", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

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