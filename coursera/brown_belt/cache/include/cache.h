#pragma once

#include "book.h"
#include "books_unpacker.h"

#include <memory>
#include <string>

// Интерфейс, представляющий кэш
class ICache
{
public:
  // Настройки кэша
  struct Settings
  {
    // Максимальный допустимый объём памяти, потребляемый закэшированными
    // объектами, в байтах
    size_t max_memory = 0;
  };

  using BookPtr = std::shared_ptr<const IBook>;

public:
  virtual ~ICache() = default;

  // Возвращает книгу с заданным названием. Если её в данный момент нет
  // в кэше, то предварительно считывает её и добавляет в кэш. Следит за тем,
  // чтобы общий объём считанных книг не превосходил указанного в параметре
  // max_memory. При необходимости удаляет из кэша книги, к которым дольше всего
  // не обращались. Если размер самой книги уже больше max_memory, то оставляет
  // кэш пустым.
  virtual BookPtr GetBook(const std::string &book_name) = 0;
};

// Создаёт объект кэша для заданного распаковщика и заданных настроек
std::unique_ptr<ICache> MakeCache(
    std::shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings &settings);
