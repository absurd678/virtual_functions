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
	// getters, setters
	int get_x() { return x; }
	void set_x(int new_x) { x = new_x; }
	int get_y() { return y; }
	void set_y(int new_y) { y = new_y; }

};

class Point :public Location
{
protected:
	bool is_visible;
public:
	Point(int init_x, int init_y, bool init_visible);
	~Point();

	// getters, setters
	bool get_visibility() { return is_visible; }
	void set_visibility(bool new_visibility) { is_visible = new_visibility; }

	void Move_to(int newX, int newY);
	void Drag(int delta);
	virtual void Show();
	virtual void Hide();
}; // Point

class Circle :public Point
{
protected:
	int radius;
public:
	Circle(int init_x, int init_y, bool init_visible, int radius);
	~Circle();
	// getters, setters
	int get_radius() { return radius; }
	void set_radius(int new_radius) { radius = new_radius; }

	void Show();
	void Hide();
};

class Ring :public Circle
{
protected:
	int wide;
public:
	Ring(int init_x, int init_y, bool init_visible, int init_radius, int init_wide);
	~Ring();
	// getters, setters
	int get_wide() { return wide; }
	void set_wide(int new_wide) { wide = new_wide; }

	void Show();
	void Hide();
};