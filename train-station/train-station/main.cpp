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

void provide_trains(std::vector<Train> trains)
{
    // couter to provide sequent train numbers (without dupilcation of trains that drove away)
    int train_coutner = 0;
    
    while(1)
    {
        // wait until train goes to free platform
        // https://github.com/Scony/systemy-operacyjne-2/blob/master/projekt/zajecia-3-4-atomic-condvar/program7-cv-wait-pred.cpp
        
        std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
        StaticWrapper::list_cv.wait(lock, []{ return StaticWrapper::is_free_slot == true; });
        
        // add new train
        Train train(train_coutner, StaticWrapper::train_position);
        trains.push_back(train);
        
        // create thread and run it
        std::thread thread(&Train::wait, trains.back());
        
        train_coutner++;
        
        // tell everyone that there is no free slot for new waiting train
        StaticWrapper::is_free_slot = false;
    }
}

// TODO: use ncurses and write list of trains, platforms and trains
//void write_trains(std::vector<Train> trains, WINDOW* b)
//{
//    while(1)
//    {
//
//    }
//}

int main()
{
    //WINDOW * a, b;
    
    
    // vector of waiting trains
    std::vector<Train> trains;
    
    // list of platforms
    std::vector<Platform> platforms;
    
    // determines how many trains can be on waiting list
    static int number_of_trains = 3;
    
    static int number_of_platforms = 6;
    
    
    for(int i = 0; i < number_of_platforms; i++){
        Platform platform(i+1);
        platforms.push_back(platform);
    }
    
    for(int i = 0; i < number_of_trains; i++){
        Train train(i+1, i+1);
        trains.push_back(train);
    }
    
    //std::cout << platforms[0].number;
    
    // TODO: add this thread to vector and join them in loop
    
    std::thread thread1(&Platform::work, platforms[0], trains);
    std::thread thread2(&Platform::work, platforms[1], trains);
    std::thread thread3(&Platform::work, platforms[2], trains);
    
    std::thread thread4(&Train::wait, trains[0]);
    std::thread thread5(&Train::wait, trains[1]);
    std::thread thread6(&Train::wait, trains[2]);
    // should be 3 more threads for trains here
    
    std::thread thread_provider(provide_trains,trains);
    
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread_provider.join();
    
}

