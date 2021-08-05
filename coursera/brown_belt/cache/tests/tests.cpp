#include "gtest/gtest.h"
#include "library.h"

#include <atomic>
#include <future>
#include <numeric>
#include <random>
#include <sstream>


void TestUnpacker(const Library &lib)
{
    BooksUnpacker unpacker;
    for (const auto &book_name : lib.book_names)
    {
        auto book = unpacker.UnpackBook(book_name);
        EXPECT_EQ(book->GetName(), book_name);
    }
}

void TestMaxMemory(const Library &lib)
{
    auto unpacker = make_shared<BooksUnpacker>();
    ICache::Settings settings;
    settings.max_memory = lib.size_in_bytes / 2;
    auto cache = MakeCache(unpacker, settings);

    for (const auto &[name, book] : lib.content)
    {
        cache->GetBook(name);
        ASSERT(unpacker->GetMemoryUsedByBooks() <= settings.max_memory);
    }
}

void TestCaching(const Library &lib)
{
    auto unpacker = make_shared<BooksUnpacker>();
    ICache::Settings settings;
    settings.max_memory = lib.size_in_bytes;
    auto cache = MakeCache(unpacker, settings);

    // Если запрашивать одну и ту же книгу подряд, то она определённо должна
    // возвращаться из кэша. Заметьте, что этого простого теста вовсе
    // недостаточно, чтобы полностью проверить правильность реализации стратегии
    // замещения элементов в кэше. Для этих целей можете написать тест
    // самостоятельно.
    cache->GetBook(lib.book_names[0]);
    cache->GetBook(lib.book_names[0]);
    cache->GetBook(lib.book_names[0]);
    EXPECT_EQ(unpacker->GetUnpackedBooksCount(), 1);
}

void TestSmallCache(const Library &lib)
{
    auto unpacker = make_shared<BooksUnpacker>();
    ICache::Settings settings;
    settings.max_memory =
        unpacker->UnpackBook(lib.book_names[0])->GetContent().size() - 1;
    auto cache = MakeCache(unpacker, settings);

    cache->GetBook(lib.book_names[0]);
    EXPECT_EQ(unpacker->GetMemoryUsedByBooks(), size_t(0));
}

void TestAsync(const Library &lib)
{
    static const int tasks_count = 10;
    static const int trials_count = 10000;

    auto unpacker = make_shared<BooksUnpacker>();
    ICache::Settings settings;
    settings.max_memory = lib.size_in_bytes - 1;
    auto cache = MakeCache(unpacker, settings);

    vector<future<void>> tasks;

    for (int task_num = 0; task_num < tasks_count; ++task_num)
    {
        tasks.push_back(async([&cache, &lib, task_num]
                              {
                                  default_random_engine gen;
                                  uniform_int_distribution<size_t> dis(0, lib.book_names.size() - 1);
                                  for (int i = 0; i < trials_count; ++i)
                                  {
                                      const auto &book_name = lib.book_names[dis(gen)];
                                      EXPECT_EQ(
                                          cache->GetBook(book_name)->GetContent(),
                                          lib.content.find(book_name)->second->GetContent());
                                  }
                                  stringstream ss;
                                  ss << "Task #" << task_num << " completed\n";
                                  cout << ss.str();
                              }));
    }

    // вызов метода get пробрасывает исключения в основной поток
    for (auto &task : tasks)
    {
        task.get();
    }
}

int main()
{
    BooksUnpacker unpacker;
    const Library lib(
        // Названия книг для локального тестирования. В тестирующей системе курсеры
        // будет другой набор, намного больше.
        {
            "Sherlock Holmes",
            "Don Quixote",
            "Harry Potter",
            "A Tale of Two Cities",
            "The Lord of the Rings",
            "Le Petit Prince",
            "Alice in Wonderland",
            "Dream of the Red Chamber",
            "And Then There Were None",
            "The Hobbit"},
        unpacker);

#define RUN_CACHE_TEST(tr, f) tr.RunTest([&lib] { f(lib); }, #f)

    TestRunner tr;
