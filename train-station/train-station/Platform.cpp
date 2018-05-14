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
        // delete last train which entered the platform from list of waiting trains
        std::cout << "Train " << StaticWrapper::train_number << " is going to leave in " << StaticWrapper::trains[StaticWrapper::train_position].waiting_time << " seconds." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(StaticWrapper::trains[StaticWrapper::train_position].waiting_time));
        
        StaticWrapper::serve_train();
        std::cout << "Train " << StaticWrapper::train_number << " has just departed from platform " << StaticWrapper::platform_number << ". What a relief!" << std::endl;
        
        // set platform as free and notify trains
        StaticWrapper::platform_is_free = true;
        StaticWrapper::notify_trains();        
        
        StaticWrapper::platform_number = number;
        
        // tell everyone that train is on the platform and new train can join waiting trains
        // (provide_trains(std::vector<Train> trains) in main should do the work and create new train)
        StaticWrapper::is_free_slot = true;
        StaticWrapper::notify_about_free_slot();
        
        // loading time from specific train should be here
        std::cout << "Train " << trains[StaticWrapper::train_position].train_number << " is on platform " << number << std::endl;
        usleep(1000000);

    }
}
