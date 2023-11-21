#include "YuhanCG.h"

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
HWND hButton1, hButton2, hButton3, hButton4, hButton5; // 버튼

POINT startPoint = { 0 }; // 시작점
POINT endPoint = { 0 }; // 끝점
POINT startPoint2 = { 0 }; // 큐브 뒷면 시작점
POINT endPoint2 = { 0 }; // 큐브 뒷면 끝점
POINT startPointSaved = { 0 }; // 기존 시작점 저장
POINT endPointSaved = { 0 }; // 기존 끝점 저장
POINT movedStartPoint = { 0 }; // 이동된 시작점
POINT movedEndPoint = { 0 }; // 이동된 끝점

POINT distance = { 0 }; // 마우스 이동거리
POINT distanceLine = { 0 }; // 원 크기 조절 이동거리
// 그리기 영역
RECT drawArea;
// 사각형 미리 정의
RECT rectangle;

bool isMouseLButtonPressed = false;
bool isMouseRButtonPressed = false;

//모드 설정
int mode = 0;
//마진 크기 설정
int marginSize = 8;
int buttonMargin = 16;
int buttonWidth = 140;
int buttonHeight = 64;
int bonoEyeClose = 0;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        //도형변경
        if (LOWORD(wParam) == 1) {
            SetFocus(hWnd); // 포커스를 버튼에서 윈도우 핸들로 변경
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

    case WM_LBUTTONDOWN:
    {
        isMouseLButtonPressed = true;
        if (mode == 1 || mode == 2 || mode == 4 || mode == 5) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        if (isMouseLButtonPressed == true)
        {
            isMouseLButtonPressed = false;
        }
        InvalidateRect(hWnd, &drawArea, TRUE);
    }
    break;

    case WM_RBUTTONDOWN:
    {
        if (mode == 1) {
            movedStartPoint.x = LOWORD(lParam);
            movedStartPoint.y = HIWORD(lParam);

            //	마우스 오른쪽 버튼을 기존에 만들어진 사각형 영역 안에서 눌렀다면
            if (PtInRect(&rectangle, movedStartPoint))
            {
                isMouseRButtonPressed = true;

                //	기존 사각형의 좌표값을 Saved 변수에 저장
                startPointSaved.x = rectangle.left;
                startPointSaved.y = rectangle.top;
                endPointSaved.x = rectangle.right;
                endPointSaved.y = rectangle.bottom;
            }
        }
        else if (mode == 2) {
            isMouseRButtonPressed = true;
            movedStartPoint.x = LOWORD(lParam);
        }
        else if (mode == 5) {
            movedStartPoint.x = LOWORD(lParam);
            movedStartPoint.y = HIWORD(lParam);

            //	마우스 오른쪽 버튼을 기존에 만들어진 사각형 영역 안에서 눌렀다면
            if (PtInRect(&rectangle, movedStartPoint))
            {
                isMouseRButtonPressed = true;

                //	기존 사각형의 좌표값을 Saved 변수에 저장
                if (startPoint.x > endPoint.x && startPoint.y > startPoint.y) {
                    startPointSaved.x = rectangle.left;
                    startPointSaved.y = rectangle.bottom;
                    endPointSaved.x = rectangle.right;
                    endPointSaved.y = rectangle.top;
                }
                else if (startPoint.x > endPoint.x) {
                    startPointSaved.x = rectangle.right;
                    startPointSaved.y = rectangle.top;
                    endPointSaved.x = rectangle.left;
                    endPointSaved.y = rectangle.bottom;
                }
                else if (startPoint.y > endPoint.y) {
                    startPointSaved.x = rectangle.left;
                    startPointSaved.y = rectangle.bottom;
                    endPointSaved.x = rectangle.right;
                    endPointSaved.y = rectangle.top;
                }
                else {
                    startPointSaved.x = rectangle.left;
                    startPointSaved.y = rectangle.top;
                    endPointSaved.x = rectangle.right;
                    endPointSaved.y = rectangle.bottom;
                }
            }
        }
    }
    break;

    case WM_RBUTTONUP:
    {
        if (isMouseRButtonPressed) {
            isMouseRButtonPressed = false;
        }
        InvalidateRect(hWnd, &drawArea, TRUE);
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (mode == 1 && isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            

            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 1 && isMouseRButtonPressed)
        {
            movedEndPoint.x = LOWORD(lParam);
            movedEndPoint.y = HIWORD(lParam);

            //	사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
            distance.x = movedEndPoint.x - movedStartPoint.x;
            distance.y = movedEndPoint.y - movedStartPoint.y;

            //	사각형의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
            rectangle.left = startPointSaved.x + distance.x;
            rectangle.top = startPointSaved.y + distance.y;
            rectangle.right = endPointSaved.x + distance.x;
            rectangle.bottom = endPointSaved.y + distance.y;

            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 2 && isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            distance.x = endPoint.x - startPoint.x;
            distance.y = endPoint.y - startPoint.y;
            if (distance.x > distance.y) {
                endPointSaved.x = startPoint.x + distance.y;
                endPointSaved.y = endPoint.y;
            }
            else {
                endPointSaved.x = endPoint.x;
                endPointSaved.y = startPoint.y + distance.x;
            }
            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 2 && isMouseRButtonPressed) {
            movedEndPoint.x = LOWORD(lParam);
            distanceLine.x = movedEndPoint.x - movedStartPoint.x;
            if (distanceLine.x > 0) {
                int i = (distanceLine.x / 100) + 1; // 100 픽셀에 2배 200픽셀에 3배
                if (distance.x > distance.y) {
                    endPointSaved.x = startPoint.x + (distance.y * i);
                    endPointSaved.y = startPoint.y + (distance.y * i);
                }
                else {
                    endPointSaved.x = startPoint.x + (distance.x * i);
                    endPointSaved.y = startPoint.y + (distance.x * i);
                }
            }
            else {
                int i = (distanceLine.x * -1 / 100) + 1; // 100 픽셀에 2배 200픽셀에 3배
                if (distance.x > distance.y) {
                    endPointSaved.x = startPoint.x + (distance.y / i);
                    endPointSaved.y = startPoint.y + (distance.y / i);
                }
                else {
                    endPointSaved.x = startPoint.x + (distance.x / i);
                    endPointSaved.y = startPoint.y + (distance.x / i);
                }
            }
            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 4 && isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 5 && isMouseLButtonPressed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            
            rectangle.left = min(startPoint.x, endPoint.x);
            rectangle.top = min(startPoint.y, endPoint.y);
            rectangle.right = max(startPoint.x, endPoint.x);
            rectangle.bottom = max(startPoint.y, endPoint.y);
            InvalidateRect(hWnd, &drawArea, TRUE);
        }
        else if (mode == 5 && isMouseRButtonPressed)
        {
            movedEndPoint.x = LOWORD(lParam);
            movedEndPoint.y = HIWORD(lParam);

            //	사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
            distance.x = movedEndPoint.x - movedStartPoint.x;
            distance.y = movedEndPoint.y - movedStartPoint.y;

            //	사각형의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
            startPoint.x = startPointSaved.x + distance.x;
            startPoint.y = startPointSaved.y + distance.y;
            endPoint.x = endPointSaved.x + distance.x;
            endPoint.y = endPointSaved.y + distance.y;

            InvalidateRect(hWnd, NULL, TRUE);
        }
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE && mode == 3) {
            bonoEyeClose = 1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        if (bonoEyeClose) {
            bonoEyeClose = 0;
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

        if (mode == 1 && isMouseLButtonPressed) {
            //	사각형 좌표값 정렬(사각형을 반대로 그리는 경우를 대비하여)
            rectangle.left = min(startPoint.x, endPoint.x);
            rectangle.top = min(startPoint.y, endPoint.y);
            rectangle.right = max(startPoint.x, endPoint.x);
            rectangle.bottom = max(startPoint.y, endPoint.y);
            DrawBox(hWnd, hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
        }
        else if (mode == 1 && isMouseRButtonPressed)
        {
            //	사각형 이동이 끝난 좌표값과 사각형 이동이 시작된 좌표값의 차를 통해 마우스의 이동 거리를 계산
            distance.x = movedEndPoint.x - movedStartPoint.x;
            distance.y = movedEndPoint.y - movedStartPoint.y;

            //	사각형의 좌표값을 기존에 저장해놓은 좌표값에 마우스의 이동거리 만큼을 더한 좌표값으로 설정
            rectangle.left = startPointSaved.x + distance.x;
            rectangle.top = startPointSaved.y + distance.y;
            rectangle.right = endPointSaved.x + distance.x;
            rectangle.bottom = endPointSaved.y + distance.y;

            DrawBox(hWnd, hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
        }
        else if (mode == 2) {
            DrawCircle(hWnd, hdc, startPoint.x, startPoint.y, endPointSaved.x, endPointSaved.y);
        }
        else if (mode == 3) {
            DrawBonobono(hWnd, hdc, bonoEyeClose);
        }
        else if (mode == 4) {
            DrawRyan(hWnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
        else if (mode == 5) {
            DrawCube(hWnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);

        
        if (PtInRect(&rectangle, pt)) {
            SetCursor(LoadCursor(NULL, IDC_HAND));
        }
        else if (PtInRect(&drawArea, pt)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        return TRUE;
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
        (marginSize * 2), (marginSize * 2),
        buttonWidth, buttonHeight,
        hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (marginSize * 2) + buttonWidth + buttonMargin, (marginSize * 2),
        buttonWidth, buttonHeight,
        hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (marginSize * 2) + (buttonWidth * 2) + (buttonMargin * 2), (marginSize * 2),
        buttonWidth, buttonHeight,
        hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (marginSize * 2) + (buttonWidth * 3) + (buttonMargin * 3), (marginSize * 2),
        buttonWidth, buttonHeight, 
        hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (marginSize * 2) + (buttonWidth * 4) + (buttonMargin * 4), (marginSize * 2),
        buttonWidth, buttonHeight, 
        hWnd, (HMENU)5, hInstance, NULL);

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