#pragma once

#include "book.h"

#include <memory>
#include <string>
#include <atomic>

// Интерфейс, позволяющий распаковывать книги
class IBooksUnpacker
{
public:
    virtual ~IBooksUnpacker() = default;

    // Распаковывает книгу с указанным названием из хранилища
    virtual std::unique_ptr<IBook> UnpackBook(const std::string &book_name) = 0;
};

// Данная реализация интерфейса IBooksUnpacker позволяет отследить объём памяти,
// в данный момент занимаемый всеми загруженными книгами и запросить количество
// обращений к методу UnpackBook(). Для тестирования своей программы вы можете
// написать другую реализацию. Собственно, тестирующая система курсеры имеет как
// раз более продвинутую реализацию.
class BooksUnpacker : public IBooksUnpacker
{
public:
    std::unique_ptr<IBook> UnpackBook(const std::string &book_name) override
    {
        ++unpacked_books_count_;
        return std::make_unique<Book>(
            book_name,
            "Dummy content of the book " + book_name,
            memory_used_by_books_);
    }

    size_t GetMemoryUsedByBooks() const
    {
        return memory_used_by_books_;
    }

    int GetUnpackedBooksCount() const
    {
        return unpacked_books_count_;
    }

private:
    // Шаблонный класс atomic позволяет безопасно использовать скалярный тип из
    // нескольких потоков. В противном случае у нас было бы состояние гонки.
    std::atomic<size_t> memory_used_by_books_ = 0;
    std::atomic<int> unpacked_books_count_ = 0;
};
