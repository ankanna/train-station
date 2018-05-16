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

#define RDELAY 100000

void provide_trains(std::vector<Train> &trains, WINDOW *list_window)
{
    // couter to provide sequent train numbers (without dupilcation of trains numbers that left platform)
    int train_coutner = StaticWrapper::number_of_trains+1;
    
    while(1)
    {        
        // wait until train goes to free platform
        std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
        StaticWrapper::list_cv.wait(lock, []{ return StaticWrapper::is_free_slot == true; });
        
        // tell everyone that there is no free slot for new waiting train
        StaticWrapper::is_free_slot = false;
        // add new train
        Train train(train_coutner, trains.size());
        trains.push_back(train);
        StaticWrapper::number_of_trains = trains.size();
        

    //    std::cout << "Added new train number " << train_coutner << std::endl;
        
        // create thread and run it
        std::thread thread(&Train::wait, trains.back(), list_window);
        thread.detach();
        
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

void init_ncurses()
{
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    refresh(); // Need this to let other windows be drawn
}

void refresh_screen(WINDOW *list_window, WINDOW *platforms_window)
{
    while (1)
    {
        StaticWrapper::lock();
        wrefresh(list_window);
        wrefresh(platforms_window);
        StaticWrapper::unlock();
        usleep(RDELAY);
    }
}

void init_windows(WINDOW *list_window, WINDOW *platforms_window){
    int maxx, maxy, halfx, halfy;
    getmaxyx(stdscr, maxy, maxx);
    halfx = maxx >> 1;
    halfy = maxy >> 1;
    
    // create two windows
    list_window = newwin(maxy, halfx, 0, 0);
    platforms_window = newwin(maxy, halfx, halfy, 0);
}

void create_threads(WINDOW *list_window, WINDOW *platforms_window){
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
    
    StaticWrapper::number_of_trains = trains.size();
    
    std::vector<std::thread> threads;
    
    // start new threads and push them to vector
    
    //trains
    for (int i = 0; i < number_of_trains; i++){
        threads.push_back(std::thread(&Train::wait, trains[i], list_window));
        usleep(1000000/4);
    }
    
    //platforms
    for (int i = 0; i < number_of_platforms; i++){
        threads.push_back(std::thread(&Platform::work, platforms[0], std::ref(trains)));
        usleep(1000000/3);
    }
    
    threads.push_back(std::thread(provide_trains, std::ref(trains), list_window));
    
    threads.push_back(std::thread(refresh_screen, list_window, platforms_window));
    
    for (auto& thread : threads) // for (int i = 0; i < 10; i++)
        thread.join();           // threads[i].join();
    
}
int main()
{
    
    WINDOW *list_window, *platforms_window;

    init_ncurses();
    
    int maxx, maxy, halfx, halfy;
    getmaxyx(stdscr, maxy, maxx);
    halfx = maxx >> 1;
    halfy = maxy >> 1;
    
    /* create two windows to fill the screen */
    // WINDOW *a, *b, *c, *d;
    list_window = newwin(maxy, halfx, 0, 0);
    platforms_window = newwin(maxy, halfx, halfy, 0);

   // init_windows(list_window, platforms_window);
    
    create_threads(list_window, platforms_window);
    
}

