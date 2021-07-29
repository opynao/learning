#include "pizza_store.h"

int main()
{
    PizzaStore store(std::make_unique<SimplePizzaFactory>());

    auto cheesePizza = store.OrderPizza(PizzaType::Cheese);
    auto meatPizza = store.OrderPizza(PizzaType::Meat);
    auto seafoodPizza = store.OrderPizza(PizzaType::Seafood);

    return 0;
}