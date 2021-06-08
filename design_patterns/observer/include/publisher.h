#pragma once

#include <memory>
#include <list>
#include <cassert>
#include <iostream>

class IObserver;

class IPublisher
{
public:
    virtual ~IPublisher() = default;

    void Add(std::shared_ptr<IObserver>);

    void Remove(std::shared_ptr<IObserver>);

protected:
    virtual void Notify() const = 0;

    std::list<std::shared_ptr<IObserver>> m_observers;
};