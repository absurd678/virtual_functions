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

//-----------------------------------ОБЩИЙ РОДИТЕЛЬ---------------------------------
//--------------------------Point------------------------------------------
class Point :public Location
{
protected:
	bool is_visible;
public:
	Point(int init_x, int init_y, bool init_visible) :Location(init_x, init_y)
	{
		is_visible = init_visible;
	} // Point
	~Point() {}
	// getters, setters
	bool get_visibility() { return is_visible; }
	void set_visibility(bool new_visibility) { is_visible = new_visibility; }
	
	bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles);
	bool Drag(int delta, vector<vector<int>> coord_of_obstacles);
	bool Drag_and_leave(int delta, vector<vector<int>> coord_of_obstacles); // как драг, только без вайла
	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
	/*void Show();
	void Hide();*/
}; // Point

//------------------------------------------ПРЕПЯТСТВИЯ--------------------------------------
//--------------------------Simple_obstacle------------------------------------------
class Simple_obstacle :public Point
{
protected:
	int x1;
	int y1;
public:
	Simple_obstacle(int init_x, int init_y, int init_x1, int init_y1, bool init_visible) :Point(init_x, init_y, init_visible)
	{
		x1 = init_x1;
		y1 = init_y1;
	} // Point
	~Simple_obstacle() {}
	// getters, setters
	int get_x1() { return x1; }
	int get_y1() { return y1; }

	virtual bool Show();
	virtual void Hide();
}; // Point

//--------------------Box-------------------
class Box :public Simple_obstacle
{
protected:
	int R, G, B;
public:
	Box(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_R = 63, int init_G = 161, int init_B = 119);
	~Box() {}

	virtual bool Show();
	virtual void Hide();
};

//----------------------Tree----------------------
class Tree :public Simple_obstacle
{
protected:
	int season;
public:
	Tree(int init_x, int init_y, int init_x1, int init_y1, bool init_visible, int init_season);
	~Tree() {}

	virtual bool Show();
	virtual void Hide();
};

//-------------------Speed Bump----------------------------
class Speed_bump :public Simple_obstacle
{
public:
	Speed_bump(int init_x, int init_y, int init_x1, int init_y1, bool init_visible) :
		Simple_obstacle(init_x, init_y, init_x1, init_y1, init_visible) {}
	~Speed_bump() {}

	virtual bool Show();
	virtual void Hide();
};

//--------------------------Bicycle------------------------------------------
class Bicycle :public Point
{
protected:
	int len_handlebar; // Длина руля 
	int LenRudder;// Высота рамы руля
	int WheelRad;// Радиус колес
	int FrameLen;// Длина рамы
	int FrameHeight;// Высота рамы
	int FrameWide; // Ширина рамы
public:
	Bicycle(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible, 
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	~Bicycle() {}

	//void Move_to(int newX, int newY); // В случае статики возникает дублирование кода
	//void Drag(int delta); // тож самое
	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
	// Геттеры для всех новых полей
	int get_handlebar() { return len_handlebar;}
	int get_rudder() { return LenRudder; }
	int get_wheelrad() { return WheelRad; }
	int get_framelen() { return FrameLen; }
	int get_frameheight(){ return FrameHeight; }
	int get_framewide() { return FrameWide; }
	int get_speed() { return SPEED; }
}; // Point

//--------------------------Speed Bike-----------------------------------------
class SpeedBike : public Bicycle
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
class MountBike : public Bicycle
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
class DamagedBike :public Bicycle
{
public:
	DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	~DamagedBike() {}

	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
};

bool check_collision(vector<vector<int>> coord_of_obstacles, int x, int y, int x1, int y1);

