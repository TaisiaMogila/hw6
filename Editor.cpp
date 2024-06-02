#include "Editor.h"
#include "vector"

bool startDrawRect = false; 
bool startDrawEllipse = false; 
bool startDrawLine = false; 
bool startDrawPoint = false;

std::vector<long> coordRect = { 0,0,0,0 }; 

void RectEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
	startDrawRect = true; 
	startPoint.x = LOWORD(lParam); 
	startPoint.y = HIWORD(lParam); 
	endPoint = startPoint;  
}

void RectEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    if (startDrawRect)
    {
        startDrawRect = false; 
        OnPaint(hwnd); 
        startPoint.x = coordRect[0]; 
        startPoint.y = coordRect[1]; 
        endPoint.x = coordRect[2]; 
        endPoint.y = coordRect[3]; 
    }
}

void RectEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
	if (startDrawRect)
	{
        RectEditor::OnPaint(hwnd);

        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
  
        RectEditor::OnPaint(hwnd); 

	}
}

void RectEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    coordRect[0] = 2 * startPoint.x - endPoint.x;
    coordRect[1] = 2 * startPoint.y - endPoint.y;
    coordRect[2] = endPoint.x;
    coordRect[3] = endPoint.y;
    Rectangle(hdc, coordRect[0], coordRect[1], coordRect[2], coordRect[3]);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void EllipseEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    startDrawEllipse = true; 
    startPoint.x = LOWORD(lParam); 
    startPoint.y = HIWORD(lParam); 
    endPoint = startPoint; 
}

void EllipseEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);


    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    Ellipse(hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc); 
}

void EllipseEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    if (startDrawEllipse)
    {
        startDrawEllipse = false; 
        EllipseEditor::OnPaint(hwnd); 
    }
}

void EllipseEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (startDrawEllipse)
    {
        EllipseEditor::OnPaint(hwnd);

        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);

        EllipseEditor::OnPaint(hwnd); 

    }
}

void LineEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    if (startDrawLine)
    {
        startDrawLine = false;
        LineEditor::OnPaint(hwnd);
    }
}

void LineEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (startDrawLine)
    {
        LineEditor::OnPaint(hwnd);

        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);

        LineEditor::OnPaint(hwnd); 

    }
}

void LineEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);


    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    MoveToEx(hdc, startPoint.x, startPoint.y, NULL); 
    LineTo(hdc, endPoint.x, endPoint.y); 

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void LineEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    startDrawLine = true;
    startPoint.x = LOWORD(lParam);
    startPoint.y = HIWORD(lParam);
    endPoint = startPoint;
}

void PointEditor::OnLBdown(HWND hwnd, LPARAM lParam) 
{
    startDrawPoint = true;
    startPoint.x = LOWORD(lParam);
    startPoint.y = HIWORD(lParam); 
    endPoint = startPoint;
};

void PointEditor::OnLBup(HWND hwnd, LPARAM lParam) 
{
    if (startDrawPoint)
    {
        startDrawPoint = false;
        PointEditor::OnPaint(hwnd); 
    }
};

void PointEditor::OnMouseMove(HWND hwnd, LPARAM lParam) 
{
    if (startDrawPoint)
    {
        PointEditor::OnPaint(hwnd);

        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);

        PointEditor::OnPaint(hwnd);
    }
};

void PointEditor::OnPaint(HWND hwnd) 
{
    HDC hdc = GetDC(hwnd);


    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    SetPixel(hdc, startPoint.x, startPoint.y, RGB(0, 0, 0)); 

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
};

void ShapeEditor::OnLBdown(HWND, LPARAM) {}; 
void ShapeEditor::OnLBup(HWND, LPARAM) {};
void ShapeEditor::OnMouseMove(HWND, LPARAM) {};
void ShapeEditor::OnPaint(HWND) {};
