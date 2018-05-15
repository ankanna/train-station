//
//  Train.h
//  train-station
//
//  Created by Ania on 12.05.2018.
//  Copyright © 2018 ankanna. All rights reserved.
//
#pragma once
#include <iostream>


class Train
{
public:
    
    int train_number;
    int train_position;
    int loading_time;
    int waiting_time;
    
    int priority;
    
    Train(int train_number, int train_position);
    
    Train();
    
    // wait for free platform
    void wait();
};

