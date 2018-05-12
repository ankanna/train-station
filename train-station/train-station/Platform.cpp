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
            StaticWrapper::notify_platform();
            
            //Train train(StaticWrapper::train_number);
            
            trains.erase(trains.begin() + StaticWrapper::train_number);
            
        //    trains.insert(trains.begin() + StaticWrapper::train_number, train);
            
            StaticWrapper::notify_list();
        //    std::cout << "Platform " << number << " has train number: " << train.get_train_number();
            usleep(1000000);
        }
    }
