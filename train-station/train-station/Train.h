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
    int train_number;
    int loading_time;
    int max_waiting_time;
    
    int priority;
    char state;
    
    
public:
    
    Train(int train_number);
    
    Train();
    
    int get_train_number();
    
    int get_train_priority();
    
    void wait();
};

