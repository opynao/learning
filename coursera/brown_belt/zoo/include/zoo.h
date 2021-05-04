#pragma once
#include "animals.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

using Zoo = std::vector<std::unique_ptr<Animal>>;

// Эта функция получает на вход поток ввода и читает из него описание зверей.
// Если очередное слово этого текста - Tiger, Wolf или Fox, функция должна поместить соответствующего зверя в зоопарк.
// В противном случае она должна прекратить чтение и сгенерировать исключение runtime_error.
Zoo CreateZoo(std::istream &in)
{
    Zoo zoo;
    std::string word;
    while (in >> word)
    {
        if (word == "Tiger")
            zoo.push_back(std::make_unique<Tiger>());

        else if (word == "Wolf")
            zoo.push_back(std::make_unique<Wolf>());

        else if (word == "Fox")
            zoo.push_back(std::make_unique<Fox>());

        else
            throw std::runtime_error("Unknown animal!");
    }
    return zoo;
}

// Эта функция должна перебрать всех зверей в зоопарке в порядке их создания
// и записать в выходной поток для каждого из них результат работы виртуальной функции voice.
// Разделяйте голоса разных зверей символом перевода строки '\n'.
void Process(const Zoo &zoo, std::ostream &out)
{
    for (const auto &animal : zoo)
        out << animal->Voice() << "\n";
}