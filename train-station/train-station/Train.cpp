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
    

     Train::Train(int train_num)
    {
        srand(time(NULL));

        train_number = train_num;
        loading_time = (rand() % 7) + 1;
        max_waiting_time = (rand() % 20) + 20;
        
        priority = (rand() % 10) + 1;
        state = 'w'; //waiting (also possible: a - approaching, l - loading)
    }
    
    Train::Train(){}
    
    int Train::get_train_number(){
        return train_number;
    }
    
    int Train::get_train_priority(){
        return priority;
    }


    // wait until platform is free
    void Train::wait()
    {
        std::unique_lock<std::mutex> lock(StaticWrapper::mutex);
        StaticWrapper::platform_cv.wait(lock, []{ return StaticWrapper::platform_is_free == true; });// TODO: add condition about number of wainting trains
        
        // assign number of train as last train 
        StaticWrapper::train_number = train_number;
        StaticWrapper::platform_is_free = false;
    }
