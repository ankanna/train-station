//
//  Train.cpp
//  train-station
//
//  Created by Szymon Kuras on 23.04.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//

#include <time.h>
#include <iostream>
#include "StaticWrapper.h"
#include "Train.h"


Train::Train(int train_num, int train_pos)
{
    srand(time(NULL));
    
    train_number = train_num;
    train_position = train_pos;
    loading_time = (rand() % 7) + 1;
    max_waiting_time = (rand() % 20) + 20;
    
    priority = (rand() % 10) + 1;
    // not necessary
    // state = 'w'; //waiting (also possible: a - approaching, l - loading)
}

Train::Train(){}

void Train::wait()
{
    // wait until any platform is free
    std::cout << "Train " << train_number << " is waiting " << std::endl;;
    std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
    StaticWrapper::platform_cv.wait(lock, []{ return StaticWrapper::platform_is_free && StaticWrapper::number_of_trains < 6; });

    // assign number and position of this train as last train which found free platform
    StaticWrapper::train_number = train_number;
    StaticWrapper::train_position = train_position;
    
    std::cout << " Train " << train_number << " goes to platform " << StaticWrapper::platform_number << std::endl;
    StaticWrapper::platform_is_free = false;


}
