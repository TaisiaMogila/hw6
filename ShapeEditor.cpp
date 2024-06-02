#include "ShapeEditor.h"

#include <vector>

bool checkedChooseRectangle = false;
bool checkedChooseEllipse = false; 
bool checkedChooseLine = false; 
bool checkedChoosePoint = false; 

std::uint32_t countObjects = 0; 

Shape* pchape[129];

ShapeObjectsEditor::ShapeObjectsEditor() 
{
    shape_ = nullptr; 
    shapeeditor_ = nullptr; 
}; 
ShapeObjectsEditor::~ShapeObjectsEditor() 
{
    delete shape_;
    delete shapeeditor_;
};

void ShapeObjectsEditor::StartLineEditor(HWND hwnd, UINT checkItem)
{
    checkedChooseEllipse = false; 
    checkedChooseRectangle = false; 
    checkedChoosePoint = false; 

    CheckMenuItem(GetMenu(hwnd), 1, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 2, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 4, MF_UNCHECKED);

    if (CheckMenuItem(GetMenu(hwnd), checkItem, NULL) == MF_CHECKED)
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_CHECKED);
    }
    checkedChooseLine = true;
    delete shape_;
    shape_ = new LineShape;
    delete shapeeditor_;
    shapeeditor_ = new LineEditor();
}

void ShapeObjectsEditor::StartPointEditor(HWND hwnd, UINT checkItem)
{
    checkedChooseEllipse = false;
    checkedChooseRectangle = false;
    checkedChooseLine = false;

    CheckMenuItem(GetMenu(hwnd), 1, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 2, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 3, MF_UNCHECKED);

    if (CheckMenuItem(GetMenu(hwnd), checkItem, NULL) == MF_CHECKED)
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_CHECKED);
    }
    checkedChoosePoint = true; 
    delete shape_;
    shape_ = new PointShape;
    delete shapeeditor_;
    shapeeditor_ = new PointEditor();
}

void ShapeObjectsEditor::StartRectEditor(HWND hwnd, UINT checkItem)
{
    checkedChooseEllipse = false;
    checkedChoosePoint = false;
    checkedChooseLine = false;

    CheckMenuItem(GetMenu(hwnd), 4, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 2, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 3, MF_UNCHECKED);

    if (CheckMenuItem(GetMenu(hwnd), checkItem, NULL) == MF_CHECKED)
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_CHECKED);
    }
    checkedChooseRectangle = true;
    delete shape_; 
    shape_ = new RectangleShape; 
    delete shapeeditor_; 
    shapeeditor_ = new RectEditor();  
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hwnd, UINT checkItem)
{
    checkedChooseRectangle = false;
    checkedChoosePoint = false;
    checkedChooseLine = false;

    CheckMenuItem(GetMenu(hwnd), 4, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 1, MF_UNCHECKED);
    CheckMenuItem(GetMenu(hwnd), 3, MF_UNCHECKED);

    if (CheckMenuItem(GetMenu(hwnd), checkItem, NULL) == MF_CHECKED)
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(GetMenu(hwnd), checkItem, MF_CHECKED);
    }
    checkedChooseEllipse = true;
    delete shape_;
    shape_ = new EllipseShape;
    delete shapeeditor_;
    shapeeditor_ = new EllipseEditor();
}

void ShapeObjectsEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd); 
    for (std::uint32_t i = 0; i < countObjects; i++)
    {
        if (pchape[i] != nullptr)
        {
            pchape[i]->Show(hdc); 
            pchape[i] = nullptr;
        }
    }
    ReleaseDC(hwnd, hdc);  
}

void ShapeObjectsEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (checkedChooseRectangle)
    {
        shapeeditor_->OnMouseMove(hwnd, lParam);
    }
    else if (checkedChooseEllipse)
    {
        shapeeditor_->OnMouseMove(hwnd, lParam); 
    } 
    else if (checkedChooseLine)
    {
        shapeeditor_->OnMouseMove(hwnd, lParam);
    }
    else if (checkedChoosePoint)
    {
        shapeeditor_->OnMouseMove(hwnd, lParam);
    }
}

void ShapeObjectsEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    if (checkedChooseRectangle)
    {
        shapeeditor_->OnLBup(hwnd, lParam);
        
        shape_->Set(dynamic_cast<RectEditor*>(shapeeditor_)->startPoint.x, dynamic_cast<RectEditor*>(shapeeditor_)->startPoint.y, dynamic_cast<RectEditor*>(shapeeditor_)->endPoint.x, dynamic_cast<RectEditor*>(shapeeditor_)->endPoint.y);
        pchape[countObjects++] = shape_;
        InvalidateRect(hwnd, NULL, TRUE);  
    }
    else if (checkedChooseEllipse)
    {
        shapeeditor_->OnLBup(hwnd, lParam); 
        shape_->Set(dynamic_cast<EllipseEditor*>(shapeeditor_)->startPoint.x, dynamic_cast<EllipseEditor*>(shapeeditor_)->startPoint.y, dynamic_cast<EllipseEditor*>(shapeeditor_)->endPoint.x, dynamic_cast<EllipseEditor*>(shapeeditor_)->endPoint.y);
        pchape[countObjects++] = shape_;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    else if (checkedChooseLine)
    {
        shapeeditor_->OnLBup(hwnd, lParam); 
        shape_->Set(dynamic_cast<LineEditor*>(shapeeditor_)->startPoint.x, dynamic_cast<LineEditor*>(shapeeditor_)->startPoint.y, dynamic_cast<LineEditor*>(shapeeditor_)->endPoint.x, dynamic_cast<LineEditor*>(shapeeditor_)->endPoint.y);
        pchape[countObjects++] = shape_;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    else if (checkedChoosePoint)
    {
        shapeeditor_->OnLBup(hwnd, lParam);
    }
}

void ShapeObjectsEditor::OnLBDown(HWND hwnd, LPARAM lParam)
{
    if (checkedChooseRectangle)
    {
        shapeeditor_->OnLBdown(hwnd, lParam);
    }
    else if (checkedChooseEllipse)
    {
        shapeeditor_->OnLBdown(hwnd, lParam); 
    }
    else if (checkedChooseLine)
    {
        shapeeditor_->OnLBdown(hwnd, lParam);
    }
    else if (checkedChoosePoint)
    {
        shapeeditor_->OnLBdown(hwnd, lParam);
    }
}