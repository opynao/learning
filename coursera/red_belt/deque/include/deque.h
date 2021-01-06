#pragma once
#include <vector>
#include <stdexcept>

template <typename T>
class Deque
{
public:
    Deque() {}
    bool Empty() const;
    size_t Size() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& At(size_t index);
    const T& At(size_t index) const;
    T& Front();
    const T& Front() const;
    T& Back();
    const T& Back() const;
    void PushBack(const T& value);
    void PushFront(const T& value);
private:
    std::vector<T> m_pushFront {};
    std::vector<T> m_pushBack {};
};

template <typename T>
bool Deque<T>::Empty() const
{
    return (m_pushBack.empty() && m_pushFront.empty());
}

template <typename T>
size_t Deque<T>::Size() const
{
    return (m_pushBack.size() + m_pushFront.size());
}

template <typename T>
T& Deque<T>::operator[](size_t index)
{
    if( index < m_pushFront.size())
        return m_pushFront[(m_pushFront.size() - index - 1)];
    index -= m_pushFront.size();
    if( (index + 1) > m_pushBack.size() )
        throw std::out_of_range("");
    return m_pushBack[index];
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const
{
    if( index < m_pushFront.size())
        return m_pushFront[(m_pushFront.size() - index - 1)];
    index -= m_pushFront.size();
    if( (index + 1) > m_pushBack.size() )
        throw std::out_of_range("");
    return m_pushBack[index];
}

template <typename T>
T& Deque<T>::At(size_t index)
{
    if( index < m_pushFront.size())
        return m_pushFront[m_pushFront.size() - index - 1];
    index -= m_pushFront.size();
    if( (index + 1) > m_pushBack.size() )
        throw std::out_of_range("");
    return m_pushBack[index];
}

template <typename T>
const T& Deque<T>::At(size_t index) const
{
    if( index < m_pushFront.size())
        return m_pushFront[m_pushFront.size() - index - 1];
    index -= m_pushFront.size();
    if( (index + 1) > m_pushBack.size() )
        throw std::out_of_range("");
    return m_pushBack[index];
}

template <typename T>
T& Deque<T>::Front()
{
    if( m_pushFront.empty() )
       return m_pushBack.front();
    return m_pushFront.back();
}

template <typename T>
const T& Deque<T>::Front() const
{
   if( m_pushFront.empty() )
      return m_pushBack.front();
   return m_pushFront.back();
}

template <typename T>
T& Deque<T>::Back()
{
    if( m_pushBack.empty() )
        return m_pushFront.front();
    return m_pushBack.back();
}

template <typename T>
const T& Deque<T>::Back() const
{
    if( m_pushBack.empty() )
       return m_pushFront.front();
    return m_pushBack.back();
}

template <typename T>
void Deque<T>::PushBack(const T& value)
{
    m_pushBack.push_back(value);
}

template <typename T>
void Deque<T>::PushFront(const T& value)
{
    m_pushFront.push_back(value);
}

