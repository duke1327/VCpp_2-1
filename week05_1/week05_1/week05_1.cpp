#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT check = { 0 };
POINT start = { 0 };
POINT end = { 0 };
POINT st = { 0 };
POINT en = { 0 };
POINT dist = { 0 };

int LMousePressed = 0;
int rectCheck = 0;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		{
			start.x = LOWORD(lParam);
			start.y = HIWORD(lParam);
			LMousePressed = 1;
		}
		break;
	case WM_RBUTTONDOWN:
		{
			check.x = LOWORD(lParam);
			check.y = HIWORD(lParam);
			if (start.x < check.x < end.x && start.y < check.y < end.y) {
				rectCheck = 1;
			}
		}
	case WM_MOUSEMOVE: // 실시간으로 끝위치 변경
		{
			if (LMousePressed) {
				end.x = LOWORD(lParam);
				end.y = HIWORD(lParam);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (rectCheck) {
				st = start;
				en = end;
			}
		}
		break;
	case WM_LBUTTONUP:
		LMousePressed = 0;
		break;
	case WM_RBUTTONUP:
		rectCheck = 0;
		break;
	case WM_PAINT:
		{
			HDC hdc = GetDC(hwnd);
			if (LMousePressed) {
				HBRUSH hBrush = CreateSolidBrush(RGB(28, 219, 241)); // 옥색 브러시 생성
				RECT rect;
				GetClientRect(hwnd, &rect);
				FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // 화면 깨끗하게

				//MoveToEx(hdc, start.x, start.y, NULL); // 선 긋기
				//LineTo(hdc, end.x, end.y);

				RECT rect2 = { start.x, start.y, end.x, end.y }; // 네모 만들기
				FillRect(hdc, &rect2, hBrush); // 사각형을 옥색으로 채우기

				ReleaseDC(hwnd, hdc);
			}
		}
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
#endif
{
	// 윈도우 클래스 선언.
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 600, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("컴소 Application"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
// 엔진 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{
			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);
		}
		/*else
		{

		}*/
	}

	return (int)msg.wParam;
}