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
*Last revision:14.05.2024                                                          *
*Comment      :                                                                    *
***********************************************************************************/

#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace std;
#include "figures.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//----------------------------КОНСТАНТЫ-----------------------------------


//----------------------------ПЕРЕМЕННЫЕ-----------------------------------
HDC hdc;
int amount = 4; // количество препятствий
int coordinates = 4; // количество координат для препятствия

// Велосипед
int len_handlebar = 80; // Длина руля 
int LenRudder = 100; // Высота рамы руля
int WheelRad = 40;  // Радиус колес
int FrameLen = 100;  // Длина рамы
int FrameHeight = 50;  // Высота рамы
int x = 600; int y = 400;  // Координаты велосипеда (определяют координаты руля!)
Bicycle* pbike;

//----------------------------МАССИВЫ-----------------------------------


//---------------------------ПРОТОТИПЫ ФУНКЦИЙ-------------------------------
void play(Bicycle* pBike, vector<vector<int>> all_obstacles, Simple_obstacle** all_pObstacles,
	int obstacles_amount, int coord_amount, int startx, int starty);


//----------------------------ОСНОВНАЯ ПРОГРАММА-------------------------------------
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли
	

	

	// Bicycle
	SpeedBike bike1(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10, 25);
	pbike = &bike1;
	
	Box obstacle1(500, 100, 530, 130, 0); // коробка 30х30
	Tree obstacle2(20, 20, 70, 90, 0, 0); // дерево 50х70
	Speed_bump obstacle3(20, 500, 90, 520, 0); // лежачий полицейский 70х20
	Simple_obstacle obstacle4(500, 300, 530, 330, 0); // просто препятствие 30x30
	Simple_obstacle** obstacle_objects = new Simple_obstacle * [amount] { &obstacle1, &obstacle2, &obstacle3, &obstacle4 }; // массив указателей на препятствия
	vector<vector<int>> obstacle_matr(amount, vector<int>(coordinates, 0));
	//int** obstacle_matr = new int*[amount];
	
	for (int i = 0; i < amount; i++)
	{
		//obstacle_matr[i] = new int[coordinates];
		obstacle_matr[i][0] = obstacle_objects[i]->get_x();
		obstacle_matr[i][1] = obstacle_objects[i]->get_y();
		obstacle_matr[i][2] = obstacle_objects[i]->get_x1();
		obstacle_matr[i][3] = obstacle_objects[i]->get_y1();
	}

	play(pbike, obstacle_matr, obstacle_objects, amount, coordinates, x, y);

    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
} // main

void play(Bicycle* pBike, vector<vector<int>> all_obstacles, Simple_obstacle** all_pObstacles, 
	int obstacles_amount, int coord_amount, int startx, int starty)
{
	// ПЕРЕМЕННЫЕ
	bool is_collision = 0; // столкнулись ли
	bool is_damaged = 0; // принадлежит ли велик классу damaged

	// Показать все объекты
	for (int i = 0; i < obstacles_amount; i++)
	{
		all_pObstacles[i]->Show();
	} // for i
	pBike->Show(all_obstacles);

	// Если врезаться уже со сломанным великом, то игра закончится
	while (!is_collision || !is_damaged)
	{
		if (is_collision)
		{ // После аварии велик становится сломанным и возвращается в исходное положение
			pBike->Hide();
			DamagedBike* damagedBike = new DamagedBike(startx, starty, pBike->get_handlebar(), pBike->get_rudder(),
				pBike->get_visibility(), pBike->get_wheelrad(), pBike->get_framelen(),
				pBike->get_frameheight(), pBike->get_framewide());
			//delete pBike; // Удаляем старый объект SpeedBike
			pBike = damagedBike; // Присваиваем указателю новый объект DamagedBike
			pBike->Show(all_obstacles);
			is_damaged = 1;
			is_collision = 0;
		}
		is_collision = pBike->Drag_and_leave(pBike->get_speed(), all_obstacles);
	}

} // play

