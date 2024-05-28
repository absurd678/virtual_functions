#include <iostream>
#include "figures.h"
#include <Windows.h>
using namespace std;

extern HDC hdc;
const float COEFF = 0.3;
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)



// ----------------------------------------КЛАССЫ----------------------------------------------
// --------------------------------------------------------------------------------------------



//------------------------------------------ПРЕПЯТСТВИЯ--------------------------------------
//--------------------------ABC_obstacle------------------------------------------

bool ABC_obstacle::Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles)
{
	Hide();
	x = newX;
	y = newY;
	Show();
	return 0;
}

bool ABC_obstacle::Drag(int delta, vector<vector<int>> coord_of_obstacles)
{
	int dragX, dragY;
	dragX = x;
	dragY = y;

	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) return 0;
		else if (KEY_DOWN(VK_UP))
		{
			dragY -= delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(250);
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			dragY += delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(250);
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			dragX -= delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(250);
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
		{
			dragX += delta;
			Move_to(dragX, dragY, coord_of_obstacles);
			Sleep(250);
		} // else if
	} // while 
}

//----------------------------------Box----------------------------------------------
Box::Box(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_R, int init_G, int init_B)
{
	x = init_x;
	y = init_y;
	x1 = init_x1;
	y1 = init_y1;
	is_visible = init_visible;
	R = init_R; 
	G = init_G;
	B = init_B;
}
void Box::Show()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);
}
void Box::Hide()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, white цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x1, y1);

	DeleteObject(hPen);
}


//--------------------------------------Tree--------------------------------------------
Tree::Tree(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_season)
{
	x = init_x;
	y = init_y;
	x1 = init_x1;
	y1 = init_y1;
	is_visible = init_visible;
	season = init_season;
}

void Tree::Show()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	Rectangle(hdc, x+0.3*(x1-x), y, x1 - 0.3 * (x1 - x), y1);
	DeleteObject(hPen);

	switch (season) {
		case 0:
			hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		case 1:
			hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		default:
			hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	}
	SelectObject(hdc, hPen);
	
	Rectangle(hdc, x, y, x1, y1+0.3*(y-y1));

	DeleteObject(hPen);
}

void Tree::Hide()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);
	Rectangle(hdc, x + 0.3 * (x1 - x), y, x1 - 0.3 * (x1 - x), y1);
	Rectangle(hdc, x, y, x1, y1 + 0.3 * (y - y1));

	DeleteObject(hPen);
}

//---------------------------------------Speed Bump--------------------------------------
Speed_bump::Speed_bump(int init_x, int init_y, int init_x1, int init_y1, bool init_visible)
{
	x = init_x;
	y = init_y;
	x1 = init_x1;
	y1 = init_y1;
	is_visible = init_visible;
}
void Speed_bump::Show()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	Ellipse(hdc, x, y, x1, y1-(y-y1));
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);
	Rectangle(hdc, x, y - (y - y1), x1, y1 - (y - y1));
	DeleteObject(hPen);
}
void Speed_bump::Hide()
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, hPen);
	Ellipse(hdc, x, y, x1, y1);
	DeleteObject(hPen);
}

//---------------------------------------ABC_Bicycle---------------------------------------

//------------------Интерфейсные методы-----------------------------------------------
bool ABC_Bicycle::Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles)
{
	Hide();
	x = newX;
	y = newY;
	bool is_collision = Show(coord_of_obstacles);
	return is_collision;
} // Point::Move_to

bool ABC_Bicycle::Drag(int delta, vector<vector<int>> coord_of_obstacles) // ВЕРСИЯ БЕЗ WHILE
{
	int dragX, dragY;
	dragX = x;
	dragY = y;
	bool is_collision = 0;


	if (KEY_DOWN(VK_ESCAPE)) return 0;
	else if (KEY_DOWN(VK_UP))
	{
		dragY -= delta;
		is_collision = Move_to(dragX, dragY, coord_of_obstacles);
		Sleep(250);
	} // else if
	else if (KEY_DOWN(VK_DOWN))
	{
		dragY += delta;
		is_collision = Move_to(dragX, dragY, coord_of_obstacles);
		Sleep(250);
	} // else if
	else if (KEY_DOWN(VK_LEFT))
	{
		dragX -= delta;
		is_collision = Move_to(dragX, dragY, coord_of_obstacles);
		Sleep(250);
	} // else if
	else if (KEY_DOWN(VK_RIGHT))
	{
		dragX += delta;
		is_collision = Move_to(dragX, dragY, coord_of_obstacles);
		Sleep(250);
	} // else if

	if (is_collision) return 1;
	return 0;
}


//-----------------------------------Speed Bike---------------------------------------------

SpeedBike::SpeedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_speed)
{
	x = init_x;
	y = init_y;
	len_handlebar = in_len_handlebar;
	LenRudder = inLenRudder;
	is_visible = init_visible;
	WheelRad = inWheelRad;
	FrameLen = inFrameLen;
	FrameHeight = inFrameHeight;
	FrameWide = inFrameWide;
	speed = init_speed;
}

bool SpeedBike::Show(vector<vector<int>> coord_of_obstacles)
{
	int init_x, init_y, init_x1, init_y1;
	int is_collision;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	Rectangle(hdc, init_x, y, init_x + FrameWide, y + FrameWide*1.5); // Фонарь на руле
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
	is_collision = check_collision(coord_of_obstacles, x, y, init_x + WheelRad, init_y + WheelRad);
	return is_collision;
} // Show

void SpeedBike:: Hide()
{
	int init_x, init_y, init_x1, init_y1;
	int is_collision;
	is_visible = 1;
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Стандартный стиль, толщина wide пиксель, красный цвет
	SelectObject(hdc, hPen);

	Rectangle(hdc, x, y, x + len_handlebar, y + FrameWide); // Руль

	init_x = x + len_handlebar / 2 - FrameWide / 2;
	Rectangle(hdc, init_x, y, init_x + FrameWide, y + FrameWide * 1.5); // Фонарь на руле
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
}


//---------------------------------Mount Bike---------------------------------------

MountBike::MountBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_wheel_wide)
{
	x = init_x;
	y = init_y;
	len_handlebar = in_len_handlebar;
	LenRudder = inLenRudder;
	is_visible = init_visible;
	WheelRad = inWheelRad;
	FrameLen = inFrameLen;
	FrameHeight = inFrameHeight;
	FrameWide = inFrameWide;
	wheel_wide = init_wheel_wide;
}

bool MountBike::Show(vector<vector<int>> coord_of_obstacles)
{
	int init_x, init_y, init_x1, init_y1;
	int is_collision;
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
	is_collision = check_collision(coord_of_obstacles, x, y, init_x + WheelRad, init_y + WheelRad);
	return is_collision;
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

	hPen = CreatePen(PS_SOLID, wheel_wide, RGB(255, 255, 255));
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
	int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide) 
{
	x = init_x;
	y = init_y;
	len_handlebar = in_len_handlebar;
	LenRudder = inLenRudder;
	is_visible = init_visible;
	WheelRad = inWheelRad;
	FrameLen = inFrameLen;
	FrameHeight = inFrameHeight;
	FrameWide = inFrameWide;
}

bool DamagedBike::Show(vector<vector<int>> coord_of_obstacles)
{
	int init_x, init_y, init_x1, init_y1;
	int is_collision;
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
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);
	// колесо 2
	init_x += FrameLen + FrameWide / 2;
	Rectangle(hdc, init_x - WheelRad, init_y - WheelRad, init_x + WheelRad, init_y + WheelRad);

	DeleteObject(hPen);
	is_collision = check_collision(coord_of_obstacles, x, y, init_x + WheelRad, init_y + WheelRad);
	return is_collision;
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


bool check_collision(vector<vector<int>> coord_of_obstacles, int x, int y, int x1, int y1)
{
	for (int i = 0; i < coord_of_obstacles.size(); i++)
	{
		if ((x < coord_of_obstacles[i][2] && x > coord_of_obstacles[i][0]) || (x1 > coord_of_obstacles[i][0] && x1 < coord_of_obstacles[i][2])) // столкновение справа или слева
		{
			if (y > coord_of_obstacles[i][1] && y < coord_of_obstacles[i][3]) 
				return 1; // рулем
			if (y1 > coord_of_obstacles[i][1] && y1 < coord_of_obstacles[i][3]) 
				return 1;  // колесом
			if (coord_of_obstacles[i][1] > y && coord_of_obstacles[i][3] < y1) 
				return 1;  // препятствие "вошло" в велик
		} // if
		if ((y < coord_of_obstacles[i][3] && y > coord_of_obstacles[i][1]) || (y1 > coord_of_obstacles[i][1] && y1 < coord_of_obstacles[i][3])) // столкновение снизу или сверху
		{
			if (x < coord_of_obstacles[i][2] && x > coord_of_obstacles[i][0]) 
				return 1; // левым углом
			if (x1 < coord_of_obstacles[i][2] && x1 > coord_of_obstacles[i][0])
				return 1;  // правым 
			if (coord_of_obstacles[i][0] > x && coord_of_obstacles[i][2] < x1)
				return 1; // препятствие "вошло" в велик
		} // if
	} // for i
	return 0;
} // check_collision