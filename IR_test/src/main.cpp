#include <iostream>

#include "IR_manager.h"
#include "FileReader.h"

#include <csignal>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

IR_manager cam;
cv::Mat frame;

std::mutex m;
std::mutex lockprint;

std::condition_variable wake_up;
bool notified = false;
bool vf_notified = false;

std::atomic<bool> run{true};
bool p_flag = false,
     o_flag = false,
     v_flag = false;

void driver_func()
{
    bool local_o_flag = false;

    std::cout << "[driver]\trunning..." << std::endl;

    while (run.load())
    {
        std::unique_lock<std::mutex> locker(m);
        wake_up.wait(locker, [&]()
                     { return notified; });

        if (local_o_flag != o_flag)
        {
            if (o_flag)
            {
                int res = cam.open();
                if (res < 0)
                {
                    o_flag = false;
                    std::cout << "[driver]\tFailed to open the camera. ERROR: " << res << std::endl;
                }
                else
                {
                    std::cout << "[driver]\tThe camera was turned on" << std::endl;
                }
            }
            else
            {
                int res = cam.close();
                if (res < 0)
                {
                    o_flag = false;
                    std::cout << "[driver]\tFailed to close the camera. ERROR: " << res << std::endl;
                }
                else
                {
                    v_flag = false;
                    std::cout << "[driver]\tThe camera was turned off" << std::endl;
                }
            }
            local_o_flag = o_flag;
        }
        if (p_flag)
        {
            if (!cam.isOpen())
            {
                std::cout << "[driver]\tYou sould to open the camera" << std::endl;
            }
            else
            {
                if (cam.take_frame(frame) < 0)
                {
                    std::cout << "[driver]\tFailed to make a photo" << std::endl;
                }
                else
                {
                    frame = frame(cv::Range(0, 191), cv::Range(0, 255));
                    cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
                    frame.convertTo(frame, CV_8UC1, 255.0 / 65535);
                    cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
                    cv::applyColorMap(frame, frame, cv::COLORMAP_TURBO);
                }
            }
            p_flag = false;
        }
        if (!run.load())
        {
            std::cout << "[driver]\tEsc was pressed. closing" << std::endl;
            break;
        }

        notified = false;
    }
}
void video_flow_func()
{
    std::cout << "[video_flow]\trunning..." << std::endl;

    while (run.load())
    {
        std::unique_lock<std::mutex> locker(m);
        wake_up.wait(locker, [&]()
                     { return vf_notified; });

        if (v_flag)
        {
            if (!o_flag)
            {
                v_flag = false;
                std::cout << "[video_flow]\tThe camera sould be open" << std::endl;
            }
            else
            {
                std::cout << "[video_flow]\tThe video flow was launched" << std::endl;

                while (v_flag && o_flag && run.load())
                {
                    if (cam.take_frame(frame) < 0)
                    {
                        std::cout << "[video_flow]\tFailed to make a photo" << std::endl;
                    }
                    else
                    {
                        frame = frame(cv::Range(0, 191), cv::Range(0, 255));
                        cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
                        frame.convertTo(frame, CV_8UC1, 255.0 / 65535);
                        cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
                        cv::applyColorMap(frame, frame, cv::COLORMAP_TURBO);
                    }
                    locker.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    locker.lock();
                }

                std::cout << "[video_flow]\tThe video flow was stopped" << std::endl;
            }
        }
        vf_notified = false;
    }
}
int main()
{
    {
        FileReader conf("res/param.conf");
        std::cout << "VENDOR_ID: " << conf.ReadString("VENDOR_ID", "Not found") << std::endl;
        std::cout << "PRODUCT_ID: " << conf.ReadString("PRODUCT_ID", "Not found") << std::endl;

        const std::string vid = conf.ReadString("VENDOR_ID", "Not found");
        const std::string pid = conf.ReadString("PRODUCT_ID", "Not found");
        uint16_t VENDOR_ID = static_cast<uint16_t>(std::stoul(conf.ReadString("VENDOR_ID", "Not found"), nullptr, 0));
        uint16_t PRODUCT_ID = static_cast<uint16_t>(std::stoul(conf.ReadString("PRODUCT_ID", "Not found"), nullptr, 0));

        cam.init(VENDOR_ID, PRODUCT_ID);
    }

    cv::Mat instr(360, 480, CV_8UC3);
    cv::putText(instr, "Press O to open/close the camera", cv::Point(10, 20), 1, 1.0, cv::Scalar(176, 216, 245));
    cv::putText(instr, "Press P to make a photo", cv::Point(10, 40), 1, 1.0, cv::Scalar(176, 216, 245));
    cv::putText(instr, "Press V to start/stop the video mode", cv::Point(10, 60), 1, 1.0, cv::Scalar(176, 216, 245));
    cv::putText(instr, "Press Esc to exit", cv::Point(10, 80), 1, 1.0, cv::Scalar(176, 216, 245));
    cv::imshow("instruction", instr);

    std::thread driver(driver_func);
    std::thread video_flow(video_flow_func);

    while (run.load())
    {
        switch (cv::waitKey(25))
        {
        case 27: // выход
        {
            std::unique_lock<std::mutex> locker(m);
            run.store(false);
            notified = true;
            vf_notified = true;
            wake_up.notify_all();
        }

        break;
        case 67: // видео режим

            break;
        case 'O':
        case 'o': // влючить камеру
        {
            std::unique_lock<std::mutex> locker(m);
            o_flag = !o_flag;
            notified = true;
            wake_up.notify_all();
        }
        break;
        case 'P':
        case 'p': // сделать снимок
        {
            std::unique_lock<std::mutex> locker(m);
            p_flag = true;
            notified = true;
            wake_up.notify_all();
        }
        break;
        case 'V':
        case 'v': // Включить видео режим
        {
            std::unique_lock<std::mutex> locker(m);
            v_flag = !v_flag;
            vf_notified = true;
            wake_up.notify_all();
        }
        break;
        default:
            break;
        }
        {
            std::unique_lock<std::mutex> locker(m);
            if (frame.data != 0)
            {
                cv::imshow("image", frame);
            }
        }
    }

    driver.join();
    video_flow.join();

    return 0;
}
