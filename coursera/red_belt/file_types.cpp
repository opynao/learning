#include <map>
#include <sstream>
#include <string>
#include <iostream>

enum class FileType
{
    Music,
    Images,
    Movies,
    Other
};

enum class FileExtension
{
    mp3,
    flac,
    aac,
    jpg,
    bmp,
    gif,
    avi,
    mkv,
    mp4,
    other
};

std::map<FileExtension, FileType> ext2Type{
    {FileExtension::mp3, FileType::Music},
    {FileExtension::flac, FileType::Music},
    {FileExtension::aac, FileType::Music},
    {FileExtension::jpg, FileType::Images},
    {FileExtension::bmp, FileType::Images},
    {FileExtension::gif, FileType::Images},
    {FileExtension::avi, FileType::Movies},
    {FileExtension::mkv, FileType::Movies},
    {FileExtension::mp4, FileType::Movies},
    {FileExtension::other, FileType::Other}};

std::map<std::string, FileExtension> m{
    {"mp3", FileExtension::mp3},
    {"flac", FileExtension::flac},
    {"aac", FileExtension::aac},
    {"jpg", FileExtension::jpg},
    {"bmp", FileExtension::bmp},
    {"gif", FileExtension::gif},
    {"avi", FileExtension::avi},
    {"mkv", FileExtension::mkv},
    {"mp4", FileExtension::mp4}};

FileExtension FileExtensionString2Type(std::string &extension)
{
    auto it = m.find(extension);
    if (it != m.end())
        return it->second;
    return FileExtension::other;
}

std::string GetFileExtensionString(std::string &fileName)
{
    auto pos = fileName.rfind('.');
    return fileName.substr(pos + 1);
}

FileExtension GetFileExtension(std::string &fileName)
{
    auto fileExt = GetFileExtensionString(fileName);
    return FileExtensionString2Type(fileExt);
}

std::string MakeString(const std::pair<FileType, size_t> &p)
{
    std::map<FileType, std::string> fileType2String{
        {FileType::Music, "music"},
        {FileType::Images, "images"},
        {FileType::Movies, "movies"},
        {FileType::Other, "other"}};
    return fileType2String[p.first] + " " + std::to_string(p.second) + "b";
}

std::string MakeResult(const std::map<FileType, size_t> &info)
{
    std::string result;
    for (const auto &item : info)
    {
        result += MakeString(item);
        result += "\n";
    }
    return result;
}

std::string solution(std::string &S)
{
    std::map<FileType, size_t> info{
        {FileType::Music, 0},
        {FileType::Images, 0},
        {FileType::Movies, 0},
        {FileType::Other, 0}};

    std::istringstream is(S);

    for (std::string str; std::getline(is, str);)
    {
        std::istringstream is(str);
        std::string fileName;
        size_t byteNumber;
        is >> fileName;
        is >> byteNumber;
        auto fileExtension = GetFileExtension(fileName);
        auto fileType = ext2Type[fileExtension];
        info[fileType] += byteNumber;
    }
    return MakeResult(info);
}

void Test1()
{
    std::string input = "my.song.mp3 11b\ngreatSong.flac 1000b\nnot3.txt 5b\nvideo.mp4 200b\ngame.exe 100b\nmov!e.mkv 10000b";
    std::string result = "music 1011b\nimages 0b\nmovies 10200b\nother 105b\n";
    std::cerr << solution(input);
}

int main()
{
    Test1();
    return 0;
}