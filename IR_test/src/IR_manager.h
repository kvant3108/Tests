#pragma once

#include "Device_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <opencv2/opencv.hpp>


//= Функции работы с тепловизором =======================//
#define ENDPOINT_OUT 0x03  // OUT endpoint
#define ENDPOINT_IN  0x01  // IN endpoint
#define TIMEOUT 0  
int Ctrl_transfer                                   
(
    libusb_device_handle* handle,
    uint8_t bmRequestType,
    uint8_t bRequest,
    uint16_t wValue,
    uint16_t wIndex,
    uint16_t wLength,
    unsigned char* data
);
int Camera_setup(libusb_device_handle* handle);   
cv::Mat Take_frame(libusb_device_handle* handle);
//=======================================================//


class IR_manager: public Device_manager
{
    public:
        int init(const uint16_t, const uint16_t); // Проинициализировать камеру

        int open() override;                  // Включить камеру
        int close() override;                 // Выключить камеру
        int reset() override;                 // Перезагрузить камеру

        bool isConnected();                   // Есть ли соединение с камерой

        bool get_error();                     // Получить состояние ошибки камеры
        void set_error(bool);                 // Установить состояние ошибки камеры

        int take_frame(cv::Mat&);             // получить кадр

    private:
        libusb_device_handle* handle = NULL;  //
        libusb_context* ctx = NULL;           // Работа с libusb
        int r = -1;                           //

        bool cam_error = false;               // ошибка камеры
        uint16_t VENDOR_ID;                   // VENDOR_ID камеры
        uint16_t PRODUCT_ID;                  // PRODUCT_ID камеры

};