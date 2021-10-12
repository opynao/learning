template<typename T>
class Base
{
private:
    Base() {}
//public:
//    void foo()
//    {
//        auto p = new T();
//    }
};

class Derived : public Base<Derived>
{
public:
    Derived() {}
};

int main()
{
    Derived d;
}