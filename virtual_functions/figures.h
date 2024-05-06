#pragma once
#include <iostream>
using namespace std;

// КОНСТАНТЫ
const int COLLEN = 3;

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
	
	void Move_to(int newX, int newY);
	void Drag(int delta); 
	virtual void Show();
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
	virtual void Show();
	virtual void Hide();
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

	virtual void Show();
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

	virtual void Show();
	virtual void Hide();
};


//--------------------------------DamagedBike-------------------------------------------
class DamagedBike :public Bicycle
{
public:
	DamagedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide);
	~DamagedBike() {}

	virtual void Show();
	virtual void Hide();
};



