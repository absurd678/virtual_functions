// virtual_functions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/***********************************************************************************
*                         Программирование                                         *
************************************************************************************
*Project type :Win64 Console Application                                           *
*Project name_bus :virtual_functions.sln                                           *
*File name_bus    :virtual_functions.cpp                                           *
*Language     :CPP, MSVS 2022                                                      *
*Programmers  :Кожевников Артем Вадимович,  М3О-209Б-22                            *
*Modified By  :                                                                    *
*Created      :10.04.2024                                                          *
*Last revision:17.04.2024                                                          *
*Comment      :                                                                    *
***********************************************************************************/

#include <iostream>
#include <Windows.h>
using namespace std;
#include "figures.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//----------------------------ПЕРЕМЕННЫЕ-----------------------------------
HDC hdc;

//----------------------------ОСНОВНАЯ ПРОГРАММА-------------------------------------
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли

	// Статические VS Виртуальные методы
	Point rect1 = Point(50, 50, 0);
	rect1.Show();
	cin.get();
	rect1.Hide();
	cin.get();
	rect1.Move_to(100, 100);  // Сравнить два связывания 
	cin.get();
	rect1.Drag(50);
	cin.get();
	

	// Велосипед
	
	int len_handlebar = 80; // Длина руля 
	int LenRudder = 100; // Высота рамы руля
	int WheelRad = 40;  // Радиус колес
	int FrameLen = 100;  // Длина рамы
	int FrameHeight = 50;  // Высота рамы
	int x = 50; int y = 50;  // Координаты велосипеда (определяют координаты руля!)

	// Bicycle
	//Bicycle bike = Bicycle(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10);
	//bike.Show();
	//cin.get();
	//bike.Hide();
	//cin.get();
	//bike.Move_to(x+50, y+50);
	//cin.get();
	//bike.Drag(50); // esc
	//cin.get();
	
	//Speed
	SpeedBike sp_bike = SpeedBike(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10, 80);
	sp_bike.Show();
	cin.get();
	sp_bike.Hide();
	cin.get();
	sp_bike.Move_to(x + 50, y + 50);
	cin.get();
	sp_bike.Drag(sp_bike.get_speed()); // esc
	cin.get();
	sp_bike.Hide();

	//Mount
	MountBike mon_bike = MountBike(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10, 5);
	mon_bike.Show();
	cin.get();
	mon_bike.Hide();
	cin.get();
	mon_bike.Move_to(x + 50, y + 50);
	cin.get();
	mon_bike.Drag(10); // esc
	cin.get();
	mon_bike.Hide();


	//Damaged
	DamagedBike dam_bike = DamagedBike(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10);
	dam_bike.Show();
	cin.get();
	dam_bike.Hide();
	cin.get();
	dam_bike.Move_to(x + 50, y + 50);
	cin.get();
	dam_bike.Drag(10); // esc
	cin.get();
	dam_bike.Hide();

    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
} // main

