#include <map>
#include <unordered_map>

bool CheckWord(const std::string &key)
{
    return key.empty();
}

int main()
{
    std::unordered_map<std::string, int> words;
    for (auto it = words.begin(); it != words.end(); ++it)
    {
        const auto key = it->first;
        if (!CheckWord(key))
        {
            words.erase(key);
        }
    }
    return 0;
}