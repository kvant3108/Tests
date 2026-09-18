// Менеджер управления работой тепловизора

#include "IR_manager.h"

// #define CHECKING

int Ctrl_transfer(
    libusb_device_handle *handle,
    uint8_t bmRequestType,
    uint8_t bRequest,
    uint16_t wValue,
    uint16_t wIndex,
    uint16_t wLength,
    unsigned char *data)
{
    int r = libusb_control_transfer(
        handle,
        bmRequestType,
        bRequest,
        wValue,
        wIndex,
        data,
        wLength,
        TIMEOUT);
    return r;
}
int Camera_setup(libusb_device_handle *handle)
{

    unsigned char data_ctrl[1024]{};
    int r;
    // 1-12
    r = Ctrl_transfer(handle, 0x80, 0x06, 0x0100, 0x0000, 0x0012, data_ctrl);
    r = Ctrl_transfer(handle, 0x80, 0x06, 0x0200, 0x0000, 0x0009, data_ctrl);
    r = Ctrl_transfer(handle, 0x80, 0x06, 0x0200, 0x0000, 0x0247, data_ctrl);
    r = Ctrl_transfer(handle, 0x00, 0x09, 0x0001, 0x0000, 0x0000, data_ctrl);

    // 13-16
    r = Ctrl_transfer(handle, 0x80, 0x06, 0x0305, 0x0409, 0x0004, data_ctrl);
    r = Ctrl_transfer(handle, 0x80, 0x06, 0x0305, 0x0409, 0x0016, data_ctrl);

    // 18-19
    r = Ctrl_transfer(handle, 0x00, 0x0b, 0x0000, 0x0001, 0x0000, data_ctrl);

    // 20-31
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0100, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0100, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0100, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0100, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0100, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0100, 0x0a00, 0x0002, data_ctrl);

    // 32-36, 39-45
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0200, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0200, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0200, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0200, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0200, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0200, 0x0a00, 0x0002, data_ctrl);

    // 46-57
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0300, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0300, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0300, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0300, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0300, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0300, 0x0a00, 0x0002, data_ctrl);

    // 58-69
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0400, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0400, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0400, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0400, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0400, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0400, 0x0a00, 0x0002, data_ctrl);

    // 70-81
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0500, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0500, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0500, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0500, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0500, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0500, 0x0a00, 0x0002, data_ctrl);

    // 82-93
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0600, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0600, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0600, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0600, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0600, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0600, 0x0a00, 0x0002, data_ctrl);

    // 94-105
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0700, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0700, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0700, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0700, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0700, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0700, 0x0a00, 0x0002, data_ctrl);

    // 106-117
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0800, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0800, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0800, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0800, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0800, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0800, 0x0a00, 0x0002, data_ctrl);

    // 118-129
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0900, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0900, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0900, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0900, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0900, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0900, 0x0a00, 0x0002, data_ctrl);

    // 130-141
    r = Ctrl_transfer(handle, 0xa1, 0x85, 0x0a00, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x86, 0x0a00, 0x0a00, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0a00, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0a00, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x84, 0x0a00, 0x0a00, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x87, 0x0a00, 0x0a00, 0x0002, data_ctrl);

    // 150-
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0100, 0x0001, 0x0022, data_ctrl);
    // data_ctrl
    unsigned char bytes[] = {0x1, 0x0, 0x1, 0x1, 0x80, 0x1a, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x0, 0x1};
    for (long unsigned int i = 0; i < sizeof(bytes) / sizeof(bytes[0]); i++)
    {
        data_ctrl[i] = bytes[i];
    }
    r = Ctrl_transfer(handle, 0x21, 0x01, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0200, 0x0001, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0200, 0x0001, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0100, 0x0001, 0x0022, data_ctrl);
    // data_ctrl
    unsigned char bytes1[] = {0x1, 0x0, 0x2, 0x1, 0x80, 0x1a, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x0, 0x1};
    for (long unsigned i = 0; i < sizeof(bytes1) / sizeof(bytes1[0]); i++)
    {
        data_ctrl[i] = bytes1[i];
    }
    r = Ctrl_transfer(handle, 0x21, 0x01, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x83, 0x0100, 0x0001, 0x0002, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0200, 0x0001, 0x0001, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x82, 0x0100, 0x0001, 0x0022, data_ctrl);
    r = Ctrl_transfer(handle, 0xa1, 0x81, 0x0200, 0x0001, 0x0001, data_ctrl);
    // data_ctrl
    unsigned char bytes2[] = {0x1, 0x0, 0x1, 0x1, 0x80, 0x1a, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x3, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x0, 0x1};
    for (long unsigned i = 0; i < sizeof(bytes2) / sizeof(bytes2[0]); i++)
    {
        data_ctrl[i] = bytes2[i];
    }
    r = Ctrl_transfer(handle, 0x21, 0x01, 0x0200, 0x0001, 0x0022, data_ctrl);
    // std::cout <<libusb_error_name(r) << '\n';

    r = Ctrl_transfer(handle, 0x00, 0x0b, 0x0000, 0x0100, 0x0000, data_ctrl);
    return 0;
}
cv::Mat Take_frame(libusb_device_handle *handle)
{
    int r;
    int actual_length;
    unsigned short data_frame[100352]{};
    unsigned int pixel_id = 0;
    unsigned char data_in[200786];
    bool error = false;
#ifdef CHECKING
    do
    {
        int cnt = 100;
#endif // CHECKING
        for (int i = 0; i < 41; i++)
        {
            r = libusb_bulk_transfer(handle, 0x81, data_in, (int)(sizeof(data_in) / sizeof(data_in[0])), &actual_length, TIMEOUT);
            if (r == 0)
            {
#ifdef CHECKING
                if (actual_length == 2)
                    cnt = i;

                if (i == 40 && actual_length != 2)
                {
                    error = true;
                    if (cnt != 100)
                    {
                        for (int j = 0; j < cnt + 1; j++)
                        {
                            r = libusb_bulk_transfer(handle, 0x81, data_in, (int)(sizeof(data_in) / sizeof(data_in[0])), &actual_length, TIMEOUT);
                        }
                    }
                }
                else
                    error = false;
#endif // CHECKING
                for (int k = 0; k < actual_length / 2 - 1; k++)
                {
                    data_frame[k + pixel_id] = (int)data_in[2 * (k + 1) + 1] * 256 + (int)data_in[2 * (k + 1)];
                }
                pixel_id += actual_length / 2 - 1;
            }
            else
            {
                fprintf(stderr, "Camera: Error reading: %s\n", libusb_error_name(r));
            }
        }

        pixel_id = 0;
#ifdef CHECKING
    } while (error);
#endif // CHECKING

    cv::Mat frame(392, 256, CV_16UC1);
    for (int y = 0; y < frame.rows; y++)
    {
        for (int x = 0; x < frame.cols; x++)
        {
            frame.at<unsigned short>(y, x) = data_frame[256 * y + x];
        }
    }

    return frame;
}

//= Методы класса =====//

int IR_manager::init(const uint16_t VENDOR_ID, const uint16_t PRODUCT_ID)
{
    std::lock_guard<std::mutex> lock(m);
    this->VENDOR_ID = VENDOR_ID;
    this->PRODUCT_ID = PRODUCT_ID;

    r = libusb_init(&ctx);
    if (r == 0)
        init_state = true;
    else
        init_state = false;

    return r;
}

int IR_manager::open()
{
    std::lock_guard<std::mutex> lock(m);
    if (!init_state)
        return -101;
    if (open_state)
        return 1;

    // включение тепловизора
    handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    if (!handle)
    {
        open_state = false;
        return -2;
    }
    libusb_reset_device(handle);
    libusb_detach_kernel_driver(handle, 1);
    libusb_claim_interface(handle, 1);
    open_state = true;

    // попытка применить настройки
    try
    {
        Camera_setup(handle);
    }
    catch (...)
    {
        libusb_release_interface(handle, 1);
        libusb_close(handle);
        handle = nullptr;
        open_state = false;
        return -3;
    }
    return 0;
}
int IR_manager::close()
{
    std::lock_guard<std::mutex> lock(m);
    if (!init_state)
        return -101;
    if (!open_state)
        return 1;

    libusb_release_interface(handle, 1);
    libusb_close(handle);
    handle = nullptr;
    open_state = false;
    return 0;
}
int IR_manager::reset()
{
    int res;
    res = this->close();
    if (res < 0)
        return res;
    res = this->open();
    return res;
}

bool IR_manager::isConnected()
{
    std::lock_guard<std::mutex> lock(m);
    if (!init_state)
        return false;

    libusb_device **devs;
    ssize_t cnt = libusb_get_device_list(ctx, &devs);

    if (cnt < 0)
    {
        return false;
    }
    bool found = false;
    for (ssize_t i = 0; i < cnt; i++)
    {
        libusb_device_descriptor desc;
        int r1 = libusb_get_device_descriptor(devs[i], &desc);

        if (r1 == 0 && desc.idVendor == VENDOR_ID && desc.idProduct == PRODUCT_ID)
        {
            found = true;
            break;
        }
    }
    libusb_free_device_list(devs, 1);
    return found;
}

bool IR_manager::get_error()
{
    std::lock_guard<std::mutex> lock(m);
    if (!init_state)
        return false;
    return cam_error;
}
void IR_manager::set_error(bool flag)
{
    std::lock_guard<std::mutex> lock(m);
    cam_error = flag;
}

int IR_manager::take_frame(cv::Mat &frame)
{
    std::lock_guard<std::mutex> lock(m);
    if (!init_state)
        return -101;
    if (!open_state)
        return -102;
    frame = Take_frame(handle);
    frame = Take_frame(handle);
    return 0;
}
//=====================//