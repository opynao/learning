#pragma once
#include <string>
#include <vector>
#include <map>
#include <istream>

using rectangles_t = std::vector<std::pair<int>>;
using triangles_t = std::vector<std::vector<int>>;
using circles_t = std::vector<int>;


enum class QueryType 
{
	AddRect,
	AddTriangle,
	AddCircle,
	Print
};

enum class FigureType
{
	Rectangle,
	Triangle, 
	Circle
} 

struct Query 
{
	QueryType type;
	rectangles_t rectangles;
	triangles_t triangles;
	circles_t circles;
	int x, y, z;
	
	std::map<std::string,QueryType> mQueries
	{
		{"ADD RECT", QueryType::AddRect},
		{"ADD TRIANGLE", QueryType::AddTriangle},
		{"ADD CIRCLE", QueryType::AddCircle},
		{"PRINT", QueryType::Print},
	};

	void Input( std::istream& );
	void AddCommand( std::istream&, FigureType );
	void PrintCommand( std::istream& );
};

std::istream& operator >> (std::istream& is, Query& q);
