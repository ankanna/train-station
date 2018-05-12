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
    static std::condition_variable platform_cv;
    static std::condition_variable list_cv;
    static int train_number;
    static bool platform_is_free;
    static bool is_free_slot;
    
    StaticWrapper();
    
    
    static void notify_platform();
    
    static void notify_list();
};

