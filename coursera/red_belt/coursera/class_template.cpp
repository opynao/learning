#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include "profile.h"
using namespace std;

/*Write the class AddElements here*/
template <typename T>
class AddElements
{
public:
    AddElements( T el )
        : elem {el}
    {}
    T add( T num )
    {
        return elem + num;
    }
private:
    T elem;
};

template <>
class AddElements <std::string>
{
public:
    AddElements( std::string el )
        : elem {el}
    {}
    std::string concatenate( std::string& num )
    {
        return elem + num;
    }
private:
    std::string elem;
};

int main () {
  int n,i;
//  std::ifstream file ("/home/vika/learning/coursera/red_belt/coursera/input10.txt");
  cin >> n;
  for(i=0;i<n;i++) {
    string type;
    cin >> type;
    if(type=="float") {
        double element1,element2;
        cin >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        cin >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        cin >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}
