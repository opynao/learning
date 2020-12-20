#include <iostream>
#include <string>


using namespace std;

class Animal {
public:
	Animal(const std::string& name)
	: Name(name)
	{
	}
	const string Name;
};


class Dog : public Animal 
{
public:
    Dog(const std::string& name)
	: Animal(name)
	{
	}
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main()
{
	Dog a("vasisuali");
	std::string* p = const_cast<std::string*>(&a.Name);
	*p = "Vasyan";
	a.Bark();
	return 0;

}
