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

void provide_trains(std::vector<Train> &trains)
{
    // couter to provide sequent train numbers (without dupilcation of trains numbers that left platform)
    int train_coutner = StaticWrapper::number_of_trains+1;
    
    while(1)
    {        
        // wait until train goes to free platform
        // https://github.com/Scony/systemy-operacyjne-2/blob/master/projekt/zajecia-3-4-atomic-condvar/program7-cv-wait-pred.cpp
        std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
        StaticWrapper::list_cv.wait(lock, []{ return StaticWrapper::is_free_slot == true; });
        
        // tell everyone that there is no free slot for new waiting train
        StaticWrapper::is_free_slot = false;
        // add new train
        Train train(train_coutner, trains.size());
        trains.push_back(train);
        StaticWrapper::number_of_trains = trains.size();
        

        std::cout << "Added new train number " << train_coutner << std::endl;
        
        // create thread and run it
        std::thread thread(&Train::wait, trains.back());
        thread.join();
        
        train_coutner++;

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

void initialize_ncurses()
{
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    refresh(); // Need this to let other windows be drawn
}

int main()
{
    //WINDOW * a, b;
    
    
    // vector of waiting trains
    std::vector<Train> trains;
    
    // list of platforms
    std::vector<Platform> platforms;
    
    // determines how many trains can be on waiting list
    static int number_of_trains = 4;
    
    static int number_of_platforms = 3;
    
    
    for(int i = 0; i < number_of_platforms; i++){
        Platform platform(i+1);
        platforms.push_back(platform);
    }
    
    for(int i = 0; i < number_of_trains; i++){
        Train train(i+1, i);
        trains.push_back(train);
    }
    
    
    // TODO: add this thread to vector and join them in loop
    
    std::thread thread4(&Train::wait, trains[0]);
          usleep(1000000/4);
    std::thread thread5(&Train::wait, trains[1]);
          usleep(1000000/4);
    std::thread thread6(&Train::wait, trains[2]);
          usleep(1000000/4);
    std::thread thread7(&Train::wait, trains[3]);
              usleep(1000000/4);
    
    StaticWrapper::number_of_trains = trains.size();
    
    std::thread thread1(&Platform::work, platforms[0], std::ref(trains));
        usleep(1000000/3);
    std::thread thread2(&Platform::work, platforms[1], std::ref(trains));
        usleep(1000000/3);
    std::thread thread3(&Platform::work, platforms[2], std::ref(trains));
        usleep(1000000/3);
    
    std::thread thread_provider(provide_trains, std::ref(trains));
    
    // trains:
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();

    // platforms:
    thread1.join();
    thread2.join();
    thread3.join();
    
    
    thread_provider.join();
    
    
}

