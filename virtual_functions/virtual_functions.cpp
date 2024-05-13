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

//----------------------------КОНСТАНТЫ-----------------------------------
const int AMOUNT = 2;
const int COORDINATES = 4;

//----------------------------ПЕРЕМЕННЫЕ-----------------------------------
HDC hdc;

//----------------------------МАССИВЫ-----------------------------------


//----------------------------ОСНОВНАЯ ПРОГРАММА-------------------------------------
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли
	

	// Велосипед
	
	int len_handlebar = 80; // Длина руля 
	int LenRudder = 100; // Высота рамы руля
	int WheelRad = 40;  // Радиус колес
	int FrameLen = 100;  // Длина рамы
	int FrameHeight = 50;  // Высота рамы
	int x = 600; int y = 400;  // Координаты велосипеда (определяют координаты руля!)

	// Bicycle
	SpeedBike bike = SpeedBike(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10, 25);

	//------------------------------------ЛАБА 3----------------------------------
	
	Box obstacle1(0, 0, 100, 100, 0);
	/*Tree obstacle2(200, 200, 300, 600, 0, 0);
	Speed_bump obstacle3(250, 250, 300, 300, 0);*/
	Simple_obstacle obstacle4(300, 300, 500, 500, 0);
	Simple_obstacle* obctacle_objects[AMOUNT] = { &obstacle1, &obstacle4 };
	int** obstacle_matr = new int*[AMOUNT];
	
	for (int i = 0; i < AMOUNT; i++)
	{
		obctacle_objects[i]->Show();
		obstacle_matr[i] = new int[COORDINATES];
		obstacle_matr[i][0] = obctacle_objects[i]->get_x();
		obstacle_matr[i][1] = obctacle_objects[i]->get_y();
		obstacle_matr[i][2] = obctacle_objects[i]->get_x1();
		obstacle_matr[i][3] = obctacle_objects[i]->get_y1();
	}
	bike.Show(obstacle_matr);
	cin.get();
	
	bike.Drag(25, obstacle_matr); // esc
	cin.get();

    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
} // main

