﻿// virtual_functions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
#include <stdio.h>
using namespace std;
#include "figures.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//----------------------------КОНСТАНТЫ-----------------------------------


//----------------------------ПЕРЕМЕННЫЕ-----------------------------------
HDC hdc;
int amount = 4;
int coordinates = 4;

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
void play(Bicycle* pBike, int** all_obstacles, Simple_obstacle** all_pObstacles, int length, int obst_amount, int startx, int starty);


//----------------------------ОСНОВНАЯ ПРОГРАММА-------------------------------------
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли
	

	

	// Bicycle
	SpeedBike bike1(x, y, len_handlebar, LenRudder, 0, WheelRad, FrameLen, FrameHeight, 10, 25);
	pbike = &bike1;
	
	Box obstacle1(0, 0, 100, 100, 0);
	Tree obstacle2(300, 300, 500, 500, 0, 0);
	Speed_bump obstacle3(300, 300, 500, 500, 0);
	Simple_obstacle obstacle4(300, 300, 500, 500, 0);
	Simple_obstacle** obstacle_objects = new Simple_obstacle * [amount] { &obstacle1, &obstacle2, &obstacle3, &obstacle4 };
	int** obstacle_matr = new int*[amount];
	
	for (int i = 0; i < amount; i++)
	{
		obstacle_matr[i] = new int[coordinates];
		obstacle_matr[i][0] = obstacle_objects[i]->get_x();
		obstacle_matr[i][1] = obstacle_objects[i]->get_y();
		obstacle_matr[i][2] = obstacle_objects[i]->get_x1();
		obstacle_matr[i][3] = obstacle_objects[i]->get_y1();
	}

	play(pbike, obstacle_matr, obstacle_objects, coordinates, amount, x, y);

    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
} // main

void play(Bicycle* pBike, int** all_obstacles, Simple_obstacle** all_pObstacles, int length, int obst_amount, int startx, int starty)
{
	// ПЕРЕМЕННЫЕ
	bool is_collision = 0; // столкнулись ли
	bool is_damaged = 0; // принадлежит ли велик классу damaged

	// Показать все объекты
	for (int i = 0; i < length; i++)
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
			DamagedBike bike(startx, starty, pBike->get_handlebar(), pBike->get_rudder(),
				pBike->get_visibility(), pBike->get_wheelrad(), pBike->get_framelen(),
				pBike->get_frameheight(), pBike->get_framewide());
			pBike = &bike;
			pBike->Show(all_obstacles);
			is_damaged = 1;
			is_collision = 0;
		}
		is_collision = pBike->Drag(pBike->get_speed(), all_obstacles);
	}

} // play

