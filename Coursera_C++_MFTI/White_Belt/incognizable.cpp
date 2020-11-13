class Incognizable
{
public:
	Incognizable();
	Incognizable(const int);
	Incognizable(const int,const int);
};

Incognizable::Incognizable()
{}

Incognizable::Incognizable(const int a,const int b)
{
}


Incognizable::Incognizable(const int a)
{
}

int main()
{
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
