#pragma once

#include <atomic>
#include <string>

// Интерфейс, представляющий книгу
class IBook
{
public:
    virtual ~IBook() = default;

    // Возвращает название книги
    virtual const std::string &GetName() const = 0;

    // Возвращает текст книги как строку.
    // Размером книги считается размер её текста в байтах.
    virtual const std::string &GetContent() const = 0;
};

// Данная реализация интерфейса IBook позволяет отследить объём памяти, в данный
// момент занимаемый всеми загруженными книгами. Для тестирования своей
// программы вы можете написать другую реализацию, которая позволит также
// убедит ься, что из кэша выгружаются в первую очередь наименее используемые
// элементы. Собственно, тестирующая система курсеры имеет как раз более
// продвинутую реализацию.
class Book : public IBook
{
public:
    Book(
        std::string name,
        std::string content,
        std::atomic<size_t> &memory_used_by_books)
        : name_(move(name)), content_(move(content)), memory_used_by_books_(memory_used_by_books)
    {
        memory_used_by_books_ += content_.size();
    }

    ~Book()
    {
        memory_used_by_books_ -= content_.size();
    }

    const std::string &GetName() const override
    {
        return name_;
    }

    const std::string &GetContent() const override
    {
        return content_;
    }

private:
    std::string name_;
    std::string content_;
    std::atomic<size_t> &memory_used_by_books_;
};
