#pragma once

#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <cctype>

class FileReader
{
public:
    explicit FileReader(const std::string &filePath);

    int ReadInt(const std::string &key, int defaultValue) const;
    double ReadDouble(const std::string &key, double defaultValue) const;
    std::string ReadString(const std::string &key, std::string defaultValue) const;

    void WriteInt(const std::string &key, int value);
    void WriteDouble(const std::string &key, double value);
    void WriteString(const std::string &key, std::string &value);

    void Save();

private:
    void ParseFile();
    void Trim(std::string &str) const;

    std::string filePath_;
    std::map<std::string, std::string> data_;
};