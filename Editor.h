#include "Windows.h"
#include "vector" 

class Editor
{
public: 
	virtual void OnLBdown(HWND, LPARAM) = 0;
	virtual void OnLBup(HWND, LPARAM) = 0;
	virtual void OnMouseMove(HWND, LPARAM) = 0;
	virtual void OnPaint(HWND) = 0;
};

class ShapeEditor : public Editor
{
public:
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};

class RectEditor : public ShapeEditor
{
public:
	POINT startPoint;
	POINT endPoint;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override; 
};

class EllipseEditor : public ShapeEditor
{
public:
	POINT startPoint;
	POINT endPoint;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};


class LineEditor : public ShapeEditor
{
public:
	POINT startPoint;
	POINT endPoint;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;  
	void OnPaint(HWND) override; 
};

class PointEditor : public ShapeEditor
{
public:
	POINT startPoint;
	POINT endPoint;
	void OnLBdown(HWND, LPARAM) override;
	void OnLBup(HWND, LPARAM) override;
	void OnMouseMove(HWND, LPARAM) override;
	void OnPaint(HWND) override;
};
