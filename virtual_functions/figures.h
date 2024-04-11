#pragma once
#include <iostream>
using namespace std;

// ���������
const int COLLEN = 3;

// -----------------������--------------------
// -------------------------------------------

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
	int colorData[COLLEN]; // ��� ��������� �����
public:
	Point(int init_x, int init_y, bool init_visible) :Location(init_x, init_y)
	{
		is_visible = init_visible;
	} // Point
	~Point() {}
	// getters, setters
	bool get_visibility() { return is_visible; }
	void set_visibility(bool new_visibility) { is_visible = new_visibility; }
	int* get_colorData() { return colorData; }
	void set_colorData(int* new_colorData);

	void Move_to(int newX, int newY);
	void Drag(int delta); // Line � Rectangle ���� ����� ���������� ���������
	virtual void Show();
	virtual void Hide();
}; // Point

class Circle :public Point
{
protected:
	int radius;
public:
	Circle(int init_x, int init_y, bool init_visible, int init_radius) :Point(init_x, init_y, init_visible)
	{
		radius = init_radius;
	} // Circle
	~Circle(){}
	// getters, setters
	int get_radius() { return radius; }
	void set_radius(int new_radius) { radius = new_radius; }
	// ������������� ������
	void Show();
	void Hide();
	int Expand(int delta); // ������ ������, ���� ������ �����.
	int Reduce(int delta); // ������ ������, ���� �� ������ ������ �������
}; // Circle

class Ring :public Circle
{
protected:
	int wide; // ������� ������
public:
	Ring(int init_x, int init_y, bool init_visible, int init_radius, int init_wide) :Circle(init_x, init_y, init_visible, init_radius)
	{
		wide = init_wide;
	} // Ring
	~Ring(){}
	// getters, setters
	int get_wide() { return wide; }
	void set_wide(int new_wide) { wide = new_wide; }
	// ������������� ������
	void Show();
	void Hide();
	int Slim(int DeltaWide); // ������� ������
	int Wide(int DeltaWide); // ������� �����
};// Ring

class Line :public Point
{
protected:
	int x1, y1; // ���������� ������ �����
public:
	Line(int init_x, int init_y, bool init_visibility, int init_x1, int init_y1) :Point(init_x, init_y, init_visibility)
	{
		x1 = init_x1; y1 = init_y1;
	} // Line
	~Line(){}
	// getters, setters
	int get_x1() { return x1; }
	void set_x1(int new_x) { x1 = new_x; }
	int get_y1() { return y1; }
	void set_y1(int new_y) { y1 = new_y; }

	// ������������� ������
	void Move_to(int newX, int newY, int newX1, int newY1); // ����������� �������
	void Drag(int delta); // Line � Rectangle ���� ����� ���������� ���������
	void Show();
	void Hide();
}; // Line

class RectAngle :public Line
{
protected:
	int wide; // ������� ����� ��-��
public:
	RectAngle(int init_x, int init_y, bool init_visibility, int init_x1, int init_y1, int init_wide) :Line(init_x, init_y, init_visibility, init_x1, init_y1)
	{
		wide = init_wide;
	} // Rectangle
	~RectAngle(){}
	// getters, setters
	int get_wide() { return wide; }
	void set_wide(int new_wide) { wide = new_wide; }

	// ������������� ������
	void Show();
	void Hide();
}; // Rectangle