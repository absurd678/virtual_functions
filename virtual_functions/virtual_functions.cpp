// virtual_functions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
using namespace std;
#include "figures.h"

const int FrameWide = 10;

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


HDC hdc;
int main()
{
    hdc = GetDC(GetConsoleWindow()); // Получаем контекст устройства консоли
    
    ReleaseDC(GetConsoleWindow(), hdc); // Освобождаем контекст устройства после использования
}

void CreateBike(int len_handlebar, int LenRudder, int WheelRad, int FrameLen, int FrameHeight, int x, int y, Bike& new_bike)
{
    int color[3] = { 255, 0, 0 };
    int init_x, init_y, init_x1, init_y1;
    
    new_bike.handlebar = &RectAngle(x, y, 0, x + len_handlebar, y + FrameWide, FrameWide, color);
    
    init_x = x + len_handlebar / 2 - FrameWide / 2;
    init_y = y + FrameWide;
    new_bike.rudder_frame = &RectAngle(init_x, init_y, 0, init_x+FrameWide, y + LenRudder, FrameWide, color);

    //init_x = x+...
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
