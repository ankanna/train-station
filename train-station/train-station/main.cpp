#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Train.h"
#include "Platform.h"
#include <string>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>

// waits until train goes to platform
void provide_trains(std::vector<Train> trains)
{
    int train_coutner = 0;
    while(1)
    {
        std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
        StaticWrapper::list_cv.wait(lock, []{ return StaticWrapper::is_free_slot == true; });
        trains.push_back(Train(train_coutner));
        train_coutner++;
        StaticWrapper::is_free_slot = false;
    }
}

//void write_trains(List<Train> trains, WINDOW* b)
//{
//    while(1)
//    {
//
//    }
//}

int main()
{
    //WINDOW * a, b;

    
    
    std::vector<Train> trains;
    std::vector<Platform> platforms;

    
    for(int i = 0; i < 3; i++){
        Platform platform(i+1);
        platforms.push_back(platform);
    }
    
    for(int i = 0; i < 6; i++){
        Train train(i+1);
        trains.push_back(train);
    }
    
    //std::cout << platforms[0].number;
    
    std::thread thread1(&Platform::work, platforms[0], trains);
    std::thread thread2(&Platform::work, platforms[1], trains);
    std::thread thread3(&Platform::work, platforms[2], trains);
    std::thread thread4(&Train::wait, trains[0]);
    std::thread thread5(&Train::wait, trains[1]);
    std::thread thread6(&Train::wait, trains[2]);


    std::thread thread_provider(provide_trains,trains);
    
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread_provider.join();

}

