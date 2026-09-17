#include <iostream>
#include "FileReader.h"
#include <chrono>

int main()
{
    FileReader conf("test.conf");

    int val = conf.ReadInt("val_key", 0);
    double d_val = conf.ReadDouble("d_val_key", 0.0);
    std::string str = conf.ReadString("str_key", "");

    val++;
    d_val += 0.1;
    auto time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(time);
    std::tm local_time = *std::localtime(&end_time);
    char buf[90];
    strftime(buf, 90, "%Y.%m.%d_[%H-%M-%S]", &local_time);
    str = buf;

    conf.WriteInt("val_key", val);
    conf.WriteDouble("d_val_key", d_val);
    conf.WriteString("str_key", str);
    conf.Save();
}
