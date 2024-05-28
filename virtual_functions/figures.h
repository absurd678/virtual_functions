#pragma once
#include <iostream>
#include <vector>
using namespace std;

// ���������
const int COLLEN = 3;
const int SPEED = 25; // ����������� ��������

// -----------------������--------------------
// -------------------------------------------
//--------------------------------------------


// -----------------Location------------------
//class Location
//{
//protected:
//	int x; int y;
//public:
//	Location(int init_x, int init_y) {
//		x = init_x;
//		y = init_y;
//	} // Location
//	~Location() {}
//	// getters, setters
//	
//
//}; // Location

//-----------------------------------����� �������� (���������)---------------------------------
//--------------------------IPoint------------------------------------------
class IPoint // ���������
{
public:
	
	// getters, setters
	virtual bool get_visibility() = 0;
	virtual void set_visibility(bool new_visibility) = 0;
	
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles) = 0;
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles) = 0;
}; // Point

//------------------------------------------�����������--------------------------------------
//--------------------------ABC_obstacle------------------------------------------
class ABC_obstacle :public IPoint
{
protected:
	int x; int y;
	int x1;
	int y1;
	int is_visible;
public:
	ABC_obstacle(int init_x, int init_y, int init_x1, int init_y1, bool init_visible)
	{
		x = init_x;
		y = init_y;
		x1 = init_x1;
		y1 = init_y1;
		is_visible = init_visible;
	}
	// ���������� ������������ �������
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles); // �����������: ���������� ����������� �� �����
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles); // � while
	virtual bool get_visibility() { return is_visible; }
	virtual void set_visibility(bool new_visibility) { is_visible = new_visibility; }
	
	// getters, setters
	int get_x() { return x; }
	void set_x(int new_x) { x = new_x; }
	int get_y() { return y; }
	void set_y(int new_y) { y = new_y; }
	int get_x1() { return x1; }
	int get_y1() { return y1; }

	// ������ ����������� ������
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

	// ���������� ����������� �������
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
	// ���������� ����������� �������
	virtual void Show();
	virtual void Hide();
};

//-------------------Speed Bump----------------------------
class Speed_bump :public ABC_obstacle
{
public:
	Speed_bump(int init_x, int init_y, int init_x1, int init_y1, bool init_visible);
	~Speed_bump() {}
	// ���������� ����������� �������
	virtual void Show();
	virtual void Hide();
};

//--------------------------Bicycle------------------------------------------
class ABC_Bicycle :public IPoint
{
protected:
	int x; int y;
	int is_visible; // ����� �� �����
	int len_handlebar; // ����� ���� 
	int LenRudder;// ������ ���� ����
	int WheelRad;// ������ �����
	int FrameLen;// ����� ����
	int FrameHeight;// ������ ����
	int FrameWide; // ������ ����
public:
	ABC_Bicycle(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide)
	{
		x = init_x;
		y = init_y;
		len_handlebar = in_len_handlebar;
		LenRudder = inLenRudder;
		is_visible = init_visible;
		WheelRad = inWheelRad;
		FrameLen = inFrameLen;
		FrameHeight = inFrameHeight;
		FrameWide = inFrameWide;
	}
	// ���������� ������������ �������
	virtual bool Move_to(int newX, int newY, vector<vector<int>> coord_of_obstacles); 
	virtual bool Drag(int delta, vector<vector<int>> coord_of_obstacles); // ��� while
	virtual bool get_visibility() { return is_visible; }
	virtual void set_visibility(bool new_visibility) { is_visible = new_visibility; }

	// ������� ��� ���� ����� �����
	int get_x() { return x; }
	void set_x(int new_x) { x = new_x; }
	int get_y() { return y; }
	void set_y(int new_y) { y = new_y; }
	int get_handlebar() { return len_handlebar;}
	int get_rudder() { return LenRudder; }
	int get_wheelrad() { return WheelRad; }
	int get_framelen() { return FrameLen; }
	int get_frameheight(){ return FrameHeight; }
	int get_framewide() { return FrameWide; }
	int get_speed() { return SPEED; }

	// ������ ����������� �������
	virtual bool Show(vector<vector<int>> coord_of_obstacles) = 0;
	virtual void Hide() = 0;
}; // Point

//--------------------------Speed Bike-----------------------------------------
class SpeedBike : public ABC_Bicycle
{
protected:
	int speed; // ������������� ��������
public:
	SpeedBike(int init_x, int init_y, int in_len_handlebar, int inLenRudder, bool init_visible,
		int inWheelRad, int inFrameLen, int inFrameHeight, int inFrameWide, int init_speed);
	~SpeedBike(){}

	virtual bool Show(vector<vector<int>> coord_of_obstacles);
	virtual void Hide();
	int get_speed() { return speed; } // �������� ������ ����� ������
};


//---------------------------------Mount Bike---------------------------------------
class MountBike : public ABC_Bicycle
{
protected:
	int wheel_wide; // ������� �����
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

