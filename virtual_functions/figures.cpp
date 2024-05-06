#include <iostream>
#include "figures.h"
#include <Windows.h>
using namespace std;

extern HDC hdc;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// ----------------------------------------КЛАССЫ----------------------------------------------
// --------------------------------------------------------------------------------------------

//------------------------------------------Point----------------------------------------------


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
	SetPixel(hdc, x, y, RGB(255, 0, 0));
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


//---------------------------------------Bicycle---------------------------------------
Bicycle::Bicycle(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide):Point(init_x, init_y, init_visible)
{
	x = init_x;
	y = init_y;
	len_handlebar = in_len_handlebar;
	LenRudder = inLenRudder;
	WheelRad = inWheelRad;
	FrameLen = inFrameLen;
	FrameHeight = inFrameHeight;
	FrameWide = inFrameWide;
}//Bicycle

void Bicycle::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);
	
	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x-WheelRad, init_y- WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);

}

void Bicycle::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, белый цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);
}


//-----------------------------------Speed Bike---------------------------------------------

SpeedBike::SpeedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_speed) : Bicycle(init_x, init_y, 
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide)
{
	speed = init_speed;
}

void SpeedBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);

}


//---------------------------------Mount Bike---------------------------------------

MountBike::MountBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_wheel_wide) : Bicycle(init_x, init_y,
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide)
{
	wheel_wide = init_wheel_wide;
}

void MountBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); 
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, wheel_wide, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);
}

void MountBike::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, wheel_wide, RGB(255, 255, 255));
	SelectObject(hdc, hPen);
	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);
}


//----------------------------------------Damaged Bike-----------------------------------------------------

DamagedBike::DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide) : Bicycle(init_x, init_y,
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide) {}

void DamagedBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); 
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	//Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	//Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);

}

void DamagedBike::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder);

	init_x += FrameWide;
	init_y = y + FrameWide + 0.3 * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 0.6 * LenRudder);

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight);

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	//Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	//Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);
}
