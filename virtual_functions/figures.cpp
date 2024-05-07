#include <iostream>
#include "figures.h"
#include <Windows.h>
using namespace std;

extern HDC hdc;
const int AMOUNT = 4;
const int COORDINATES = 4;
const float COEFF = 0.3;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// ----------------------------------------КЛАССЫ----------------------------------------------
// --------------------------------------------------------------------------------------------

//------------------------------------------Point----------------------------------------------


void Point::Move_to(int newX, int newY, int coord_of_obstacles[][COORDINATES])
{
	Hide();
	x = newX;
	y = newY;
	bool is_collision = Show(coord_of_obstacles);
	if (is_collision) cout << "the collision was caught" << endl;
} // Point::Move_to

void Point::Hide()
{
	is_visible = 0;
	SetPixel(hdc, x, y, RGB(255, 255, 255)); // Белый
} // Point::Hide()

bool Point::Show(int coord_of_obstacles[][COORDINATES])
{
	is_visible = 1;
	SetPixel(hdc, x, y, RGB(255, 0, 0));
	return 0;
} // Point::Show()

void Point::Drag(int delta, int coord_of_obstacles[][COORDINATES])
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
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			dragY += delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			dragX -= delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
{
			dragX += delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(500);
		} // else if
	} // while 1
} // Point::Drag


//--------------------------RectAngle------------------------------------------
bool RectAngle::Show()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);

	return 0;
}

void RectAngle::Hide()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, white цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);
}


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

bool Bicycle::Show(int coord_of_obstacles[][COORDINATES])
{
	int init_x, init_y, init_x1, init_y1;
	bool is_collision = 0;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);
	
	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль
	is_collision = check_collision(coord_of_obstacles, x, y, x + len_handlebar, y + FrameWide);

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Левое колесо
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Правое колесо

	DeleteObject(hPen);

	return is_collision;
}

void Bicycle::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, белый цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2*COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide+WheelRad, init_y + COEFF * FrameHeight); // Седло

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Левое колесо
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Правое колесо

	DeleteObject(hPen);
}


//-----------------------------------Speed Bike---------------------------------------------

SpeedBike::SpeedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_speed) : Bicycle(init_x, init_y, 
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide)
{
	speed = init_speed;
}

bool SpeedBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Левое колесо
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Правое колесо

	DeleteObject(hPen);
	return 0;
}


//---------------------------------Mount Bike---------------------------------------

MountBike::MountBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_wheel_wide) : Bicycle(init_x, init_y,
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide)
{
	wheel_wide = init_wheel_wide;
}

bool MountBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); 
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

	hPen = CreatePen(PS_SOLID, wheel_wide, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Левое колесо
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Правое колесо

	DeleteObject(hPen);
	return 0;
}

void MountBike::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

	hPen = CreatePen(PS_SOLID, wheel_wide, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Левое колесо
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Ellipse(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad); // Правое колесо

	DeleteObject(hPen);
}


//----------------------------------------Damaged Bike-----------------------------------------------------

DamagedBike::DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide) : Bicycle(init_x, init_y,
		in_len_handlebar, inLenRudder, init_visible, inWheelRad, inFrameLen, inFrameHeight, inFrameWide) {}

bool DamagedBike::Show()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); 
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

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
	return 0;
}

void DamagedBike::Hide()
{
	int init_x, init_y, init_x1, init_y1;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide, y + LenRudder); // Рама руля

	init_x += FrameWide;
	init_y = y + FrameWide + COEFF * LenRudder;
	Rectangle(hdc, init_x, init_y, init_x + FrameLen, init_y + 2 * COEFF * LenRudder); // Рама

	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	Rectangle(hdc, init_x, init_y, init_x + FrameWide + WheelRad, init_y + COEFF * FrameHeight); // Седло

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


//----------------------------------ФУНКЦИИ--------------------------------------

bool check_collision(int coord_of_obstacles[][COORDINATES], int x, int y, int x1, int y1)
{
	for (int i = 0; i < AMOUNT; i++)
	{
		if (x == coord_of_obstacles[i][2]) return 1;
		else if (x1 == coord_of_obstacles[i][0]) return 1;
		else if (y == coord_of_obstacles[i][3]) return 1;
		else if (y1 == coord_of_obstacles[i][1]) return 1;
	}
	return 0;
}