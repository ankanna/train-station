//
//  StaticWrapper.h
//  train-station
//
//  Created by Ania on 12.05.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <mutex>
#include <condition_variable>

class StaticWrapper
{
public:
    
    static std::mutex mutex;
    
    // condition variables:
    // blocks thread Train::wait()
    static std::condition_variable platform_cv;
    
    // blocks thread in main provide_trains(std::vector<Train> trains)
    static std::condition_variable list_cv;
    
    // number of last train which found free platform
    static int train_number;
    
    // position on list of last train which found free platform
    static int train_position;
    
    // is there a free platform?
    static bool platform_is_free;
    
    // is there a free slot on list of trains that are waiting for free platform?
    static bool is_free_slot;
    
    StaticWrapper();
    
    // notifies trains about free platform
    static void notify_trains();
    
    // notifies about free slot on list (new train can join to wainting trains)
    static void notify_about_free_slot();
};

