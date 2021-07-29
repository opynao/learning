#pragma once
#include <iostream>

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
    virtual void Prepare() const = 0;
    virtual void Bake() const = 0;
    virtual void Cut() const = 0;
    virtual void Box() const = 0;
};

class SeafoodPizza : public Pizza
{
public:
    void Prepare() const override
    {
        std::cout << "Seafood pizza is preparing...\n";
    }
    void Bake() const override
    {
        std::cout << "Seafood pizza is baking...\n";
    }
    void Cut() const override
    {
        std::cout << "Seafood pizza is cutting...\n";
    }
    void Box() const override
    {
        std::cout << "Seafood pizza is boxing...\n";
    }
};
class MeatPizza : public Pizza
{
public:
    void Prepare() const override
    {
        std::cout << "Meat pizza is preparing...\n";
    }
    void Bake() const override
    {
        std::cout << "Meat pizza is baking...\n";
    }
    void Cut() const override
    {
        std::cout << "Meat pizza is cutting...\n";
    }
    void Box() const override
    {
        std::cout << "Meat pizza is boxing...\n";
    }
};

class CheesePizza : public Pizza
{
public:
    void Prepare() const override
    {
        std::cout << "Cheese pizza is preparing...\n";
    }
    void Bake() const override
    {
        std::cout << "Cheese pizza is baking...\n";
    }
    void Cut() const override
    {
        std::cout << "Cheese pizza is cutting...\n";
    }
    void Box() const override
    {
        std::cout << "Cheese pizza is boxing...\n";
    }
};