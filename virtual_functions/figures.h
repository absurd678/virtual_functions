#pragma once
#include <iostream>
using namespace std;

// КОНСТАНТЫ
const int COLLEN = 3;
extern const int AMOUNT;
extern const int COORDINATES;

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
	
	void Move_to(int newX, int newY, int coord_of_obstacles[][COORDINATES]);
	void Drag(int delta, int coord_of_obstacles[][COORDINATES]);
	virtual bool Show(int coord_of_obstacles[][COORDINATES]);
	virtual void Hide();
	/*void Show();
	void Hide();*/
}; // Point

//--------------------------RectAngle------------------------------------------
class RectAngle :public Point
{
protected:
	int x1;
	int y1;
public:
	RectAngle(int init_x1, int init_y1, int init_x, int init_y, bool init_visible) :Point(init_x, init_y, init_visible)
	{
		x1 = init_x1;
		y1 = init_y1;
	} // Point
	~RectAngle() {}
	// getters, setters
	int get_x1() { return x1; }
	int get_y1() { return y1; }

	virtual bool Show();
	virtual void Hide();
	/*void Show();
	void Hide();*/
}; // Point

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
	virtual bool Show(int coord_of_obstacles[][COORDINATES]);
	virtual void Hide();
	// Геттеры для всех новых полей
	int get_handlebar() { return len_handlebar;}
	int get_rudder() { return LenRudder; }
	int get_wheelrad() { return WheelRad; }
	int get_framelen() { return FrameLen; }
	int get_frameheight(){ return FrameHeight; }
	int get_framewide() { return FrameWide; }
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

	virtual bool Show();
	int get_speed() { return speed; }
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

	virtual bool Show();
	virtual void Hide();
};


//--------------------------------DamagedBike-------------------------------------------
class DamagedBike :public Bicycle
{
public:
	DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	~DamagedBike() {}

	virtual bool Show();
	virtual void Hide();
};

bool check_collision(int coord_of_obstacles[][COORDINATES], int x, int y, int x1, int y1);

