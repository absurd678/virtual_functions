#include <iostream>
#include <Windows.h>
#include "figures.h"
using namespace std;

extern HDC hdc;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// class Point

// ...
void Point::Move_to(int newX, int newY)
{
	x = newX;
	y = newY;
	Hide();
	Show();
} // Point::Move_to

void Point::Hide()
{
	is_visible = 0;
	SetPixel(hdc, x, y, RGB(0, 0, 255));
} // Point::Hide()

void Point::Show()
{
	is_visible = 1;
	SetPixel(hdc, x, y, RGB(255, 0, 0));
} // Point::Show()

void Point::Drag(int delta)
{
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) break;
		else if (KEY_DOWN(VK_UP))
		{
			y -= delta;
			Hide();
			Show();
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			y += delta;
			Hide();
			Show();
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			x -= delta;
			Hide();
			Show();
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
		{
			x += delta;
			Hide();
			Show();
		} // else if
	} // while 1
} // Point::Drag

