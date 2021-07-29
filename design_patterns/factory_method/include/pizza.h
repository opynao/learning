#pragma once
#include "pizza_ingredient_factory.h"

#include <iostream>
#include <string>
#include <vector>

enum class PizzaType
{
    Cheese,
    Meat,
    Seafood
};

class Pizza
{
public:
    virtual ~Pizza() = default;

    Pizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory)
        : m_ingredientFactory{ingredientFactory}
    {
    }

    virtual void Prepare() = 0;

    virtual void Bake() const
    {
        std::cout << "Bake at temperature 350 C for 20 minutes\n";
    }

    virtual void Box() const
    {
        std::cout << "Place pizza into oficial PizzaStore box\n";
    }
    virtual void Cut() const
    {
        std::cout << "Cut into " << m_ingredientFactory->GetPizzaSlices() << "slices\n";
    }

protected:
    std::string m_name;

    std::shared_ptr<PizzaIngredientFactory> m_ingredientFactory;

    std::unique_ptr<Dough> m_dough;
    std::unique_ptr<Mushroom> m_mushroom;
    std::unique_ptr<Sauсe> m_sauce;
    std::unique_ptr<Onion> m_onion;
    std::unique_ptr<Sausage> m_sausage;
};