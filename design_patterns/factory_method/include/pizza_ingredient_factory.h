#pragma once
#include "ingredients.h"

#include <memory>

class PizzaIngredientFactory
{
public:
    virtual ~PizzaIngredientFactory() = default;
    virtual std::unique_ptr<Dough> CreateDough() const = 0;
    virtual std::unique_ptr<Onion> CreateOnion() const = 0;
    virtual std::unique_ptr<Mushroom> CreateMushroom() const = 0;
    virtual std::unique_ptr<Sauсe> CreateSause() const = 0;
    virtual std::unique_ptr<Sausage> CreateSasauge() const = 0;
    virtual std::string GetPizzaStyle() const = 0;
    virtual std::string GetPizzaSlices() const = 0;
};

class NYStylePizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    std::unique_ptr<Dough> CreateDough() const override
    {
        return std::make_unique<ThickDough>();
    }
    std::unique_ptr<Onion> CreateOnion() const override
    {
        return std::make_unique<RedOnion>();
    }
    std::unique_ptr<Mushroom> CreateMushroom() const override
    {
        return std::make_unique<ChampignonMushroom>();
    }
    std::unique_ptr<Sauсe> CreateSause() const override
    {
        return std::make_unique<TomatoSauсe>();
    }
    std::unique_ptr<Sausage> CreateSasauge() const override
    {
        return std::make_unique<DoctorsSausage>();
    }
    std::string GetPizzaStyle() const override
    {
        return "NY Style ";
    }
    std::string GetPizzaSlices() const override
    {
        return "square";
    }
};

class MinskStylePizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    std::unique_ptr<Dough> CreateDough() const override
    {
        return std::make_unique<ThinDough>();
    }
    std::unique_ptr<Onion> CreateOnion() const override
    {
        return std::make_unique<WhiteOnion>();
    }
    std::unique_ptr<Mushroom> CreateMushroom() const override
    {
        return std::make_unique<WhiteMushroom>();
    }
    std::unique_ptr<Sauсe> CreateSause() const override
    {
        return std::make_unique<CezarSauce>();
    }
    std::unique_ptr<Sausage> CreateSasauge() const override
    {
        return std::make_unique<SalamiSausage>();
    }
    std::string GetPizzaStyle() const override
    {
        return "Minsk Style ";
    }
    std::string GetPizzaSlices() const override
    {
        return "diagonal";
    }
};