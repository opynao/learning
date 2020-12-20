#include "query.h"

std::istream& operator >> (std::istream& is, Query& q) 
{
	q.Input(is);
	return is;
}

void Query::Input(std::istream& is)
{
	std::string query {};	
	is >> query;
	auto itFind = mQueries.find(query);
	type = itFind->second;
	
	switch(type)
	{
		case QueryType::AddRect:
			AddCommand( is, FigureType::Rectangle );
			break;
		case QueryType::AddTriangle:
		        AddCommand( is, FigureType::Triangle );
			break;
		case QueryType::AddCircle:
		        AddCommand( is, FigureType::Circle );
			break;
		case QueryType::Print:
			PrintCommand();
			break;
	}
}

void Query::AddCommand(std::istream& is, FigureType figure)
{
	switch(FigureType)
	{
		case FigureType::Rectangle:
			is >> x >> y;
			rectangles.push_back({x,y});
			break; 
		case FigureType::Triangle:
			is >> x >> y >> z;
			triangles.push_back({x,y,z});
			break; 
		case FigureType::Circle:
			is >> x;
			circles.push_back(x);
			break; 
	}
}


