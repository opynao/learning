#include "serve_request.h"
#include <string>
#include <iostream>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

Stats ServeRequests(std::istream& input) 
{
  Stats result;
  for ( std::string line; std::getline(input, line); ) 
  {
    const HttpRequest req = ParseRequest( line );
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}
