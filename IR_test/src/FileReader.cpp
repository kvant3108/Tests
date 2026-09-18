#include "FileReader.h"
#include <filesystem>

//= Вспомогательные функции =====================//
void FileReader::Trim(std::string &str) const
{
    auto start = std::find_if_not(str.begin(), str.end(), [](int c)
                                  { return std::isspace(c); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](int c)
                                { return std::isspace(c); })
                   .base();
    str = (start < end) ? std::string(start, end) : "";
}
void FileReader::ParseFile()
{
    std::ifstream file(filePath_);
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line))
    {
        Trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos)
            continue;

        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);
        Trim(key);
        Trim(value);

        if (!key.empty())
        {
            data_[key] = value;
        }
    }
}
//===============================================//

//= Конструктор =================================//
FileReader::FileReader(const std::string &filePath) : filePath_(filePath)
{
    ParseFile();
}
//===============================================//

//= Чтение ======================================//
int FileReader::ReadInt(const std::string &key, int defaultValue) const
{
    auto it = data_.find(key);
    if (it == data_.end())
        return defaultValue;

    try
    {
        return std::stoi(it->second);
    }
    catch (...)
    {
        return defaultValue;
    }
}
double FileReader::ReadDouble(const std::string &key, double defaultValue) const
{
    auto it = data_.find(key);
    if (it == data_.end())
        return defaultValue;

    try
    {
        return std::stod(it->second);
    }
    catch (...)
    {
        return defaultValue;
    }
}
std::string FileReader::ReadString(const std::string &key, std::string defaultValue) const
{
    auto it = data_.find(key);
    if (it == data_.end())
        return defaultValue;

    try
    {
        return it->second;
    }
    catch (...)
    {
        return defaultValue;
    }
}
//===============================================//

//= Запись ======================================//
void FileReader::WriteInt(const std::string &key, int value)
{
    data_[key] = std::to_string(value);
}
void FileReader::WriteDouble(const std::string &key, double value)
{
    data_[key] = std::to_string(value);
}
void FileReader::WriteString(const std::string &key, std::string &value)
{
    data_[key] = value;
}
void FileReader::Save()
{
    std::ofstream file(filePath_);
    if (!file.is_open())
        return;

    for (const auto &[key, value] : data_)
    {
        file << key << "=" << value << "\n";
    }
}
//===============================================//