#pragma once
#include <iostream>
using namespace std;

class Location
{
protected:
	int x; int y;
public:
	Location(int init_x, int init_y);
	~Location();
};

class Point :public Location
{
protected:
	bool is_visible;
public:
	Point(int init_x, int init_y, bool is_visible);
	~Point();
	virtual void Show();
	virtual void Hide();
};

class Circle :public Point
{
protected:
	int radius;
public:
	Circle(int init_x, int init_y, bool is_visible, int radius);
	~Circle();
	void Show();
	void Hide();
};

class Ring :public Circle
{
protected:
	int wide;
public:
	Ring(int init_x, int init_y, bool is_visible, int init_radius, int init_wide);
	~Ring();
	void Show();
	void Hide();
};