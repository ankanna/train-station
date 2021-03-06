//
//  StaticWrapper.cpp
//  train-station
//
//  Created by Anna Antonczak on 12.05.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "StaticWrapper.h"

std::mutex StaticWrapper::mutex;

std::condition_variable StaticWrapper::platform_cv;

std::condition_variable StaticWrapper::list_cv;

int StaticWrapper::train_number;

int StaticWrapper::train_position;

int StaticWrapper::platform_number;

bool StaticWrapper::platform_is_free;

bool StaticWrapper::is_free_slot;

int StaticWrapper::number_of_trains;

// vector of waiting trains
std::vector<Train> StaticWrapper::trains;

StaticWrapper::StaticWrapper(){
    platform_is_free = false;
    is_free_slot = false;
}

void StaticWrapper::notify_trains()
{
    platform_cv.notify_one();
}

void StaticWrapper::notify_about_free_slot()
{
    list_cv.notify_one();
}

void StaticWrapper::lock()
{
    mutex.lock();
}

void StaticWrapper::unlock()
{
    mutex.unlock();
}

void StaticWrapper::wait_for_platform(int train_number)
{
    std::unique_lock<std::mutex> lock(mutex);
    std::cout << "Train " << train_number << " is waiting..." << std::endl;;
    platform_cv.wait(lock, []{ return platform_is_free && number_of_trains < 6; });
}

void StaticWrapper::serve_train(std::vector<Train> &trains)
{
    if (!trains.empty())
    {
        trains.erase(trains.begin() + train_position);
    }
}
