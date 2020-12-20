#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <map>

using Name_t = std::string;
using Perimeter_t = double;
using Area_t = double;

enum class FigureType
{
	Rectangle,
	Triangle, 
	Circle
}; 

class Figure
{
public:
	virtual	~Figure() {}
	virtual Name_t Name() const = 0;
	virtual Perimeter_t Perimeter() const = 0;
	virtual Area_t Area() const = 0;
};

//------------------------CIRCLE--------------------------

class Circle : public Figure
{
public:
	explicit Circle(const int radius);
	Name_t Name() const override;
	Perimeter_t Perimeter() const override;
	Area_t Area() const override;
private:
	int radius_;
};

Circle::Circle(const int radius)
	: radius_ {radius}
{
}

Name_t Circle::Name() const
{
	return "CIRCLE";
}

Perimeter_t Circle::Perimeter() const
{
	double perimeter = 2 * 3.14 * radius_ ;
	return perimeter;
}

Area_t Circle::Area() const
{
	double area = 3.14 * std::pow(radius_,2) ;
	return area;
}

//-------------------------TRIANGLE-----------------------------

class Triangle : public Figure
{
public:
	explicit Triangle(const int a, const int b, const int c);
	Name_t Name() const override;
	Perimeter_t Perimeter() const override;
	Area_t Area() const override;
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

Name_t Triangle::Name() const
{
	return "TRIANGLE";
}

Perimeter_t Triangle::Perimeter() const
{
	int perimeter = a_ + b_ + c_ ;
	return perimeter;
}

Area_t Triangle::Area() const
{
	double poluPerimeter = static_cast<double>(a_ + b_ + c_)/2;
	double area = pow( ( poluPerimeter * ( poluPerimeter - a_ ) * ( poluPerimeter - b_ ) * ( poluPerimeter - c_ ) ), 0.5 );
	return area;
}

//----------------RECTANGLE---------------------

class Rect : public Figure
{
public:
	Rect(const int width, const int height);
	Name_t Name() const override;
	Perimeter_t Perimeter() const override;
	Area_t Area() const override;
private:
	int width_;
	int height_;
};

Rect::Rect(const int width, const int height)
	: width_ {width}
	, height_ {height}
{
}

Name_t Rect::Name() const
{
	return "RECT";
}

Perimeter_t Rect::Perimeter() const
{
	return ( width_ + height_ ) * 2;
}

Area_t Rect::Area() const
{
	return width_ * height_;
}


std::shared_ptr<Figure> CreateFigure(std::istream& is)
{
	std::map<std::string,FigureType> mFigures
	{
		{"RECT", FigureType::Rectangle},
		{"TRIANGLE", FigureType::Triangle},
		{"CIRCLE", FigureType::Circle},
	};
	std::string figureType;
	is >> figureType;
	int x, y, z;
	auto itFind = mFigures.find(figureType);
	std::shared_ptr<Figure> f;
	switch( itFind->second )	
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
				std::cout << std::fixed << std::setprecision(3)  << current_figure->Name() << " " << current_figure->Perimeter() << " " << current_figure->Area() << std::endl;
			}
		}
	}
	return 0;
}
