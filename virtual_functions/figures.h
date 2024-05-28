#pragma once
#include <iostream>
#include <vector>
using namespace std;

// КОНСТАНТЫ
const int COLLEN = 3;
const int SPEED = 25; // константная скорость

// -----------------КЛАССЫ--------------------
// -------------------------------------------
//--------------------------------------------


// -----------------Location------------------
class Location
{
protected:
	int x; int y;
public:
	Location(int init_x, int init_y) {
		x = init_x;
		y = init_y;
	} // Location
	~Location() {}
	// getters, setters
	int get_x() { return x; }
	void set_x(int new_x) { x = new_x; }
	int get_y() { return y; }
	void set_y(int new_y) { y = new_y; }

}; // Location

//-----------------------------------ОБЩИЙ РОДИТЕЛЬ (ИНТЕРФЕЙС)---------------------------------
//--------------------------IPoint------------------------------------------
class IPoint: public Location // ИНТЕРФЕЙС
{
public:
	IPoint(int init_x, int init_y):Location(init_x, init_y){}  // Объект создать нельзя!
	// getters, setters
	virtual bool get_visibility() = 0;
	virtual void set_visibility(bool new_visibility) = 0;
	
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles) = 0;
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles) = 0;
}; // Point

//------------------------------------------ПРЕПЯТСТВИЯ--------------------------------------
//--------------------------ABC_obstacle------------------------------------------
class ABC_obstacle :public IPoint // Абстрактный класс! Объект создать нельзя!
{
protected:
	
	int x1;
	int y1;
	int is_visible;
public:
	ABC_obstacle(int init_x, int init_y, int init_x1, int init_y1, bool init_visible);
	// РЕАЛИЗАЦИЯ ИНТЕРФЕЙСНЫХ МЕТОДОВ
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles); // перегрузили: координаты препятствий не нужны
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles); // с while
	virtual bool get_visibility() { return is_visible; }
	virtual void set_visibility(bool new_visibility) { is_visible = new_visibility; }
	
	// getters, setters
	int get_x1() { return x1; }
	int get_y1() { return y1; }

	// ЧИСТЫЕ ВИРТУАЛЬНЫЕ МЕТОДЫ
	virtual void Show() = 0;
	virtual void Hide() = 0;
}; // Point

//--------------------Box-------------------
class Box :public ABC_obstacle
{
protected:
	int R, G, B;
public:
	Box(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_R = 63, int init_G = 161, int init_B = 119);
	~Box() {}

	// РЕАЛИЗАЦИЯ АБСТРАКТНЫХ МЕТОДОВ
	virtual void Show();
	virtual void Hide();
};

//----------------------Tree----------------------
class Tree :public ABC_obstacle
{
protected:
	int season;
public:
	Tree(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_season);
	~Tree() {}
	// РЕАЛИЗАЦИЯ АБСТРАКТНЫХ МЕТОДОВ
	virtual void Show();
	virtual void Hide();
};

//-------------------Speed Bump----------------------------
class Speed_bump :public ABC_obstacle
{
public:
	Speed_bump(int init_x, int init_y, int init_x1, int init_y1, bool init_visible);
	~Speed_bump() {}
	// РЕАЛИЗАЦИЯ АБСТРАКТНЫХ МЕТОДОВ
	virtual void Show();
	virtual void Hide();
};

//--------------------------Bicycle------------------------------------------
class ABC_Bicycle :public IPoint // Абстрактный класс! Объект создать нельзя!
{
protected:
	int is_visible; // Виден ли велик
	int len_handlebar; // Длина руля 
	int LenRudder;// Высота рамы руля
	int WheelRad;// Радиус колес
	int FrameLen;// Длина рамы
	int FrameHeight;// Высота рамы
	int FrameWide; // Ширина рамы
public:
	ABC_Bicycle(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	// РЕАЛИЗАЦИЯ ИНТЕРФЕЙСНЫХ МЕТОДОВ
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles); 
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles); // без while
	virtual bool get_visibility() { return is_visible; }
	virtual void set_visibility(bool new_visibility) { is_visible = new_visibility; }

	// Геттеры для всех новых полей
	
	int get_handlebar() { return len_handlebar;}
	int get_rudder() { return LenRudder; }
	int get_wheelrad() { return WheelRad; }
	int get_framelen() { return FrameLen; }
	int get_frameheight(){ return FrameHeight; }
	int get_framewide() { return FrameWide; }
	int get_speed() { return SPEED; }

	// ЧИСТЫЕ ВИРТУАЛЬНЫЕ ФУНКЦИИ
	virtual bool Show(vector<vector<int>> coord_of_obstacles) = 0;
	virtual void Hide() = 0;
}; // Point

//--------------------------Speed Bike-----------------------------------------
class SpeedBike : public ABC_Bicycle
{
protected:
	int speed; // настраиваемая скорость
public:
	SpeedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_speed);
	~SpeedBike(){}

	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
	int get_speed() { return speed; } // Скорость теперь можно менять
};


//---------------------------------Mount Bike---------------------------------------
class MountBike : public ABC_Bicycle
{
protected:
	int wheel_wide; // толщина колес
public:
	MountBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_wheel_wide);
	~MountBike() {}

	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
};


//--------------------------------DamagedBike-------------------------------------------
class DamagedBike :public ABC_Bicycle
{
public:
	DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	~DamagedBike() {}

	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
};

bool check_collision(vector<vector<int>> coord_of_obstacles, int x, int y, int x1, int y1);

