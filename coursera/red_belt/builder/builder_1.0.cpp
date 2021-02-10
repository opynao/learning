#include <iostream>
#include <vector>
#include <memory>
#include <numeric>

template< typename T >
void PrintInfo( std::vector< T > v )
{
  for( auto& item : v )
    item.info();
}

template< typename T >
void CalculateAmount( std::vector< T > v )
{
  T m;
  for( auto& item : v )
    m += item;
  m.PrintTotal( );
}

class Meal
{
protected:
  static int total_;
public:
  virtual Meal& operator=(Meal& m )
  {
    return m;
  }
  virtual ~Meal() {}
  virtual void info() {}
  virtual void PrintTotal() const {}
  virtual void SetTotal( const int t )
  {
    total_ = t;
  }
  virtual int GetTotal()
  {
    return total_;
  }
};


Meal operator+=( Meal& rhs, Meal& lhs )
{
  Meal meal;
  meal.SetTotal( lhs.GetTotal() + rhs.GetTotal() ) ;
  return meal;
}

int Meal::total_ = 0;

class Flour : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 100 g of flour" << std::endl;
    total_ += 100;
  }
  void PrintTotal( ) const override
  {
    std::cout << "\t" << total_ << " g of flour" << std::endl;
  }
};

class Water : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 250 ml of water" << std::endl;
    total_ += 250;
  }
  void PrintTotal( ) const override 
  {
    std::cout << "\t" << total_ << " ml of water" << std::endl;
  }
};

class Eggs : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 1 egg" << std::endl;
    total_ += 1;
  }
  void PrintTotal( ) const override
  {
    std::cout << "\t" << total_ << " egg(s)" << std::endl;
  }
};

class Sugar : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 10 g of sugar" << std::endl;
    total_ += 10;
  }
  void PrintTotal( ) const override
  {
    std::cout << "\t" << total_ << " g of sugar" << std::endl;
  }
};

class Yeast : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 5 g of yeast" << std::endl;
    total_ += 5;
  }
  void PrintTotal( ) const override
  {
    std::cout << "\t" << total_ << " g of yeast" << std::endl;
  }
};

class Milk : public Meal
{
public:
  void info() override
  {
    std::cout << "\tAdd 250 ml of milk" << std::endl;
    total_ += 250;
  }
  void PrintTotal( ) const override
  {
    std::cout << "\t" << total_ << " ml of milk" << std::endl;
  }
};

class Food
{
public:
  std::vector< Flour > vf;
  std::vector< Water > vw;
  std::vector< Eggs > ve;
  std::vector< Sugar > vs;
  std::vector< Yeast > vy;
  std::vector< Milk > vm;
  void info() 
  {
    int i;
    PrintInfo( vf );
    PrintInfo( vw );
    PrintInfo( ve );
    PrintInfo( vs );
    PrintInfo( vy );
    PrintInfo( vm );
  }
  void calculate()
  {
    std::cout << " ------------------- " << std::endl;
    std::cout << "Total amount of components:" << std::endl;
    CalculateAmount( vf );
    CalculateAmount( vw );
    CalculateAmount( ve );
    CalculateAmount( vs );
    CalculateAmount( vy );
    CalculateAmount( vm );
    std::cout << " ------------------- " << std::endl;
  }
};


class FoodBuilder
{
protected:
  std::unique_ptr< Food > p;
public:
  FoodBuilder()
    : p { nullptr } 
  {} 
  virtual ~FoodBuilder() {}
  virtual void createFood() {}
  virtual void addFlour() {}
  virtual void addWater() {}
  virtual void addEggs() {}
  virtual void addSugar() {}
  virtual void addYeast() {}
  virtual void addMilk() {}
  virtual std::unique_ptr< Food > getFood()
  {
    return std::move(p);
  }
};

class Pancakes : public FoodBuilder
{
public:
  void createFood() override
  {
    p = std::make_unique< Food >();
  }
  void addFlour() override
  {
    p->vf.push_back( Flour() );
  }
  void addEggs() override
  {
    p->ve.push_back( Eggs() );
    p->ve.push_back( Eggs() );
  }
  void addMilk() override
  {
    p->vm.push_back( Milk() );
  }
};

class Bread : public FoodBuilder
{
public:
  void createFood() override
  {
    p = std::make_unique< Food >();
  }
  void addFlour() override
  {
    p->vf.push_back( Flour() );
  }
  void addWater() override
  {
    p->vw.push_back( Water() );
  }
  void addYeast() override
  {
    p->vy.push_back( Yeast() );
  }
};

class Omelet : public FoodBuilder
{
public:
  void createFood() override
  {
    p = std::make_unique< Food >();
  }
  void addMilk() override
  {
    p->vm.push_back( Milk() );
  }
  void addEggs() override
  {
    p->ve.push_back( Eggs() );
    p->ve.push_back( Eggs() );
  }
};

class Director
{
public:
  std::unique_ptr< Food > createFood( FoodBuilder& builder )
  {
    builder.createFood();
    builder.addEggs();
    builder.addMilk();
    builder.addFlour();
    builder.addSugar();
    builder.addYeast();
    builder.addWater();
    return builder.getFood();
  }
};

int main()
{
  Director dir;
  Pancakes pancake;
  Bread bread;
  Omelet omelet;
  
  std::unique_ptr< Food > p = dir.createFood( pancake );
  std::unique_ptr< Food > b = dir.createFood( bread );
  std::unique_ptr< Food > o = dir.createFood( omelet );
  std::cout << "Recipe of pancakes: "  << std::endl;
  p->info();
  p->calculate();
  std::cout << "Recipe of bread: " << std::endl;
  b->info();
  b->calculate();
  std::cout << "Recipe of omelet: " << std::endl;
  o->info();
  o->calculate();
  return 0;
}
