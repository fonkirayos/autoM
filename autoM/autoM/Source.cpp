#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std::chrono;

int main() {
    INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    //virtual key codes https://docs.microsoft.com/es-es/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
    ip.ki.wVk = 0x4D; // virtual-key code for the "m" key
 
    std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

    std::cout << "WOOOOLAAAZ" << std::endl;
    while (true)
    {
            // Maintain designated frequency of 20 Hz (50 ms per frame)
            a = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> work_time = a - b;

            if (work_time.count() < 50.0)
            {
                std::chrono::duration<double, std::milli> delta_ms(50.0 - work_time.count());
                auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
                std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
            }

            b = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> sleep_time = b - a;

            // Your code here
            ip.ki.dwFlags = 0; // dwflags 0 = key pressed
            SendInput(1, &ip, sizeof(INPUT));

            // Release 
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
            //printf("Time: %f \n", (work_time + sleep_time).count());
    }
    return 0;
}