#include<iostream>
#include<math.h>


using namespace std;

class IShape
{
public:
	virtual double Area() = 0;
	virtual ~IShape() { cout << "IShape::dtor()" << endl; }
};

class Rectangle:IShape
{
public:
	Rectangle(int height, int weight) { this->height = height; this->weight = weight; }
	double Area() { return height*weight; }
	~Rectangle(){ cout << "Rectangle::dtor()" << endl; }
private:
	int height;
	int weight;
};

class Square :IShape
{
public:
	Square(int height) { this->height = height; }
	double Area() { return height*height; }
	~Square() { cout << "Square::dtor()" << endl; }
private:
	int height;
};

class Triangle :IShape
{
public:
	Triangle(int a,int b, int c) { this->a = a; this->b = b;this->c= c; }
	double Area() { double p = (a + b + c) / 2;  return sqrt(p*(p-a)*(p-b)*(p-c)); }
	~Triangle() { cout << "Triangle::dtor()" << endl; }
private:
	int a;
	int b;
	int c;
};

class Circle :IShape
{
public:
	Circle(int radius) { this->radius = radius; diameter = radius * 2; }
	double Area() { return 3.14*pow(radius, 2); }
	~Circle() { cout << "Circle::dtor()" << endl; }
private:
	int radius;
	int diameter;
};
