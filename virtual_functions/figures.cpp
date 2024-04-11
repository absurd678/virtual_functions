#include <iostream>
#include "figures.h"
#include <Windows.h>
using namespace std;

extern HDC hdc;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// ----------------------------------------КЛАССЫ----------------------------------------------
// --------------------------------------------------------------------------------------------

//------------------------------------------Point----------------------------------------------

void Point::set_colorData(int* new_colorData)
{
	for (int i = 0; i < COLLEN; i++)
		colorData[i] = new_colorData[i];
} // set_colorData

void Point::Move_to(int newX, int newY)
{
	Hide();
	x = newX;
	y = newY;
	Show();
} // Point::Move_to

void Point::Hide()
{
	is_visible = 0;
	SetPixel(hdc, x, y, RGB(255, 255, 255)); // Белый
} // Point::Hide()

void Point::Show()
{
	is_visible = 1;
	SetPixel(hdc, x, y, RGB(colorData[0], colorData[1], colorData[2]));
} // Point::Show()

void Point::Drag(int delta)
{
	int dragX, dragY;
	dragX = x;
	dragY = y;
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) break;
		else if (KEY_DOWN(VK_UP))
		{
			dragY -= delta;
			Move_to(dragX, dragY);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			dragY += delta;
			Move_to(dragX, dragY);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			dragX -= delta;
			Move_to(dragX, dragY);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
{
			dragX += delta;
			Move_to(dragX, dragY);
			Sleep(500);
		} // else if
	} // while 1
} // Point::Drag

// --------------------------------------Circle----------------------------------------

void Circle::Show() {
	is_visible = 1;
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(colorData[0], colorData[1], colorData[2]));
	SelectObject(hdc, PenRed);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(PenRed);
} // Show

void Circle::Hide()
{
	is_visible = 0;
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, PenRed);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(PenRed);
} // Hide

int Circle::Expand(int delta)
{
	if (delta < 0 && abs(delta) > radius) return 1;
	radius += delta;
	if (radius < 2) radius = 2;
	Show();
	return 0;
} // Expand

int Circle::Reduce(int delta)
{
	return Expand(-delta);
} // Reduce


//------------------------------------------- Ring---------------------------------------------------
void Ring::Show()
{
	is_visible = 1;
	HPEN PenRed = CreatePen(PS_SOLID, wide, RGB(colorData[0], colorData[1], colorData[2]));
	SelectObject(hdc, PenRed);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(PenRed);
} // Show

void Ring::Hide()
{
	is_visible = 0;
	HPEN PenRed = CreatePen(PS_SOLID, wide, RGB(255, 255, 255));
	SelectObject(hdc, PenRed);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(PenRed);
} // Hide

int Ring::Wide(int DeltaWide)
{
	if (DeltaWide < 0 && abs(DeltaWide) > radius) return 1;
	wide += DeltaWide;
	if (wide < 2) wide = 2;
	Show();
	return 0;
} // Wide

int Ring::Slim(int DeltaWide)
{
	return Wide(-DeltaWide);
} // Slim


// -------------------------------------------Line---------------------------------------------------
void Line::Show()
{
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(colorData[0], colorData[1], colorData[2])); // Стандартный стиль, толщина 1 пиксель, красный цвет
	SelectObject(hdc, hPen);

	MoveToEx(hdc, x, y, NULL); // Начальная точка 
	LineTo(hdc, x1, y1); // Конечная точка 

	DeleteObject(hPen);
	
} // Show()

void Line::Hide()
{
	is_visible = 0;
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // Стандартный стиль, толщина 1 пиксель, синий цвет
	SelectObject(hdc, hPen);

	MoveToEx(hdc, x, y, NULL); // Начальная точка 
	LineTo(hdc, x1, y1); // Конечная точка 

	DeleteObject(hPen);
} // Hide

void Line::Move_to(int newX, int newY, int newX1, int newY1)
{
	Hide();
	x = newX; x1 = newX1;
	y = newY; y1 = newY1;
	Show();
} // Line::Move_to

void Line::Drag(int delta)
{
	int dragX, dragY, dragX1, dragY1;
	dragX = x; dragX1 = x1;
	dragY = y; dragY1 = y1;
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) break;
		else if (KEY_DOWN(VK_UP))
		{
			dragY -= delta;
			dragY1 -= delta;
			Move_to(dragX, dragY, dragX1, dragY1);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			dragY += delta;
			dragY1 += delta;
			Move_to(dragX, dragY, dragX1, dragY1);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			dragX -= delta;
			dragX1 -= delta;
			Move_to(dragX, dragY, dragX1, dragY1);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
		{
			dragX += delta;
			dragX1 += delta;
			Move_to(dragX, dragY, dragX1, dragY1);
			Sleep(500);
		} // else if
	} // while 1
} // Line::Drag


// -------------------------------------------------------Rectangle-------------------------------------------------
void RectAngle::Show()
{
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, wide, RGB(colorData[0], colorData[1], colorData[2])); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);
} // Show()
void RectAngle::Hide()
{
	is_visible = 0;
	HPEN hPen = CreatePen(PS_SOLID, wide, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, синий цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);
} // Hide