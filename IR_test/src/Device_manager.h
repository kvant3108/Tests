#pragma once

#include <iostream>
#include <mutex>

class Device_manager
{
public:
    virtual int open() = 0;  // открыть устройство
    virtual int close() = 0; // закрыть устройство
    virtual int reset() = 0; // перезагрузить устройств

    bool isInit() const
    { // проверка инициализации устройства
        std::lock_guard<std::mutex> lock(m);
        return init_state;
    }
    bool isOpen() const
    { // проверка открыто ли устройств
        std::lock_guard<std::mutex> lock(m);
        if (!init_state)
            return false;
        return open_state;
    }

protected:
    mutable std::mutex m;
    bool init_state = false;
    bool open_state = false;
};