#include "YuhanCG.h"

POINT mouseDistance = { 0 }; // 마우스 이동거리
POINT ryanDistance = { 0 }; // 라이언 얼굴 길이
POINT cubeDistance = { 0 }; // 큐브 길이
// 보노보노 수염 지정 좌표
POINT bonoMustacheStart[4] = { {320,295},{323,332},{478,281},{480,325} };
POINT bonoMustacheEnd[4] = { {359,302},{365,313},{435,301},{437,316} };
POINT bonoEyeLineStart[4] = { {260,230},{260,270},{530,230},{530,270} };
POINT bonoEyeLineEnd[4] = { {290,250},{290,250},{500,250},{500,250} };
// 라이언 눈썹 좌표
POINT ryanEyeBrowStart1 = { 0 };
POINT ryanEyeBrowEnd1 = { 0 };
POINT ryanEyeBrowStart2 = { 0 };
POINT ryanEyeBrowEnd2 = { 0 };
POINT cubeStartPoint = { 0 }; // 큐브 앞면 시작점
POINT cubeEndPoint = { 0 }; // 큐브 앞면 끝점
POINT cubeStartPoint2 = { 0 }; // 큐브 뒷면 시작점
POINT cubeEndPoint2 = { 0 }; // 큐브 뒷면 끝점
// 색깔 브러쉬
HBRUSH bonoBody = CreateSolidBrush(RGB(127, 200, 255));
HBRUSH bonoMouse = CreateSolidBrush(RGB(255, 150, 255));
HBRUSH whiteColor = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH blackColor = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH ryanColor = CreateSolidBrush(RGB(255, 200, 15));
// 라이언 좌표
RECT ryanEar1;
RECT ryanEar2;
RECT ryanFace;
RECT ryanNose1;
RECT ryanNose2;
RECT ryanEye1;
RECT ryanEye2;

int diagonal = 0;

void DrawBonobono(HWND hWnd, HDC hdc, int blink)
{
    SelectObject(hdc, bonoBody);
    Ellipse(hdc, 205, 100, 595, 460);
    SelectObject(hdc, bonoMouse);
    Ellipse(hdc, 375, 290, 425, 385);
    SelectObject(hdc, whiteColor);
    Ellipse(hdc, 340, 280, 400, 330);
    Ellipse(hdc, 400, 280, 460, 330);
    SelectObject(hdc, blackColor);
    Ellipse(hdc, 380, 270, 420, 305);
    for (int i = 0; i < 4; i++) {
        MoveToEx(hdc, bonoMustacheStart[i].x, bonoMustacheStart[i].y, NULL);
        LineTo(hdc, bonoMustacheEnd[i].x, bonoMustacheEnd[i].y);
    }
    if (!blink) { // 눈 부분만 따로 그리기
        Ellipse(hdc, 265, 245, 280, 270);
        Ellipse(hdc, 522, 245, 537, 270);
        SelectObject(hdc, whiteColor);
        Ellipse(hdc, 268, 250, 276, 265);
        Ellipse(hdc, 525, 250, 533, 265);
    }
    else { // 스페이스바 눌렀을 시 작동
        for (int i = 0; i < 4; i++) {
            MoveToEx(hdc, bonoEyeLineStart[i].x, bonoEyeLineStart[i].y, NULL);
            LineTo(hdc, bonoEyeLineEnd[i].x, bonoEyeLineEnd[i].y);
        }
    }
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom)
{
    mouseDistance.x = right - left;
    mouseDistance.y = bottom - top;

    ryanEar1 = { left, top, left + (mouseDistance.x / 5 * 2), top + (mouseDistance.y / 5 * 2) };
    ryanEar2 = { right - (mouseDistance.x / 5 * 2), top, right, top + (mouseDistance.y / 5 * 2) };
    ryanFace = { left + (mouseDistance.x / 20),
        top + (mouseDistance.y / 10),
        right - (mouseDistance.x / 20),
        bottom };

    ryanDistance.x = ryanFace.right - ryanFace.left;
    ryanDistance.y = ryanFace.bottom - ryanFace.top;

    ryanNose1 = { ryanFace.left + (ryanDistance.x / 12 * 5),
        ryanFace.top + (ryanDistance.y / 2),
        ryanFace.left + (ryanDistance.x / 2),
        ryanFace.top + (ryanDistance.y / 5 * 3) };
    ryanNose2 = { ryanFace.left + (ryanDistance.x / 2),
        ryanFace.top + (ryanDistance.y / 2),
        ryanFace.right - (ryanDistance.x / 12 * 5),
        ryanFace.top + (ryanDistance.y / 5 * 3) };
    ryanEye1 = { ryanFace.left + (ryanDistance.x / 4),
        ryanFace.top + (ryanDistance.y / 8 * 3),
        ryanFace.left + (ryanDistance.x / 16 * 5),
        ryanFace.top + (ryanDistance.y / 16 * 7) };
    ryanEye2 = { ryanFace.right - (ryanDistance.x / 4),
        ryanFace.top + (ryanDistance.y / 8 * 3),
        ryanFace.right - (ryanDistance.x / 16 * 5),
        ryanFace.top + (ryanDistance.y / 16 * 7) };
    ryanEyeBrowStart1 = { ryanFace.left + (ryanDistance.x / 16 * 3),
        ryanFace.top + (ryanDistance.y / 4) };
    ryanEyeBrowEnd1 = { ryanFace.left + (ryanDistance.x / 8 * 3),
        ryanFace.top + (ryanDistance.y / 4) };
    ryanEyeBrowStart2 = { ryanFace.right - (ryanDistance.x / 8 * 3),
        ryanFace.top + (ryanDistance.y / 4) };
    ryanEyeBrowEnd2 = { ryanFace.right - (ryanDistance.x / 16 * 3),
        ryanFace.top + (ryanDistance.y / 4) };

    SelectObject(hdc, ryanColor);
    Ellipse(hdc, ryanEar1.left, ryanEar1.top, ryanEar1.right, ryanEar1.bottom);
    Ellipse(hdc, ryanEar2.left, ryanEar2.top, ryanEar2.right, ryanEar2.bottom);
    Ellipse(hdc, ryanFace.left, ryanFace.top, ryanFace.right, ryanFace.bottom);
    SelectObject(hdc, whiteColor);
    Ellipse(hdc, ryanNose1.left, ryanNose1.top, ryanNose1.right, ryanNose1.bottom);
    Ellipse(hdc, ryanNose2.left, ryanNose2.top, ryanNose2.right, ryanNose2.bottom);
    SelectObject(hdc, blackColor);
    Ellipse(hdc, ryanEye1.left, ryanEye1.top, ryanEye1.right, ryanEye1.bottom);
    Ellipse(hdc, ryanEye2.left, ryanEye2.top, ryanEye2.right, ryanEye2.bottom);
    for (int i = 0; i < 3; i++) {
        MoveToEx(hdc, ryanEyeBrowStart1.x, ryanEyeBrowStart1.y + (i * 2), NULL);
        LineTo(hdc, ryanEyeBrowEnd1.x, ryanEyeBrowEnd1.y + (i * 2));
        MoveToEx(hdc, ryanEyeBrowStart2.x, ryanEyeBrowStart2.y + (i * 2), NULL);
        LineTo(hdc, ryanEyeBrowEnd2.x, ryanEyeBrowEnd2.y + (i * 2));
    }
}

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    if (left < right)
        cubeDistance.x = right - left;
    else
        cubeDistance.x = left - right;
    if (top < bottom)
        cubeDistance.y = bottom - top;
    else
        cubeDistance.y = top - bottom;

    if (cubeDistance.x > cubeDistance.y) { // 큐브 길이 조절 조건 설정
        diagonal = cubeDistance.y / 4;
    }
    else {
        diagonal = cubeDistance.x / 4;
    }

    cubeStartPoint.x = left;
    cubeStartPoint.y = top + diagonal;
    cubeEndPoint.x = right - diagonal;
    cubeEndPoint.y = bottom;
    cubeStartPoint2.x = left + diagonal;
    cubeStartPoint2.y = top;
    cubeEndPoint2.x = right;
    cubeEndPoint2.y = bottom - diagonal;

    if (left > right && top > bottom) {
        cubeStartPoint.x = left;
        cubeStartPoint.y = top - diagonal;
        cubeEndPoint.x = right + diagonal;
        cubeEndPoint.y = bottom;
        cubeStartPoint2.x = left - diagonal;
        cubeStartPoint2.y = top;
        cubeEndPoint2.x = right;
        cubeEndPoint2.y = bottom + diagonal;
    }
    else if (left > right) {
        cubeStartPoint.x = left;
        cubeStartPoint.y = top + diagonal;
        cubeEndPoint.x = right + diagonal;
        cubeEndPoint.y = bottom;
        cubeStartPoint2.x = left - diagonal;
        cubeStartPoint2.y = top;
        cubeEndPoint2.x = right;
        cubeEndPoint2.y = bottom - diagonal;
    }
    else if (top > bottom) {
        cubeStartPoint.x = left;
        cubeStartPoint.y = top - diagonal;
        cubeEndPoint.x = right - diagonal;
        cubeEndPoint.y = bottom;
        cubeStartPoint2.x = left + diagonal;
        cubeStartPoint2.y = top;
        cubeEndPoint2.x = right;
        cubeEndPoint2.y = bottom + diagonal;
    }

    POINT vertices[6][4] = {
        //뒷면
        {{cubeStartPoint2.x, cubeStartPoint2.y},
         {cubeStartPoint2.x, cubeEndPoint2.y},
         {cubeEndPoint2.x, cubeEndPoint2.y},
         {cubeEndPoint2.x, cubeStartPoint2.y}},
         //아랫면
         {{cubeStartPoint.x, cubeEndPoint.y},
         {cubeStartPoint2.x, cubeEndPoint2.y},
         {cubeEndPoint2.x, cubeEndPoint2.y},
         {cubeEndPoint.x, cubeEndPoint.y}},
         //왼쪽면
         {{cubeStartPoint.x, cubeStartPoint.y},
         {cubeStartPoint2.x, cubeStartPoint2.y},
         {cubeStartPoint2.x, cubeEndPoint2.y},
         {cubeStartPoint.x, cubeEndPoint.y}},
         //오른쪽면
         {{cubeEndPoint.x, cubeStartPoint.y},
         {cubeEndPoint.x, cubeEndPoint.y},
         {cubeEndPoint2.x, cubeEndPoint2.y},
         {cubeEndPoint2.x, cubeStartPoint2.y}},
         //윗면
         {{cubeStartPoint.x, cubeStartPoint.y},
         {cubeStartPoint2.x, cubeStartPoint2.y},
         {cubeEndPoint2.x, cubeStartPoint2.y},
         {cubeEndPoint.x, cubeStartPoint.y}},
         //앞면
         {{cubeStartPoint.x, cubeStartPoint.y},
         {cubeStartPoint.x, cubeEndPoint.y},
         {cubeEndPoint.x, cubeEndPoint.y},
         {cubeEndPoint.x, cubeStartPoint.y}}
    };

    for (int i = 0; i < 6; i++) {
        Polygon(hdc, vertices[i], 4);
    }
}