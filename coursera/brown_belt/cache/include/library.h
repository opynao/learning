#pragma once

struct Library
{
    vector<string> book_names;
    unordered_map<string, unique_ptr<IBook>> content;
    size_t size_in_bytes = 0;

    explicit Library(vector<string> a_book_names, IBooksUnpacker &unpacker)
        : book_names(std::move(a_book_names))
    {
        for (const auto &book_name : book_names)
        {
            auto &book_content = content[book_name];
            book_content = unpacker.UnpackBook(book_name);
            size_in_bytes += book_content->GetContent().size();
        }
    }
};
