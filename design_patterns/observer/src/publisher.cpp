#include "publisher.h"

void IPublisher::Add(std::shared_ptr<IObserver> observer)
{
    m_observers.push_back(std::move(observer));
}

void IPublisher::Remove(std::shared_ptr<IObserver> observer)
{
    m_observers.remove(observer);
}
