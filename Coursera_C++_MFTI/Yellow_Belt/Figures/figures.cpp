#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

enum class FigureType
{
	Rectangle,
	Triangle, 
	Circle
}; 

class Figure
{
public:
	virtual void Name() const = 0;
	virtual void Perimeter() const = 0;
	virtual void Area() const = 0;
};

//------------------------CIRCLE--------------------------

class Circle : public Figure
{
public:
	explicit Circle(const int radius);
	void Name() const override;
	void Perimeter() const override;
	void Area() const override;
private:
	int radius_;
};

Circle::Circle(const int radius)
	: radius_ {radius}
{
}

void Circle::Name() const
{
	std::cout << "CIRCLE";
}

void Circle::Perimeter() const
{
	double perimeter = 2 * 3.14 * radius_ ;
	std::cout << perimeter;
}

void Circle::Area() const
{
	double area = 3.14 * std::pow(radius_,2) ;
	std::cout << area;
}

//-------------------------TRIANGLE-----------------------------

class Triangle : public Figure
{
public:
	explicit Triangle(const int a, const int b, const int c);
	void Name() const override;
	void Perimeter() const override;
	void Area() const override;
private:
	int a_;
	int b_;
	int c_;
};

Triangle::Triangle(const int a, const int b, const int c)
	: a_ {a}
	, b_ {b}
	, c_ {c}
{
}

void Triangle::Name() const
{
	std::cout << "TRIANGLE";
}

void Triangle::Perimeter() const
{
	int perimeter = a_ + b_ + c_ ;
	std::cout << perimeter;
}

void Triangle::Area() const
{
	double poluPerimeter = (a_ + b_ + c_)/2;
	double area = std::pow( ( poluPerimeter * ( poluPerimeter - a_ ) * ( poluPerimeter - b_ ) * ( poluPerimeter - c_ ) ), 0.5 );
	std::cout << area;
}

//----------------RECTANGLE---------------------

class Rect : public Figure
{
public:
	Rect(const int width, const int height);
	void Name() const override;
	void Perimeter() const override;
	void Area() const override;
private:
	int width_;
	int height_;
};

Rect::Rect(const int width, const int height)
	: width_ {width}
	, height_ {height}
{
}

void Rect::Name() const
{
	std::cout << "RECT";
}

void Rect::Perimeter() const
{
	int perimeter = ( width_ + height_ ) * 2;
	std::cout << perimeter;
}

void Rect::Area() const
{
	int area = width_ * height_;
	std::cout << area;
}


std::shared_ptr<Figure> CreateFigure(std::istream& is)
{
	std::map<std::string,FigureType> mFigures
	{
		{"RECT", FigureType::Rect},
		{"TRIANGLE", FigureType::Triangle},
		{"CIRCLE", FigureType::Circle},
	};
	std::string figureType;
	is >> figureType;
	auto itFind = mFigures
	std::shared_ptr<Figure> f;
	switch(figureType)	
	{
		case FigureType::Rectangle:
			is >> x >> y;
			f = std::make_shared<Rect>(x,y);
			break; 
		case FigureType::Triangle:
			is >> x >> y >> z;
			f = std::make_shared<Triangle>(x,y,z);
			break; 
		case FigureType::Circle:
			is >> x;
			f = std::make_shared<Circle>(x);
			break; 
	}
	return f;
}


int main() 
{
	std::vector<std::shared_ptr<Figure>> figures;
	for (std::string line; std::getline(std::cin, line); ) 
	{
		std::istringstream is(line);
		std::string command;
		is >> command;
		if (command == "ADD") 
		{
			is >> std::ws;
			figures.push_back(CreateFigure(is));
		} 
		else if (command == "PRINT") 
		{
			for (const auto& current_figure : figures) 
			{
				std::cout << std::fixed << std::setprecision(3) << current_figure->Name() << " " << current_figure->Perimeter() << " " << current_figure->Area() << std::endl;
			}
		}
	}
	return 0;
}
