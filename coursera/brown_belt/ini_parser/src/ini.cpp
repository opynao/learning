#include "ini.h"
#include <iterator>
#include <iostream>
#define PR(x) std::cerr << #x << " = " << x << std::endl

namespace Ini
{
    Document Load(std::istream &input)
    {
        Document document;
        Section section;
        std::string section_name;
        for (std::string current_str; std::getline(input, current_str);)
        {
            if (current_str.empty())
                continue;
            if (current_str[0] == '[')
            {
                section_name = current_str.substr(1, current_str.size() - 2);
                document.AddSection(section_name);
                continue;
            }
            auto pos = current_str.find('=');
            std::string category = current_str.substr(0, pos);
            std::string amount = current_str.substr(pos + 1);
            document.AddSection(section_name).insert({category, amount});
        }
        return document;
    }

    Section &Document::AddSection(string name)
    {
        return sections[name];
    }

    const Section &Document::GetSection(const string &name) const
    {
        return sections.at(name);
    }

    size_t Document::SectionCount() const
    {
        return sections.size();
    }
}