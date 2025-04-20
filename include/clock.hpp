#ifndef __CLOCK_HPP_
#define __CLOCK_HPP_

#include <thread>
#include <chrono>

#include"common.hpp"

namespace CPU6502{
    constexpr double CPUDefaultFrequency = 1000000;

    class Clock {
        private:
            double hz;
            std::thread backgroundThread;
            std::atomic<bool> running;
            std::atomic<int> sharedVar; 

            void loop() {
                using namespace std::chrono;
                auto interval = duration<double>(1.0 / this->hz);
            
                while (running) {
                    sharedVar = 1;
                    std::this_thread::sleep_for(interval);
                    sharedVar = 0;
                    std::this_thread::sleep_for(interval);
                }
            }
            
        public:
            Clock() : Clock(CPUDefaultFrequency) {}

            Clock(double frequencyHz) : hz(frequencyHz), running(false), sharedVar(0) {}

            void Start(){
                running = true;
                backgroundThread = std::thread(&Clock::loop, this);
            }

            void Stop(){
                running = false;
                if (backgroundThread.joinable()){
                    backgroundThread.join();
                }
            } 
            
            int Value() const{
                if (this->running){
                    return 0;
                }
                return this->sharedVar.load();
            }
    };
}
#endif // __CLOCK_HPP_
