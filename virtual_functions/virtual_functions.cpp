// virtual_functions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
using namespace std;
#include "figures.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
// КОНСТАНТЫ
const int FrameWide = 10;
int red[3] = { 255, 0, 0 };
int black[3] = { 0, 0, 0 };

struct Bike
{
    RectAngle* handlebar;  // руль
    RectAngle* rudder_frame;  // рама руля
    RectAngle* frame;  // рама
    RectAngle* seat;  // сиденье
    Ring* wheel1;  // колесо 1
    Ring* wheel2;  // колесо 2
};

void CreateBike(int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike);
void ShowBike(Bike bike);
void HideBike(Bike bike);
void MoveBikeTo(int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike);
void DragBike(int delta, int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike); 
// вызывать по очереди drag у каждого объекта - неправильное решение.
// Если создавать класс велика, то нужно сделать множественное наследование. Но тогда возникает неоднозначность полей x, y в конструкторе


HDC hdc;
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли
	Bike bike;
	int len_handlebar = 80; 
	int LenRudder = 100; 
	int WheelRad = 20;
	int FrameLen = 100;
	int FrameHeight = 50; 
	int x = 50; int y = 50;
	CreateBike(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, x, y, bike);
	ShowBike(bike);
	cin.get();
	HideBike(bike);
	cin.get();
	DragBike(10, len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, x, y, bike); // esc
    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
}

void CreateBike(int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike)
{
    int init_x, init_y, init_x1, init_y1;
    // руль
    new_bike.handlebar = new RectAngle(x, y, 0, x + len_handlebar, y + FrameWide, FrameWide, black);
    // рама руля
    init_x = x + len_handlebar / 2 - FrameWide / 2;
    init_y = y + FrameWide;
    new_bike.rudder_frame = new RectAngle(init_x, init_y, 0, init_x + FrameWide, y + LenRudder, FrameWide, red);
	// рама
    init_x += FrameWide;
	init_y = y + FrameWide + 0.3*LenRudder;
	new_bike.frame = new RectAngle(init_x, init_y, 0, init_x + FrameLen, init_y + 0.6*LenRudder, FrameWide, red);
	// сиденье
	init_x = init_x + FrameLen - FrameWide;
	init_y -= FrameWide;
	new_bike.seat = new RectAngle(init_x, init_y, 0, init_x + 0.3 * FrameLen, init_y + 0.3 * FrameHeight, FrameWide, black);
	// колесо 1
	init_x = x + len_handlebar / 2 - FrameWide / 2;
	init_y = y + FrameWide + LenRudder;
	new_bike.wheel1 = new Ring(init_x, init_y, 0, WheelRad, FrameWide, black);
	// колесо 2
	init_x += FrameLen + FrameWide/2;
	new_bike.wheel2 = new Ring(init_x, init_y, 0, WheelRad, FrameWide, black);
} // CreateBike

void ShowBike(Bike bike)
{
	bike.handlebar->Show();
	bike.rudder_frame->Show();
	bike.frame->Show();
	bike.seat->Show();
	bike.wheel1->Show();
	bike.wheel2->Show();
} // ShowBike

void HideBike(Bike bike)
{
	bike.handlebar->Hide();
	bike.rudder_frame->Hide();
	bike.frame->Hide();
	bike.seat->Hide();
	bike.wheel1->Hide();
	bike.wheel2->Hide();
} // HideBike

void MoveBikeTo(int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike)
{
	HideBike(new_bike);
	CreateBike(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, x, y, new_bike);
	ShowBike(new_bike);
} // MoveBikeTo

void DragBike(int delta, int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike)
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
			MoveBikeTo(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, dragX, dragY, new_bike);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_DOWN))
		{
			dragY += delta;
			MoveBikeTo(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, dragX, dragY, new_bike);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_LEFT))
		{
			dragX -= delta;
			MoveBikeTo(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, dragX, dragY, new_bike);
			Sleep(500);
		} // else if
		else if (KEY_DOWN(VK_RIGHT))
		{
			dragX += delta;
			MoveBikeTo(len_handlebar, LenRudder, WheelRad, FrameLen, FrameHeight, dragX, dragY, new_bike);
			Sleep(500);
		} // else if
	} // while 1
} // DragBike


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
