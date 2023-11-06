#include <windows.h>

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hBox;
HWND hDrawingArea;
HWND hButton1, hButton2, hButton3, hButton4, hButton5;
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT bonoMustacheStart[4] = { {320,295},{323,332},{478,281},{480,325} };
POINT bonoMustacheEnd[4] = { {359,302},{365,313},{435,301},{437,316} };
POINT bonoEyeLineStart[4] = { {260,230},{260,270},{530,230},{530,270} };
POINT bonoEyeLineEnd[4] = { {290,250},{290,250},{500,250},{500,250} };
HBRUSH bonoBody = CreateSolidBrush(RGB(127, 200, 255));
HBRUSH bonoMouse = CreateSolidBrush(RGB(255, 150, 255));
HBRUSH bonoWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH bonoBlack = CreateSolidBrush(RGB(0, 0, 0));
RECT drawArea;

bool isMouseLButtonPressed = false;
bool bonoEyeClose = false;

int mode = 0;
int marginSize = 8;
int boxMargin = 16;
int buttonWidth = 140;
int buttonHeight = 64;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        //도형변경
        if (LOWORD(wParam) == 1) {
            SetFocus(hWnd);
            mode = 1;
        }
        else if (LOWORD(wParam) == 2) {
            SetFocus(hWnd);
            mode = 2;
        }
        else if (LOWORD(wParam) == 3) {
            SetFocus(hWnd);
            mode = 3;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) {
            SetFocus(hWnd);
            mode = 4;
        }
        else if (LOWORD(wParam) == 5) {
            SetFocus(hWnd);
            mode = 5;
        }
        break;

    case WM_LBUTTONUP:
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_RBUTTONDOWN:
        break;

    case WM_RBUTTONUP:
        break;

    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            bonoEyeClose = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        if (bonoEyeClose == true) {
            bonoEyeClose = false;
            InvalidateRect(hWnd, NULL, TRUE);
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
            800 - marginSize,
            480 - marginSize
        };

        FillRect(hdc, &box, boxColorBrush);

        drawArea = { marginSize * 2,
            marginSize * 4 + buttonHeight,
            800 - (marginSize * 2),
            480 - (marginSize * 2) };
        Rectangle(hdc, drawArea.left, drawArea.top, drawArea.right, drawArea.bottom);

        if (mode == 1) {

        }
        else if (mode == 2) {

        }
        else if (mode == 3) {
            SelectObject(hdc, bonoBody);
            Ellipse(hdc, 205, 100, 595, 460);
            SelectObject(hdc, bonoMouse);
            Ellipse(hdc, 375, 290, 425, 385);
            SelectObject(hdc, bonoWhite);
            Ellipse(hdc, 340, 280, 400, 330);
            Ellipse(hdc, 400, 280, 460, 330);
            SelectObject(hdc, bonoBlack);
            Ellipse(hdc, 380, 270, 420, 305);
            for (int i = 0; i < 4; i++) {
                MoveToEx(hdc, bonoMustacheStart[i].x, bonoMustacheStart[i].y, NULL);
                LineTo(hdc, bonoMustacheEnd[i].x, bonoMustacheEnd[i].y);
            }
            if (!bonoEyeClose) {
                Ellipse(hdc, 265, 245, 280, 270);
                Ellipse(hdc, 522, 245, 537, 270);
                SelectObject(hdc, bonoWhite);
                Ellipse(hdc, 268, 250, 276, 265);
                Ellipse(hdc, 525, 250, 533, 265);
            }
            else {
                for (int i = 0; i < 4; i++) {
                    MoveToEx(hdc, bonoEyeLineStart[i].x, bonoEyeLineStart[i].y, NULL);
                    LineTo(hdc, bonoEyeLineEnd[i].x, bonoEyeLineEnd[i].y);
                }
            }
        }
        else if (mode == 4) {

        }
        else if (mode == 5) {

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
        169, 16, buttonWidth, buttonHeight, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        327, 16, buttonWidth, buttonHeight, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        485, 16, buttonWidth, buttonHeight, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        643, 16, buttonWidth, buttonHeight, hWnd, (HMENU)5, hInstance, NULL);

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