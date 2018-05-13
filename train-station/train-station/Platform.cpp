//
//  Platform.cpp
//  train-station
//
//  Created by Anna Antonczak on 12.05.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//
#include <stdio.h>
#include "StaticWrapper.h"
#include "Train.h"
#include "Platform.h"
#include <vector>
#include <unistd.h>

Platform::Platform(int num){
    number = num;
}

Platform::Platform(){
}

void Platform::work(std::vector<Train> trains)
{
    while(1)
    {
        // set platform as free and notify trains
        StaticWrapper::platform_is_free = true;
        StaticWrapper::notify_trains();
        
        // delete last train which entered the platform from list of waiting trains
        trains.erase(trains.begin() + StaticWrapper::train_position);
        
        // tell everyone that train is on platform and new train can join waiting trains
        // (provide_trains(std::vector<Train> trains) in main should do the work and create new train)
        StaticWrapper::notify_about_free_slot();
        
        // loading time from specific train should be here
        usleep(1000000);
    }
}
