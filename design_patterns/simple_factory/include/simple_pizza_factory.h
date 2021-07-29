#pragma once
#include <memory>

#include "pizza.h"

class SimplePizzaFactory
{
public:
    std::shared_ptr<Pizza> CreatePizza(PizzaType &type)
    {
        std::shared_ptr<Pizza> pizza = nullptr;
        switch (type)
        {
        case PizzaType::Cheese:
            pizza = std::make_shared<CheesePizza>();
            break;
        case PizzaType::Meat:
            pizza = std::make_shared<MeatPizza>();
            break;
        case PizzaType::Seafood:
            pizza = std::make_shared<SeafoodPizza>();
            break;
        }
        return pizza;
    }
};